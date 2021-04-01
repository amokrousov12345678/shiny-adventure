SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Werror -fsanitize=address -fsanitize=undefined")

// (clock() - start) * 1.0 / CLOCKS_PER_SEC;

#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize("Ofast")//Comment optimisations for interactive problems (use endl)
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct None {};

struct Graph {
	vector<vector<int>> g;
}

const int INFi = 1e9;
const ll INFll = 1e18;

using ld = double;

double eps = 1e-9;
const ld pi = acos(-1);

namespace std {
    template<typename a, typename b>
    struct hash<std::pair<a, b> > {
    public:
        hash() {}
        size_t operator()(const std::pair<a, b> &p) const {
            return hash<a>()(p.first) + hash<b>()(p.second)*998242353;
        }
    };
};

void solve() {
   
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    cout << setprecision(15) << fixed;
    int t = 1;
    //cin >> t;
    for (int i=0;i<t;i++)
		solve();
    return 0;
}