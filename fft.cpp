ll bin_pow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res*=a;
            res %=mod;
        }
        a*=a;
        a %= mod;
        b>>=1;
    }
    return res;
}

template<int mod, int root, int rootPw>
struct FFT {
private:
    ll mul(ll a, ll b) {
        return (a*b) % mod;
    }

    ll bin_pow(ll a, ll b) {
        ll res = 1;
        while (b) {
            if (b & 1) {
                res = mul(res, a);
            }
            a = mul(a,a);
            b>>=1;
        }
        return res;
    }
    ll reverse(ll a) {
        return bin_pow(a,mod-2);
    }
public:
    vector<int> operator()(const vector<int>& a, int n, bool invert) {
        assert(mod==::mod);
        int root_1 = reverse(root);

        int pow2 = 1;
        while (pow2<n) {
            pow2 <<= 1;
        }
        n = pow2;
        vector<int> res(n, 0);
        std::copy(a.begin(), a.end(), res.begin());


        for (int i=1, j=0; i<n; ++i) {
            int bit = n >> 1;
            for (; j>=bit; bit>>=1)
                j -= bit;
            j += bit;
            if (i < j)
                swap (res[i], res[j]);
        }

        for (int len=2; len<=n; len<<=1) {
            int wlen = invert ? root_1 : root;
            for (int i=len; i<rootPw; i<<=1)
                wlen = int (wlen * 1ll * wlen % mod);
            for (int i=0; i<n; i+=len) {
                int w = 1;
                for (int j=0; j<len/2; ++j) {
                    int u = res[i+j],  v = int (res[i+j+len/2] * 1ll * w % mod);
                    res[i+j] = u+v < mod ? u+v : u+v-mod;
                    res[i+j+len/2] = u-v >= 0 ? u-v : u-v+mod;
                    w = int (w * 1ll * wlen % mod);
                }
            }
        }
        if (invert) {
            int nrev = reverse (n);
            for (int i=0; i<n; ++i)
                res[i] = int (res[i] * 1ll * nrev % mod);
        }
        return res;
    }
};

FFT<998244353, 15311432 /*3^(7*17)*/, 1<<23> fft;