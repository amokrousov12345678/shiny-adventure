struct DSU {
    vector<int> parent;
    vector<int> rank;
    DSU(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i=0;i<n;i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int getSetId(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = getSetId(parent[v]);
    }

    void connect(int a, int b) {
        a = getSetId(a);
        b = getSetId(b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap (a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                ++rank[a];
        }
    }

    bool isConnected(int a, int b) {
        return getSetId(a) == getSetId(b);
    }
    
    int addV() {
        int v = parent.size();
        parent.push_back(v);
        rank.push_back(0);
        return v;
    }
};