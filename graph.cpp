struct None {
    friend bool operator<(const None& lhs, const None& rhs) {
        return false;
    }
};

struct Edge {
    int to;
};

struct WEdge {
    int to;
    ll w;
};

#define ParEdgeType typename conditional<is_same<EIdType,None>::value, EType, pair<EIdType, EType>>::type
template<typename EIdType, typename EType>
struct PFInfo {
    int par = -1;
    ll dist = INFll;
    ParEdgeType parEdge;

    friend bool operator<(const PFInfo& a, const PFInfo& b) {
        return a.dist<b.dist;
    }

    bool isPath() {
        return dist!=INFll;
    }
};

#define FOR_GRAPH(ReturnType) template<typename EIdType_=EIdType> \
        typename enable_if<is_same<EIdType_, None>::value, ReturnType>::type
#define FOR_BOR(ReturnType) template<typename EIdType_=EIdType> \
        typename enable_if<!is_same<EIdType_, None>::value, ReturnType>::type

template<typename VType_, typename EType_, typename VIdType=None, typename EIdType=None>
struct Graph {
    using VType = VType_;
    using EType = EType_;
    vector<VType> v;
    typename conditional<is_same<EIdType, None>::value, vector<vector<EType>>, vector<map<EIdType, EType>>>::type g;
    vector<PFInfo<EIdType, EType>> pf;

    Graph(int n): v(n), g(n), pf(n) {};
    Graph(): Graph(0) {};

    FOR_GRAPH(void) addOEdge(int u, int v, const EType& newE) {g[u].push_back(newE); g[u].back().to = v;}
    FOR_BOR(void) addOEdge(int u, int v, const EType& newE) {assert(false);}
    FOR_GRAPH(void) addEdge(int u, int v, const EType& newE) {addOEdge(u,v, newE);addOEdge(v,u, newE);}
    FOR_BOR(void) addEdge(int u, int v, const EType& newE) {assert(false);}

    FOR_BOR(void) addOEdge(int u, int v, const EIdType& newEId, const EType& newE) {assert(g[u].count(newEId)==0); g[u][newEId] = newE; g[u][newEId].to = v;}
    FOR_GRAPH(void) addOEdge(int u, int v, const EIdType& newEId, const EType& newE) {assert(false);}

    //to update edge after insertion
    FOR_GRAPH(int) addOEdge(int u, int v) {g[u].emplace_back(); g[u].back().to = v; return ((int) g[u].size())-1;};
    FOR_BOR(int) addOEdge(int u, int v) {assert(false);};

    FOR_BOR(int) goTo(int from, const EIdType& eId, const EType& newE) {
        if (!g[from].count(eId)) {
            int to = g.addV();
            addOEdge(from, to, eId, newE);
        }
        return g[from][eId].to;
    }
    FOR_GRAPH(int) goTo(int from, const EIdType& eId, const EType& newE) {assert(false);}

    int addV() {
        int id = v.size();
        v.emplace_back();
        g.emplace_back();
        pf.emplace_back();
        return id;
    }

    map<VIdType, int> ids; //or unordered_map if better
    vector<VIdType> idsBack;

    //if too slow, use external vertex id generator, but don't forget to allocate graph of required size
    int asV(const VIdType& id) {
        if (!ids.count(id)) {
            ids[id] = addV();
            idsBack.push_back(id);
        }
        return ids[id];
    }
    const VIdType& asLabel(int id) {
        return idsBack[id];
    }

    void printAdj() const {
        for (int i=0;i<g.size();i++) {
            cout << i+1 << ": ";
            for (auto& it: g[i]) {
                cout << it.to+1 << " ";
            }
            cout << "\n";
        }
        cout << endl;
    }
};
//contains common algorithm to restore path

template<typename EIdType, typename EType>
struct Path {
    vector<int> verts;
    vector<ParEdgeType> edges;
};

template<typename EIdType, typename EType>
Path<EIdType, EType> restorePath(const vector<PFInfo<EIdType, EType>>& pfInfo, int to) {
    vector<int> verts;
    vector<ParEdgeType> edges;
    while (true) {
        verts.push_back(to);
        if (pfInfo[to].par == -1) { //Not found
            return {};
        }
        if (pfInfo[to].par == -2) {
            reverse(verts.begin(), verts.end());
            reverse(edges.begin(), edges.end());
            return {verts, edges};
        }
        edges.push_back(pfInfo[to].parEdge);
        to = pfInfo[to].par;
    }
}