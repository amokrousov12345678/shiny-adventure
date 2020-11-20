//когда построили поднимаемся, из depth[cur] берем текущий уровень, через него получам dist[depth][v] - расстояние до вершины от текущего центроида, и с учетом его релаксируем значение в вершине центроида
template<typename GraphType, typename ValueType>
    struct Centroid {
        vector<int> level; //глубина вершины в дереве центроидов
        vector<int> par; //предок-центроид
        vector<vector<int>> d; //d[i][j] - расстояние от центроида i левела до вершины j
        vector<ValueType> cData; //функция в вершине
        GraphType& g;

        void build(int v, int size, int depth, int last) {
            int center = -1;
            dfs(v, size, center);
            level[center] = depth;
            par[center] = last;
            d[depth][center] = 0;
            for (auto& it: g.g[center]) {
                int x = it.to;
                if (level[x] == -1) {
                    dfs2(x, depth, 1);
                    build(x, size/2, depth+1, center);
                }
            }
        }

        int dfs(int v, int size, int& center, int p = -1) {
            int sum = 1;
            for (auto& it: g.g[v]) {
                int x = it.to;
                if (level[x] == -1 && x != p) {
                    sum += dfs(x, size, center, v);
                }
            }
            if (center == -1 && (2*sum>=size || p == -1)) {
                center = v;
            }
            return sum;
        }

        void dfs2(int v, int depth, int dist, int p = -1) {
            d[depth][v] = dist;
            for (auto& it: g.g[v]) {
                int x = it.to;
                if (level[x] == -1 && x != p) {
                    dfs2(x, depth, dist+1, v);
                }
            }
        }

        Centroid(GraphType &g, ValueType initialVal): g(g) {
            int n = g.v.size();
            int logn = 0;
            int cur = 1;
            while (cur<n) {
                cur <<= 1;
                logn++;
            }
            d.assign(logn+1, vector<int>(n, -1));
            par.resize(n);
            level.assign(n, -1);
            cData.assign(n, initialVal);
            build(0, n, 0, -1);
        }
    };