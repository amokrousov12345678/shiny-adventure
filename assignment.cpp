struct ASSolution {
    vector<int> rowForEachCol;
    vector<ll> u, v;
    ll cost;
};

ASSolution assignment(Matrix<ll>& matr) {
    int n = matr.n;
    int m = matr.m;
 
    vector<ll> u(n+1), v(m+1);
    vector<int> p(m+1), way(m+1);
 
    for (int i=1; i<=n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<ll> minv(m + 1, INFll);
        vector<char> used(m + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], j1;
            ll delta = INFll;
            for (int j = 1; j <= m; ++j)
                if (!used[j]) {
                    ll cur = matr(i0 - 1, j - 1) - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur, way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j], j1 = j;
                }
            for (int j = 0; j <= m; ++j)
                if (used[j])
                    u[p[j]] += delta, v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    ll cost = -v[0];
    for (int i=1;i<=n;i++) {
        u[i-1] = u[i];
    }
    u.pop_back();
    for (int i=1;i<=m;i++) {
        v[i-1] = v[i];
        p[i-1] = p[i]-1;
    }
    v.pop_back();
    p.pop_back();
    return {p, u, v, cost};
}