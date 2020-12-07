ll mod = 998244353;

template<typename T, bool modulo = false>
struct Matrix {
    vector<T> data;
    int n, m;
    Matrix(int n, int m): n(n), m(m), data(n*m, 0) {};

    static Matrix identity(int n) {
        Matrix res(n,n);
        for (int i=0;i<n;i++) {
            res(i,i) = 1;
        }
        return res;
    }

    T& operator()(int i, int j) {
        assert(i<n);
        assert(j<m);
        return data[i*m+j];
    }

    T operator()(int i, int j) const {
        assert(i<n);
        assert(j<m);
        return data[i*m+j];
    }

    template<bool modulo_=modulo> typename std::enable_if<!modulo_, void>::type doMod(T& val) const {};

    template<bool modulo_=modulo> typename std::enable_if<modulo_, void>::type doMod(T& val) const {val %= mod;};

    friend Matrix operator*(const Matrix& l, const Matrix& r) {
        assert(l.m==r.n);
        Matrix res(l.n, r.m);
        for (int i=0;i<l.n;i++) {
            for (int j=0;j<r.m;j++) {
                for (int k=0;k<l.m;k++) {
                    //__int128 kk = l(i, k);
                    //kk *= r(k,j);
                    //kk %= mod;
                    T kk = l(i,k) * r(k,j);
                    l.doMod(kk);
                    res(i,j) += kk;
                    l.doMod(res(i,j));
                }
            }
        }
        return res;
    }
    Matrix operator*=(const Matrix& r) {
        *this = (*this)*r;
        return *this;
    }
    friend Matrix operator+(const Matrix& l, const Matrix& r) {
        assert(l.n==r.n && l.m==r.m);
        Matrix res(l.n, l.m);
        for (int i=0;i<l.n;i++) {
            for (int j=0;j<l.m;j++) {
                res(i,j) = (l(i,j)+r(i,j));
                l.doMod(res(i,j));
            }
        }
        return res;
    }
    Matrix operator+=(const Matrix& r) {
        *this = (*this)+r;
        return *this;
    }

    friend Matrix operator*(const Matrix& l, ll r) {
        Matrix res(l.n, l.m);
        for (int i=0;i<l.n;i++) {
            for (int j=0;j<l.m;j++) {
                res(i,j) = (l(i,j)*r);
                l.doMod(res(i,j));
            }
        }
        return res;
    }
    Matrix operator*(ll r) {
        *this = (*this)*r;
        return *this;
    }

    friend Matrix binPow(Matrix a, ll b) {
        assert(a.n==a.m);
        auto res = Matrix::identity(a.n);
        while (b) {
            if (b& 1) {
                res*=a;
            }
            a*=a;
            b>>=1;
        }
        return res;
    }
};




void solve() {
    ll n,k,m;
    cin >> n >> k >> m;
    mod = m;
    Matrix<ll, true> matr(2,2);
    matr(0, 0) = 0;
    matr(0, 1) = 1;
    matr(1, 0) = k-1;
    matr(1, 1) = k-1;

    Matrix<ll, true> dp0(2,1);
    dp0(0,0) = 0;
    dp0(1,0) = 1;

    Matrix<ll, true> kk = binPow(matr, n);
    Matrix<ll, true> ans = kk*dp0;
    cout << ans(1,0);
}
int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // freopen("input.txt","r",stdin);
    solve();
    return 0;
}