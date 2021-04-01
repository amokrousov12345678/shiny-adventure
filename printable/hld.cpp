template<typename GraphType, typename RMQType, bool ValuesInVerts = true>
    struct HLD {
        using VType = typename GraphType::VType;
        using EType = typename GraphType::EType;
        using ValType = typename RMQType::T;
        using PushType = typename RMQType::PushT;

        vector<int> par, sz_sub, mx, pos, root, depth;
        vector<ValType> vals;
        RMQType& rmq;
        GraphType& g;
        std::function<ValType(const VType& v, const EType& e)> getValue;

        HLD(GraphType& g, RMQType& rmq, vector<int> roots,
            std::function<ValType(const VType& v, const EType& e)> getValue): g(g), rmq(rmq), getValue(getValue) {
            int n = g.v.size();

            par.assign(n, -1);
            sz_sub.assign(n, 0);
            mx.assign(n, 0);
            pos.assign(n, 0);
            root.assign(n, 0);
            depth.assign(n, 0);
            vals.resize(n);

            for (auto& v0: roots) {
                vals[v0] = getValue(g.v[v0], {});
                dfs_all(v0);
            }

            build_array();
        }

        void dfs_all(int v, int d = 0) {
            depth[v] = d;
            sz_sub[v] = 1;
            int ind = -1, mai = -1;
            for (auto it : g.g[v]) {
                if (par[v] != it.to) {
                    par[it.to] = v;
                    vals[it.to] = getValue(g.v[it.to], it);
                    dfs_all(it.to, d+1);
                    sz_sub[v] += sz_sub[it.to];
                    if (sz_sub[it.to] > mai) {
                        mai = sz_sub[it.to];
                        ind = it.to;
                    }
                }
            }

            mx[v] = ind;
        }

        void build_array() {
            int cpos = 0;
            int n = g.v.size();
            for (int i=0;i<n;i++) {
                if (par[i] == -1 || mx[par[i]]!=i)
                    for (int v = i; v!= -1; v= mx[v]) {
                        rmq.setVal(cpos, vals[v]);
                        pos[v] = cpos++;
                        root[v] = i;
                    }
            }
        }

        int lca(int u, int v) {
            while (root[u]!=root[v]) {
                if (depth[root[u]] < depth[root[v]])
                    swap(u,v);
                u = par[root[u]];
                if (u==-1) return -1;
            }
            if (depth[u]<depth[v])
                swap(u,v);
            return v;
        }

        ValType query(int u, int v) {
            auto ans = rmq.neutral;
            while (root[u]!=root[v]) {
                if (depth[root[u]] < depth[root[v]])
                    swap(u,v);
                ans = rmq.op(ans, rmq.query(pos[root[u]], pos[u]));
                u = par[root[u]];
            }
            if (depth[u]<depth[v])
                swap(u,v);
            ans = rmq.op(ans, rmq.query(pos[v] + !ValuesInVerts, pos[u]));
            return ans;
        }

        void setVal(int v, ValType val) {
            rmq.setVal(pos[v], val);
        }

        ValType getVal(int v) {
            return rmq.getVal(pos[v]);
        }

        void modify(int u, int v, PushType val) { //group ops only
            while (root[u]!=root[v]) {
                if (depth[root[u]] < depth[root[v]])
                    swap(u,v);
                rmq.modify(pos[root[u]], pos[u], val);
                u = par[root[u]];
            }
            if (depth[u]<depth[v])
                swap(u,v);
            rmq.modify(pos[v] + !ValuesInVerts, pos[u], val);
        }
    };