template<typename VType, typename EType, typename VIdType, typename EIdType>
vector<PFInfo<EIdType, EType>> dijkstra(Graph<VType, EType, VIdType, EIdType>& g, int start) {
    vector<PFInfo<EIdType, EType>>& res = g.pf;
    res.assign(res.size(), PFInfo<EIdType, EType>());

    set<pair<ll,int>> s;
    s.insert({0,start});

    res[start].par = -2;
    res[start].dist = 0;

    while (!s.empty()) {
        auto p = *s.begin();
        int v = p.second;
        s.erase(p);

        //add edges if need
        for (auto& it: g.g[v]) {
            int to = it.to;
            ll w = it.w;
            if (res[v].dist+w<res[to].dist) {
                s.erase({res[to].dist, to});
                res[to].par = v;
                res[to].parEdge = it;
                res[to].dist = res[v].dist+w;
                s.insert({res[to].dist, to});
            }
        }
    }
    return res;
}