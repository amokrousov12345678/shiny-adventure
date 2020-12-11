template<typename Graph>
struct StrongComponents {
    Graph& g;
    ::Graph<None, Edge> gT;
    ::Graph<None, Edge> gCondens;
    vector<int> vertComp;
    vector<vector<int>> components;

    vector<int> _cur_component;
    vector<int> order;
    vector<char> used;

    void dfs1 (int v) {
        used[v] = true;
        for (size_t i=0; i<g.g[v].size(); ++i)
            if (!used[g.g[v][i].to])
                dfs1 (g.g[v][i].to);
        order.push_back (v);
    }

    void dfs2 (int v) {
        used[v] = true;
        _cur_component.push_back (v);
        for (size_t i=0; i<gT.g[v].size(); ++i)
            if (!used[gT.g[v][i].to])
                dfs2 (gT.g[v][i].to);
    }

    StrongComponents(Graph& g): g(g), gT(g.v.size()) {
        int n = g.v.size();

        for (int i=0;i<n;i++) {
            for (auto it: g.g[i]) {
                gT.addOEdge(it.to, i, {});
            }
        }

        vertComp.assign(n, -1);
        used.assign (n, 0);
        for (int i=0; i<n; ++i)
            if (!used[i])
                dfs1 (i);

        used.assign (n, 0);
        for (int i=0; i<n; ++i) {
            int v = order[n - 1 - i];
            if (!used[v]) {
                dfs2(v);
                int id = components.size();
                for (auto& it: _cur_component) {
                    vertComp[it] = id;
                }
                components.push_back(_cur_component);
                _cur_component.clear();
            }
        }

        gT = decltype(gT)(1);
        order.clear();
        used.clear();

        int k = components.size();
        gCondens = decltype(gCondens)(k);
        unordered_set<pair<int,int>> createdEdges;
        for (int i=0;i<n;i++) {
            for (auto it: g.g[i]) {
                int from = i;
                int to = it.to;
                int fromC = vertComp[from];
                int toC = vertComp[to];
                if (fromC==toC) continue;
                if (fromC>toC) {
                    swap(from, to);
                    swap(fromC, toC);
                }
                if (createdEdges.count({fromC,toC})) continue;
                gCondens.addOEdge(fromC, toC, {});
                createdEdges.insert({fromC, toC});
            }
        }
    }
};