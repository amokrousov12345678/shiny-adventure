template<typename Graph>
struct Dinitz {
    Graph& g;
    int n;
    Dinitz(Graph& g): g(g), n(g.v.size()) {};

    vector<int> d;
    vector<int> ptr;

    void bfs(int s) {
        queue<int> q;
        q.push(s);
        for (int i=0;i<n;i++) {
            d[i] = -1;
        }
        d[s] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i=0;i<g.g[v].size();i++) {
                auto& edge = g.g[v][i];
                int to = edge.to;
                if (d[to]!=-1) continue;
                if (edge.flow==edge.cap) continue;
                d[to] = d[v]+1;
                q.push(to);
            }
        }
    }

    ll dfs(int v, ll in, int t) {
        if (!in) return 0;
        if (v==t) return in;
        for (;ptr[v]<g.g[v].size();ptr[v]++) {
            auto& edge = g.g[v][ptr[v]];
            int to = edge.to;
            if (d[to] != d[v] + 1) continue;
            ll pushed = dfs(to, min(in, edge.cap-edge.flow), t);
            if (pushed) {
                edge.flow += pushed;
                g.g[to][edge.invId].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    ll operator()(int s, int t) {
        for (int i=0;i<n;i++) {
            for (auto& edge: g.g[i]) {
                edge.flow = 0;
            }
        }
        d.resize(g.v.size());


        ll ans = 0;
        while (1) {
            bfs(s);
            if (d[t]==-1) break;
            ptr.assign(g.v.size(), 0);
            while (ll f = dfs(s, INFll, t)) {
                ans+=f;
            }
        }
        return ans;
    }
};

template<typename Graph>
int addOEdge(Graph& g, int from, int to, ll cap) {
    int eId1 = g.addOEdge(from, to);
    int eId2 = g.addOEdge(to, from);
    auto& e1 = g.g[from][eId1];
    auto& e2 = g.g[to][eId2];
    e1.cap = cap;
    e1.flow = 0;
    e1.invId = eId2;
    e2.cap = 0;
    e2.flow = 0;
    e2.invId = eId1;
    return eId1;
}

struct FlowEdge {
    int to;
    int invId;
    ll cap;
    ll flow;
};