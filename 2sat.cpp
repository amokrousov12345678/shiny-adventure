//нумерация переменных с 1, знак определяет с отрицанием или без
struct Solver2SAT {
    vector<int> vals;
    bool solvable = true;

    Solver2SAT(int n, vector<pair<int,int>>& disj): vals(n+1, -1) {
        Graph<None, Edge> g(2*n);
        for (auto& it: disj) {
            int u = -it.first;
            int v = it.second;
            if (u<0) {
                u = n+(-u);
            }
            if (v<0) {
                v = n+(-v);
            }
            u--;
            v--;
            g.addOEdge(u,v, {});

            u = -it.second;
            v = it.first;
            if (u<0) {
                u = n+(-u);
            }
            if (v<0) {
                v = n+(-v);
            }
            u--;
            v--;
            g.addOEdge(u,v, {});
        }
        //vector<pair<int,int>>().swap(disj);
        StrongComponents<decltype(g)> scc(g);
        for (int i=0;i<n;i++) {
            int x = i;
            int notX = n+i;
            int sccX = scc.vertComp[x];
            int sccNotX = scc.vertComp[notX];
            if (sccX==sccNotX) {
                solvable = false;
                continue;
            }
            if (sccX<sccNotX) {
                vals[i+1] = 0;
            } else {
                vals[i+1] = 1;
            }
        }
    }
};