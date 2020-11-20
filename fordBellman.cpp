template<typename VType, typename EType, typename VIdType, typename EIdType>
vector<PFInfo<EIdType, EType>> fordBellman(Graph<VType, EType, VIdType, EIdType>& g, int start) {
    vector<PFInfo<EIdType, EType>>& res = g.pf;
    res.assign(res.size(), PFInfo<EIdType, EType>());

    res[start].par = -2;
    res[start].dist = 0;

    int n = g.v.size();
    for (int phase = 0;phase<n-1;phase++) {
        for (int v=0;v<n;v++) {
            if (res[v].dist == INF64) continue;
            for (auto& it: g.g[v]) {
                int to = it.to;
                ll w = it.w;
                if (res[v].dist+w<res[to].dist) {
                    res[to].par = v;
                    res[to].parEdge = it;
                    res[to].dist = res[v].dist+w;
                }
            }
        }
    }

    return res;
}