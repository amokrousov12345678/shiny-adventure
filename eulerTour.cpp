//полезно, если надо выдать смежные ребра без повторов
//если надо вернуть подотрезок определенной длины - надо ифнуть 1.) при добавлении в стек (правда тогда что накопилось в стеке надо выкинутЬ) 2.) при доббавлении в ответ
template<typename VType, typename EType, typename VIdType, typename EIdType>
Path<EIdType, EType> eulerTour(Graph<VType, EType, VIdType, EIdType>& g, int v, int edgesLen = 1e9) {
    stack<ParEdgeType> s;
    ParEdgeType e;
    e.to = v;
    s.push(e);
    vector<int> verts;
    vector<ParEdgeType> edges;
    while (!s.empty()) {
        int v = s.top().to;

        auto& ptr = g.v[v].ptr;
        for (;ptr<g.g[v].size();ptr++) {
            if (!g.g[v][ptr].deleted) {
                s.push(g.g[v][ptr]);
                g.g[v][ptr].deleted = true;
                break;
            }
        }
        if (g.v[v].ptr == g.g[v].size()) {
            edges.push_back(s.top());
            s.pop();
            verts.push_back(v);
        } else {
            g.v[v].ptr++;
        }

    }
    edges.pop_back();
    reverse(verts.begin(), verts.end());
    reverse(edges.begin(), edges.end());
    return {verts, edges};
}