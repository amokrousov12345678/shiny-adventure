template<typename VType, typename EType, typename VIdType, typename EIdType>
vector<PFInfo<EIdType, EType>> bfs(Graph<VType, EType, VIdType, EIdType>& g, int start) {
    vector<PFInfo<EIdType, EType>>& res = g.pf;
    res.assign(res.size(), PFInfo<EIdType, EType>());
    queue<int> s;
    res[start].par = -2;
    res[start].dist = 0;
    s.push(start);
    while (!s.empty()) {
        int v = s.front();
        s.pop();
        //add edges if need
        for (auto& it: g.g[v]) {
            int to = it.to;
            if (res[to].dist == INF64) {
                res[to].par = v;
                res[to].dist = res[v].dist + 1;
                res[to].parEdge = it;
                s.push(to);
            }
        }
    }
    return res;
}