template<typename Graph>
struct Bridges {
    Graph& g;

    unordered_map<pair<int,int>, int> _edgeCnt;
    unordered_set<pair<int,int>> bridges;

    vector<char> used;
    vector<int> tin, fup;
    int timer;

    void dfs (int v, int p = -1) {
        used[v] = true;
        tin[v] = fup[v] = timer++;
        for (size_t i=0; i<g.g[v].size(); ++i) {
            int to = g.g[v][i].to;
            if (to == p)  continue;
            if (used[to])
                fup[v] = min (fup[v], tin[to]);
            else {
                dfs (to, v);
                fup[v] = min (fup[v], fup[to]);
                if (fup[to] > tin[v]) {
                    bridges.insert({v, to});
                }
            }
        }
    }


    Bridges(Graph& g): g(g) {
        int n = g.v.size();
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

        //if multiedges possible
        for (int i=0;i<n;i++) {
            for (auto& it: g.g[i]) {
                _edgeCnt[{i, it.to}]++;
            }
        }

        unordered_set<pair<int,int>> bridgesFiltered;
        for (auto& it: bridges) {
            if (_edgeCnt[it]>1) continue;
            bridgesFiltered.insert(it);
        }
        bridges.swap(bridgesFiltered);
    }
};