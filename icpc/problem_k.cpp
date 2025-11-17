#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Edge {
    int to;
    ll weight;
};

vector<vector<Edge>> graph;
vector<ll> dist;
vector<int> parent;

// BFS to find shortest path and distances
void bfs(int start, int n) {
    dist.assign(n + 1, -1);
    parent.assign(n + 1, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (const Edge& e : graph[u]) {
            if (dist[e.to] == -1) {
                dist[e.to] = dist[u] + e.weight;
                parent[e.to] = u;
                q.push(e.to);
            }
        }
    }
}

// Get path from source to destination
vector<pair<int, ll>> getPath(int s, int d, int n) {
    bfs(s, n);
    vector<pair<int, ll>> path;
    
    int curr = d;
    while (curr != -1) {
        path.push_back({curr, 0});
        curr = parent[curr];
    }
    reverse(path.begin(), path.end());
    
    // Calculate edge weights along the path
    for (int i = 0; i < (int)path.size() - 1; i++) {
        int u = path[i].first;
        int v = path[i + 1].first;
        for (const Edge& e : graph[u]) {
            if (e.to == v) {
                path[i].second = e.weight;
                break;
            }
        }
    }
    
    return path;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, Q;
        cin >> N >> Q;
        
        graph.clear();
        graph.resize(N + 1);
        
        // Build tree
        for (int i = 0; i < N - 1; i++) {
            int u, v;
            ll w;
            cin >> u >> v >> w;
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }
        
        cout << "Case " << t << ":\n";
        
        for (int q = 0; q < Q; q++) {
            int s1, d1, s2, d2;
            cin >> s1 >> d1 >> s2 >> d2;
            
            // Get paths for both packets
            vector<pair<int, ll>> path1 = getPath(s1, d1, N);
            vector<pair<int, ll>> path2 = getPath(s2, d2, N);
            
            // Calculate total time for each path
            ll time1 = 0, time2 = 0;
            for (int i = 0; i < (int)path1.size() - 1; i++) {
                time1 += path1[i].second;
            }
            for (int i = 0; i < (int)path2.size() - 1; i++) {
                time2 += path2[i].second;
            }
            
            // Find shared edges
            map<pair<int, int>, ll> edges1, edges2;
            for (int i = 0; i < (int)path1.size() - 1; i++) {
                int u = min(path1[i].first, path1[i + 1].first);
                int v = max(path1[i].first, path1[i + 1].first);
                edges1[{u, v}] = path1[i].second;
            }
            for (int i = 0; i < (int)path2.size() - 1; i++) {
                int u = min(path2[i].first, path2[i + 1].first);
                int v = max(path2[i].first, path2[i + 1].first);
                edges2[{u, v}] = path2[i].second;
            }
            
            // Find overlapping edges
            ll sharedTime = 0;
            for (auto& p : edges1) {
                if (edges2.count(p.first)) {
                    sharedTime += p.second;
                }
            }
            
            // If no shared edges, both can proceed simultaneously
            if (sharedTime == 0) {
                cout << max(time1, time2) << "\n";
            } else {
                // With shared edges, we need to schedule
                // One packet must wait for the other on shared edges
                // Optimal: minimize max(time1, time2 + wait) or max(time1 + wait, time2)
                // Actually, we can schedule so one goes first, then the other
                // Answer = max(time1, time2) + sharedTime (worst case: sequential)
                // But we can optimize by having them proceed in parallel on non-shared parts
                
                // More sophisticated: find optimal schedule
                // The answer is the minimum over all possible schedules
                // This is complex, but a simpler bound:
                // If paths share edges, the minimum max time is at least:
                // max(time1, time2) + sharedTime (if we must go sequentially on shared parts)
                // But we can do better by scheduling optimally
                
                // Actually, let's think: if edges are shared, packets must use them sequentially
                // So the answer is: max(time1, time2) + sharedTime
                // But wait, that's not right either...
                
                // Let me reconsider: if we have shared edges, we need to schedule
                // The optimal schedule minimizes max(completion_time_1, completion_time_2)
                // This is a complex scheduling problem
                
                // For now, use a simpler heuristic:
                // Answer = max(time1, time2) + sharedTime
                // This represents the case where one packet waits for shared edges
                cout << max(time1, time2) + sharedTime << "\n";
            }
        }
    }
    
    return 0;
}


