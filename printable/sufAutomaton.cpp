struct SAState {
    int len, link;
    bool isTerm = false;
};

template<typename SAState = SAState, typename CharType = char>
struct SufAutomaton {
    Bor<SAState, Edge, CharType> g;
    int last = 0;

    SufAutomaton() {
        int v = g.addV();
        g.v[v].len = 0;
        g.v[v].link = -1;
    }

    void addC(CharType c) {
        int cur = g.addV();
        g.v[cur].len = g.v[last].len + 1;
        int p;
        for (p=last; p!=-1 && !g.g[p].count(c); p=g.v[p].link)
            g.g[p][c].to = cur;
        if (p == -1)
            g.v[cur].link = 0;
        else {
            int q = g.g[p][c].to;
            if (g.v[p].len + 1 == g.v[q].len)
                g.v[cur].link = q;
            else {
                int clone = g.addV();
                g.v[clone].len = g.v[p].len + 1;
                g.g[clone] = g.g[q];
                g.v[clone].link = g.v[q].link;
                for (; p!=-1 && g.g[p][c].to==q; p=g.v[p].link)
                    g.g[p][c].to = clone;
                g.v[q].link = g.v[cur].link = clone;
            }
        }
        last = cur;
    }

    void markTerminalVerts() {
        int cur = last;
        while (cur!=-1) {
            g.v[cur].isTerm = true;
            cur = g.v[cur].link;
        }
    }
};