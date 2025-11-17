#include <bits/stdc++.h>
using namespace std;

void bfs(int start, vector<vector<int>>& graph, bitset<10001>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, M;
        cin >> N >> M;
        
        vector<vector<int>> graph(N + 1);
        vector<vector<int>> reverseGraph(N + 1);
        
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            reverseGraph[v].push_back(u);
        }
        
        int Q;
        cin >> Q;
        
        cout << "Case " << t << ":\n";
        
        for (int q = 0; q < Q; q++) {
            int U, V;
            cin >> U >> V;
            
            // Check if V is reachable from U using bitset for efficiency
            bitset<10001> visitedFromU;
            bfs(U, graph, visitedFromU);
            
            if (visitedFromU[V]) {
                cout << "0\n";
                continue;
            }
            
            // Find all nodes that can reach V (backward set)
            bitset<10001> visitedToV;
            bfs(V, reverseGraph, visitedToV);
            
            // Build compact lists for two-pointer approach
            vector<int> forwardList, backwardList;
            forwardList.reserve(N);
            backwardList.reserve(N);
            
            for (int i = 1; i <= N; i++) {
                if (visitedFromU[i]) forwardList.push_back(i);
                if (visitedToV[i]) backwardList.push_back(i);
            }
            
            // Two pointers to find minimum |X - Y|
            int minCost = INT_MAX;
            int i = 0, j = 0;
            
            while (i < forwardList.size() && j < backwardList.size()) {
                minCost = min(minCost, abs(forwardList[i] - backwardList[j]));
                if (minCost == 0) break; // Early exit
                
                if (forwardList[i] < backwardList[j]) {
                    i++;
                } else {
                    j++;
                }
            }
            
            cout << minCost << "\n";
        }
    }
    
    return 0;
}

