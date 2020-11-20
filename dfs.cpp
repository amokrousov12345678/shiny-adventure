//в графе для вершины должно быть поле used
template<typename VType, typename EType, typename VIdType, typename EIdType=None>
bool dfsImpl(Graph<VType, EType, VIdType, EIdType>& g, int v, int p, ParEdgeType* edge) {
    if (g.v[v].used) return false;
    g.v[v].used = true;
    //or for tree: if (v==p) return;

    auto label = g.asLabel(v);
    //g.addOEdge(v, g.asV(vector<int>{label[3], label[0], label[1], label[2]}), {-1, 0});

    for (auto& it : g.g[v]) {
        if (dfsImpl(g, it.to, v, &it)) {
            return true;
        }
    }
    return false;
}

template<typename GType>
auto dfs(GType& g, int v) {
    for (auto& it: g.v) {
        it.used = false;
    }
    return dfsImpl(g,v, -1, nullptr);
}