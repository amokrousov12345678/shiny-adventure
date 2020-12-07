template<typename T>
T div(T a, T b) {
    return a/b;
}

ll binPow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b&1) {
            res = (res*a) % mod;
        }
        a = (a*a) % mod;
        b>>=1;
    }
    return res;
}

ll inv(ll a) {
    return binPow(a, mod-2);
}

template<>
int div(int a, int b) {
    return (a*inv(b)) % mod;
}

template<>
ll div(ll a, ll b) {
    return (a*inv(b)) % mod;
}

//обязательно нужен столбец свободных членов
template<typename M>
vector<int> gauss(M& a) {
    int m = a.m - 1;
    int n = a.n;
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {

        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs(a(i, col)) > abs(a(sel,col)))
                sel = i;

        if (abs(a(sel,col)) < eps)
            continue;
        for (int i=col; i<=m; ++i)
            swap(a(sel,i), a(row,i));
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                auto c = div(a(i,col), a(row, col));
                for (int j=col; j<=m; ++j) {
                    auto acc = a(row,j) * c;
                    a.doMod(acc);
                    a(i,j) -= acc;
                    a.doMod(a(i,j));
                }
            }
        ++row;
    }
    return where;
}