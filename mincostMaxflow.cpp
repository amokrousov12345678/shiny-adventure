template<typename Graph>
struct MincostMaxflow {
    struct Result {
        ll flow;
        ll cost;
    };

    Graph& g;
    int n;

    vector<ll> phi, d;
    vector<pair<int,int>> par;

    void ford_bellman(int s) {
        phi.assign(n, INFll);
        phi[s] = 0;
        for (int k=0;k<maxn;k++) {
            for (int i=0;i<n;i++) {
                for (auto& edge: g.g[i]) {
                    int to = edge.to;
                    if (edge.cap==edge.flow) continue;
                    if (phi[i]==INFll) continue;
                    if (phi[i] + edge.cost < phi[to]) {
                        phi[to] = phi[i] + edge.cost;
                    }
                }
            }
        }
    }

//дейкстра с потенциалами для каждого шага
    void dijkstra(int s) {
        d.assign(n, INFll);
        par.resize(n);
        d[s] = 0;
        set<pair<ll,int>> verts;
        verts.insert({0,s});
        while (!verts.empty()) {
            int v = verts.begin()->second;
            verts.erase(verts.begin());
            for (int i=0;i<g.g[v].size();i++) {
                auto& edge = g.g[v][i];
                int to = edge.to;
                if (edge.cap==edge.flow) continue;
                ll len = edge.cost + phi[v] - phi[to];

                if (d[to]>d[v]+len) {
                    verts.erase({d[to],to});
                    d[to] = d[v]+len;
                    par[to] = {v, i};
                    verts.insert({d[to],to});
                }
            }
        }
    }

    MincostMaxflow(Graph& g): g(g), n(g.v.size()) {};

    Result operator()(int s, int t) {
        ford_bellman(s);
        dijkstra(s);
        ll cost = 0;
        ll flow = 0;
        while (1) {
            if (d[t]==INFll) break;

            ll pushed = INFll;
            ll sum_cost = 0;
            for (int tmp=t;tmp!=s;) {
                int from = par[tmp].first;
                int eId = par[tmp].second;
                auto& edge = g.g[from][eId];
                sum_cost+=edge.cost;
                pushed = min(pushed, edge.cap-edge.flow);
                tmp = from;
            }

            for (int tmp=t;tmp!=s;) {
                int from = par[tmp].first;
                int eId = par[tmp].second;
                auto& edge = g.g[from][eId];
                edge.flow+=pushed;
                g.g[tmp][edge.invId].flow-=pushed;
                tmp = from;
            }

            cost+=sum_cost*pushed;
            flow+=pushed;

            dijkstra(s);
            for (int i=0;i<n;i++) {
                phi[i] = d[i];
            }
        }
        return {flow, cost};
    }
};

template<typename Graph>
int addOEdge(Graph& g, int from, int to, ll cap, ll cost) {
    int eId1 = g.addOEdge(from, to);
    int eId2 = g.addOEdge(to, from);
    auto& e1 = g.g[from][eId1];
    auto& e2 = g.g[to][eId2];
    e1.cap = cap;
    e1.flow = 0;
    e1.cost = cost;
    e1.invId = eId2;
    e2.cost = -cost;
    e2.cap = 0;
    e2.flow = 0;
    e2.invId = eId1;
    return eId1;
}

struct CostFlowEdge {
    int to;
    int invId;
    ll cap;
    ll cost;
    ll flow;
};
