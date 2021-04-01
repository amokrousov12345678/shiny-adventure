//after create matching, dfs from unused verts of left part will give us: (L- U R+) - min cover (L+ U R-) - max independent set
template<typename Graph>
struct Kuhn {
    Graph& g;
    vector<int> used, match, part;
    int cc;

    void dfs2(int v, int curPart) {
        if (part[v] != -1) {
            assert(curPart==part[v]); 
			return;
        }
        part[v] = curPart;
        for (auto& it: g.g[v]) {
            dfs2(it.to, curPart^1);
        }
    }

    bool dfs(int v) {
        if (used[v]==cc) return false;
        used[v] = cc;
        for (auto it: g.g[v]) {
            int to = it.to;
            if (match[to]==-1 || dfs(match[to])) {
                match[v] = to;
                match[to] = v;
                return true;
            }
        }
        return false;
    }

    Kuhn(Graph& g): g(g) {
        int n = g.v.size();
        used.assign(n, -1);
        match.assign(n, -1);
        part.assign(n, -1);
        for (int i=0;i<n;i++) {
            if (part[i]==-1) {
                dfs2(i, 0);
            }
        }
        cc = 0;
        for (int i=0;i<n;i++) {
            if (match[i]!=-1) continue;
            if (dfs(i)) {
                cc++;
            }
        }
    }
};