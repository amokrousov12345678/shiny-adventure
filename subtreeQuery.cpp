template<typename GraphType, typename RMQType, bool ValuesInVerts = true>
    struct SubTree {
        using ValType = typename RMQType::T;
        using PushType = typename RMQType::PushT;

        vector<int> par;
        vector<pair<int,int>> poses;
        RMQType& rmq;
        GraphType& g;
        int timer;

        SubTree(GraphType& g, RMQType& rmq, vector<int> roots): g(g), rmq(rmq) {
            int n = g.v.size();

            par.assign(n, -1);
            poses.resize(n);

            timer = 0;
            for (auto& v0: roots) {
                dfs_all(v0);
            }
        }

        void dfs_all(int v) {
            int start = timer++;
            int ind = -1, mai = -1;
            for (auto it : g.g[v]) {
                if (par[v] != it.to) {
                    par[it.to] = v;
                    dfs_all(it.to);
                }
            }
            int end = timer-1;
            poses[v] = {start,end};
        }

        void setVal(int v, ValType val) {
            rmq.setVal(poses[v].first, val);
        }

        ValType getVal(int v) {
            return rmq.getVal(poses[v].first);
        }

        void modify(int v, PushType val) { //group ops only
             rmq.modify(poses[v].first, poses[v].second, val);
        }

        ValType query(int v) {
            return rmq.query(poses[v].first, poses[v].second);
        }
    };