ll base = 31;
ll mod = 998244353;

ll binPow(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = (res*a) % mod;
        }
        a = (a*a) % mod;
        b>>=1;
    }
    return res;
}
ll inv(ll a, ll mod) {
    return binPow(a,mod-2, mod);
}

template<int base, int mod>
struct PolyHash {
    ll val = 0;
    ll curPow = 1;

    ll invBase = inv(base, mod);

    void add(char c) {
        ll tmp = c-'a'+1;
        tmp *= curPow;
        tmp %= mod;
        val += tmp;
        val %= mod;
        curPow *= base;
        curPow %= mod;
    }

    void eraseFirst(char c) {
        val -= (c-'a'+1);
        if (val<0) val+=mod;
        val *= invBase;
        val %= mod;
        curPow *= invBase;
        curPow %= mod;
    }

    friend bool operator==(const PolyHash& l, const PolyHash& r) {
        return l.val==r.val;
    }
};

template<int base1, int mod1, int base2, int mod2>
struct DoublePolyHash {
    PolyHash<base1, mod1> h1;
    PolyHash<base2, mod2> h2;

    void add(char c) {
        h1.add(c);
        h2.add(c);
    }

    void eraseFirst(char c) {
        h1.eraseFirst(c);
        h2.eraseFirst(c);
    }

    friend bool operator==(const DoublePolyHash& l, const DoublePolyHash& r) {
        return l.h1.val==r.h1.val && l.h2.val==r.h2.val;
    }
};


namespace std {
    template<int base, int mod>
    struct hash<PolyHash<base, mod>> {
        size_t operator()(const PolyHash<base, mod> &l) const {
            return l.val;
        }
    };
};

namespace std {
    template<int base1, int mod1, int base2, int mod2>
    struct hash<DoublePolyHash<base1, mod1, base2, mod2>> {
        size_t operator()(const DoublePolyHash<base1, mod1, base2, mod2> &l) const {
            return l.h1.val + l.h2.val*1'000'000'007;
        }
    };
};

using HashType = DoublePolyHash<31, 998244353, 29, 1'000'000'007>;