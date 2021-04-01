int low[maxn], was[maxn], num[maxn], comp_num[maxn], cur;
int n;
vector<int> is_bridge[maxn], back[maxn], comp[maxn];
pair<int, int> stck[maxe];
int ssize, comp_cnt, is_art[maxn];

void add_biedge(int u, int v) {
	back[u].push_back(g[v].size());
	back[v].push_back(g[u].size());
	g[u].push_back(v);
	g[v].push_back(u);
	comp[u].push_back(-1);
	comp[v].push_back(-1);
	is_bridge[u].push_back(0);
	is_bridge[v].push_back(0);
}
void clear() {
	for (int i = 0; i < n; ++i) {
		g[i].clear();
		is_bridge[i].clear();
		back[i].clear();
		comp[i].clear();
	}
	memset(num, -1, sizeof(num));
	memset(was, 0, sizeof(was));
	cur = comp_cnt = ssize = 0;
}

//Articulation points
void dfs(int v, int par) {
	was[v] = 1;
	num[v] = low[v] = cur++;
	int d = 0, maxlo = -1;
	for (int i = 0; i < g[v].size(); ++i) {
		if (g[v][i] == par) continue;
		if (was[g[v][i]]) {
			low[v] = min(low[v], num[g[v][i]]);
			continue;
		}
		dfs(g[v][i], v); ++d;
		maxlo = max(maxlo, low[g[v][i]]);
		low[v] = min(low[v], low[g[v][i]]);
	}
	if (par >= 0) is_art[v] = (maxlo >= num[v]);
	else is_art[v] = (d > 1);
}

//Bridges
void dfs(int v, int par) {
	was[v] = 1;
	num[v] = low[v] = cur++;
	for (int i = 0; i < g[v].size(); ++i) {
		is_bridge[v][i] = 0;
		if (g[v][i] == par) continue;
		if (was[ g[v][i] ]) {
			low[v] = min(low[v], num[ g[v][i] ]);
			continue;
		}
		dfs(g[v][i], v);
		low[v] = min(low[v], low[ g[v][i] ]);
		if (low[ g[v][i] ] > num[v]) is_bridge[v][i] = 1;
	}
}

//strong comps
vector<int> g[maxn]; // <-- input data
int comp[maxn];      // <-- result here ;)

bool visit[maxn];
vector<int> revg[maxn];
vector<int> que, component;
int last_comp_id;

void dfs_fwd(int v) {
    visit[v] = true;
    for (int u : g[v]) if (!visit[u]) dfs_fwd(u);
    que.push_back(v);
}

void dfs_rev(int v) {
    visit[v] = true;
    for (int u : revg[v]) if (!visit[u]) dfs_rev(u);
    component.push_back(v);
}

void tarjan() {
    // add reverse edges
    for (int v = 0; v < maxn; ++v) revg[v].clear();
    for (int v = 0; v < maxn; ++v)
        for (int u : g[v]) 
            revg[u].push_back(v);
    // dfs forward
    memset(visit, 0, sizeof(visit));
    que.clear();
    for (int v = 0; v < maxn; ++v) 
        if (!visit[v]) 
            dfs_fwd(v);
    reverse(que.begin(), que.end());
    // dfs backward
    memset(visit, 0, sizeof(visit));
    for (int v : que) if (!visit[v]) {
        component.clear();
        dfs_rev(v);
        for (int u : component) comp[u] = last_comp_id;
        ++last_comp_id;
    }
}
