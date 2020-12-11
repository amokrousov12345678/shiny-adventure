template<typename Graph>
struct Cutpoints {
    Graph& g;
    vector<char> isCutpoint;
    vector<char> used;
    vector<int> tin, fup;
    int timer;

    void dfs (int v, int p = -1) {
        used[v] = true;
        tin[v] = fup[v] = timer++;
        int children = 0;
        for (size_t i = 0; i < g.g[v].size(); ++i) {
            int to = g.g[v][i].to;
            if (to == p) continue;
            if (used[to])
                fup[v] = min(fup[v], tin[to]);
            else {
                dfs(to, v);
                fup[v] = min(fup[v], fup[to]);
                if (fup[to] >= tin[v] && p != -1)
                    isCutpoint[v] = 1;
                ++children;
            }
        }
        if (p == -1 && children > 1)
            isCutpoint[v] = 1;
    }

    Cutpoints(Graph& g): g(g) {
        int n = g.v.size();
        isCutpoint.resize(n, 0);
        used.resize(n, 0);
        tin.resize(n, 0);
        fup.resize(n, 0);
        timer = 0;
        for (int i=0; i<n; ++i) {
            used[i] = false;
        }
        for (int i=0; i<n; ++i) {
            if (!used[i]) {
                dfs(i);
            }
        }
    }
};