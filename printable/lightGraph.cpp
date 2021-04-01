//light graph structures
struct Edge {
    int to;
};

struct WEdge {
    int to;
    ll w;
};

template<typename VType_ = None, typename EType_ = Edge>
struct Graph {
	using VType = VType_;
	using EType = EType_;
	vector<VType> v;
	vector<vector<EType>> g;
	
	Graph(int n): v(n), g(n) {};
	int addV() {
        int id = v.size();
        v.emplace_back();
        g.emplace_back();
        return id;
    }
	
	int addOEdge(int u, int v, const EType& newE) {
		g[u].push_back(newE);
		g[u].back().to = v;
		return ((int)g[u].size())-1;
	}
	
	void addEdge(int u, int v, const EType& newE) {
		addOEdge(u, v, newE);
		addOEdge(v, u, newE);
	}
};

template<typename VType_ = None, typename EType_ = Edge, typename EIdType_ = char>
struct Bor {
	using VType = VType_;
	using EType = EType_;
	using EIdType = EIdType_;
	vector<VType> v;
	vector<map<EIdType, EType>> g;
	
	Bor(int n): v(n), g(n) {};
	int addV() {
        int id = v.size();
        v.emplace_back();
        g.emplace_back();
        return id;
    }
	
	void addOEdge(int u, int v, const EIdType& newEId, const EType& newE) {
		assert(g[u].count(newEId)==0);
		g[u][newEId] = newE;
		g[u][newEId].to = v;
	}
	
	void addEdge(int u, int v, const EType& newE) {
		addOEdge(u, v, newE);
		addOEdge(v, u, newE);
	}
}