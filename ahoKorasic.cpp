struct VertType {
    int par;
    char parCh;
    int link = -1;
    vector<int> ends;
    bool isLeaf;
    int up = -1;
};

template<typename Graph>
void addString (Graph& g, const string& s, int lineId) {
    int v = 0;
    for (size_t i=0; i<s.length(); ++i) {
        char c = s[i];
        if (!g.g[v].count(c)){
            int newV = g.addV();
            g.v[newV].par = v;
            g.v[newV].parCh = c;
            g.g[v][c].to = newV;
        }
        v = g.g[v][c].to;
    }
    g.v[v].ends.push_back(lineId);
    g.v[v].isLeaf = true;
}

template<typename Graph>
int go (Graph& g, int v, char c);

template<typename Graph>
int getLink (Graph& g, int v) {
    if (g.v[v].link == -1) {
        if (v == 0 || g.v[v].par == 0) {
            g.v[v].link = 0;
        } else {
            g.v[v].link = go(g, getLink(g, g.v[v].par), g.v[v].parCh);
        }
    }
    return g.v[v].link;
}

template<typename Graph>
int go (Graph& g, int v, char c) {
    if (!g.g[v].count(c))
        g.g[v][c].to = v==0 ? 0 : go (g, getLink(g, v), c);
    return g.g[v][c].to;
}

template<typename Graph>
int getUp(Graph& g, int v) {
    if (g.v[v].up == -1) {
        int suf = getLink(g, v);
        if (g.v[suf].isLeaf) {
            g.v[v].up = suf;
        } else if (suf == 0) {
            g.v[v].up = 0;
        } else {
            g.v[v].up = getUp(g, getLink(g, v));
        }
    }
    return g.v[v].up;
}


//usage
Graph<VertType, Edge, None, char> g;
int v0 = g.addV();
g.v[v0].par = g.v[v0].up = g.v[v0].link = -1;
//
addString(g, cur, i);
strLens[i] = cur.size();

int v = 0;
for (int i=0;i<s0.size();i++) {
    v = go(g, v, s0[i]);
    vector<int> strs;
    int tmp = v;

    while (true) {
        strs.insert(strs.end(), g.v[tmp].ends.begin(), g.v[tmp].ends.end());
        if (tmp==0) break;
        tmp = getUp(g, tmp);
    }
    for (int j=0;j<strs.size();j++) {
        poses[strs[j]].push_back(i-strLens[strs[j]]+1);
    }
}