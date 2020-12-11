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

int swapCnt = 0;
template<typename M>
vector<int> gauss(M& a, int n = -1, int m = -1) {
    swapCnt = 0;
    if (m==-1) m = a.m;
    if (n==-1) n = a.n;
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {

        int sel = row;
        if (a(sel,col)==0)
            for (int i=row; i<n; ++i)
                if (abs(a(i, col)) > abs(a(sel,col)))
                    sel = i;

        if (abs(a(sel,col)) < eps)
            continue;
        for (int i=col; i<a.m; ++i)
            swap(a(sel,i), a(row,i));
        if (row!=sel) {
            swapCnt++;
        }
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                if (a(i,col)==0) continue;
                ll c = myDiv(a(i,col), a(row, col));
                for (int j=col; j<a.m; ++j) {
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

template<typename M>
typename M::T determinant(M a) {
    gauss(a);
    typename M::T res = swapCnt % 2 ? -1 : 1;
    a.doMod(res);
    for (int i=0;i<a.n;i++) {
        res = res * a(i,i);
        a.doMod(res);
    }
    return res;
}