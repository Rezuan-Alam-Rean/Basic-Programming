#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
#define yes cout << "YES\n";
#define no cout << "NO\n";
#define endl '\n'
#define gcd(a, b) __gcd(a, b)
#define lcm(a, b) ((a / gcd(a, b)) * b)
#define e4 signed main()
#define Infinite void
#ifdef LOKAL
#include "Debug_Template.h"
#else
#define HERE
#define debug(args...)
#endif
using namespace std;
// using namespace __gnu_pbds;
// template <typename T> using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const ll mod = 1e9 + 7;
const int MAXN = 10005; 
vector<bitset<MAXN>> can_reach;
vector<bitset<MAXN>> rev_reach;
vector<int> adj[MAXN];
vector<int> adj_rev[MAXN];
vector<int> in_degree;
vector<int> rev_in_degree;
vector<int> topo_order;
vector<int> rev_topo_order;

void topological_sort(int N, vector<int> graph[], vector<int>& in_deg, vector<int>& order) {
    order.clear();
    queue<int> q;
    for (int i = 1; i <= N; i++) {
        if (in_deg[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);

        for (int v : graph[u]) {
            in_deg[v]--;
            if (in_deg[v] == 0) {
                q.push(v);
            }
        }
    }
}

void compute_reachability(int N, vector<int> graph[], vector<bitset<MAXN>>& reach, vector<int>& order) {
    for (int i = 1; i <= N; i++) {
        reach[i].reset();
    }
    for (int i = N - 1; i >= 0; i--) {
        int u = order[i];
        reach[u][u] = 1;
        for (int v : graph[u]) {
            reach[u] |= reach[v];
        }
    }
}

Infinite Void() {
    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        adj[i].clear();
        adj_rev[i].clear();
    }
    
    in_degree.assign(N + 1, 0);
    rev_in_degree.assign(N + 1, 0);
    can_reach.assign(N + 1, bitset<MAXN>());
    rev_reach.assign(N + 1, bitset<MAXN>());

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
        in_degree[v]++;
        rev_in_degree[u]++;
    }

    topological_sort(N, adj, in_degree, topo_order);
    compute_reachability(N, adj, can_reach, topo_order);

    topological_sort(N, adj_rev, rev_in_degree, rev_topo_order);
    compute_reachability(N, adj_rev, rev_reach, rev_topo_order);

    int Q;
    cin >> Q;
    while (Q--) {
        int U, V;
        cin >> U >> V;
        if (can_reach[U].test(V)) {
            cout << 0 << endl;
        } else {
            vector<int> list_R;
            vector<int> list_P;
            for (int i = 1; i <= N; i++) {
                if (can_reach[U].test(i)) {
                    list_R.push_back(i);
                }
                if (rev_reach[V].test(i)) {
                    list_P.push_back(i);
                }
            }
            int min_cost = INT_MAX;
            int i = 0, j = 0;
            while (i < list_R.size() && j < list_P.size()) {
                min_cost = min(min_cost, abs(list_R[i] - list_P[j]));
                if (list_R[i] < list_P[j]) {
                    i++;
                } else {
                    j++;
                }
            }
            cout << min_cost << endl;
        }
    }
}

e4{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case " << i << ":" << endl;
        Void();
    }
    return 0;
}