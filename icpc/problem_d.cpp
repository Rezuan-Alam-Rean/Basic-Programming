#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent, size;
    
    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
    }
    
    int getSize(int x) {
        return size[find(x)];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;
        
        string clowders;
        cin >> clowders;
        
        // Count initial clowder sizes
        map<char, int> clowderSize;
        for (char c : clowders) {
            clowderSize[c]++;
        }
        
        // Map clowder to index
        map<char, int> clowderToIdx;
        vector<char> idxToClowder;
        int idx = 0;
        for (auto& p : clowderSize) {
            clowderToIdx[p.first] = idx;
            idxToClowder.push_back(p.first);
            idx++;
        }
        
        int M;
        cin >> M;
        
        vector<pair<int, int>> events(M);
        for (int i = 0; i < M; i++) {
            cin >> events[i].first >> events[i].second;
            events[i].first--; // 0-indexed
            events[i].second--;
        }
        
        int Q;
        cin >> Q;
        
        cout << "Case " << t << ":\n";
        
        for (int q = 0; q < Q; q++) {
            int U, V;
            cin >> U >> V;
            U--; V--; // 0-indexed
            
            // Find clowders in query range
            set<char> queryClowders;
            for (int pos = U; pos <= V; pos++) {
                queryClowders.insert(clowders[pos]);
            }
            
            // Find events that can help merge clowders in query range
            // An event helps if it contains at least one clowder from query range
            vector<int> relevantEvents;
            for (int i = 0; i < M; i++) {
                int L = events[i].first;
                int R = events[i].second;
                
                // Check if this event contains any query clowder
                bool relevant = false;
                for (int pos = L; pos <= R; pos++) {
                    if (queryClowders.count(clowders[pos])) {
                        relevant = true;
                        break;
                    }
                }
                if (relevant) {
                    relevantEvents.push_back(i);
                }
            }
            
            // Build graph: events are connected if they share at least one clowder type
            // This is because if two events share a clowder, using both merges all their clowders
            int numEvents = relevantEvents.size();
            vector<vector<int>> eventGraph(numEvents);
            vector<set<char>> eventClowderTypes(numEvents);
            
            // Precompute clowder types for each event
            for (int i = 0; i < numEvents; i++) {
                int L = events[relevantEvents[i]].first;
                int R = events[relevantEvents[i]].second;
                for (int pos = L; pos <= R; pos++) {
                    eventClowderTypes[i].insert(clowders[pos]);
                }
            }
            
            // Connect events that share at least one clowder type
            for (int i = 0; i < numEvents; i++) {
                for (int j = i + 1; j < numEvents; j++) {
                    // Check if events share any clowder type
                    bool shareClowder = false;
                    for (char c : eventClowderTypes[i]) {
                        if (eventClowderTypes[j].count(c)) {
                            shareClowder = true;
                            break;
                        }
                    }
                    if (shareClowder) {
                        eventGraph[i].push_back(j);
                        eventGraph[j].push_back(i);
                    }
                }
            }
            
            // Find connected components of events using DFS
            vector<bool> visited(numEvents, false);
            int maxSize = 0;
            
            // Also consider no events
            map<char, int> noEventSize;
            for (int pos = U; pos <= V; pos++) {
                noEventSize[clowders[pos]]++;
            }
            for (auto& p : noEventSize) {
                maxSize = max(maxSize, p.second);
            }
            
            // For each connected component of events
            for (int start = 0; start < numEvents; start++) {
                if (visited[start]) continue;
                
                // DFS to find all events in this component
                vector<int> component;
                stack<int> st;
                st.push(start);
                visited[start] = true;
                
                while (!st.empty()) {
                    int curr = st.top();
                    st.pop();
                    component.push_back(curr);
                    
                    for (int next : eventGraph[curr]) {
                        if (!visited[next]) {
                            visited[next] = true;
                            st.push(next);
                        }
                    }
                }
                
                // Merge all clowders in events of this component
                DSU dsu(clowderToIdx.size());
                set<char> mergedClowders;
                
                for (int eventIdx : component) {
                    // Use precomputed clowder types for this event
                    set<char>& eventClowders = eventClowderTypes[eventIdx];
                    
                    // Merge all these clowder types (all cats with these types merge)
                    vector<int> clowderIndices;
                    for (char c : eventClowders) {
                        clowderIndices.push_back(clowderToIdx[c]);
                        mergedClowders.insert(c);
                    }
                    
                    // Unite all clowders in this event
                    for (int j = 1; j < clowderIndices.size(); j++) {
                        dsu.unite(clowderIndices[0], clowderIndices[j]);
                    }
                }
                
                // Calculate total size of merged components
                // For each merged clowder type, add its original size
                map<int, int> componentTotalSize;
                for (char c : mergedClowders) {
                    int clowderIdx = clowderToIdx[c];
                    int root = dsu.find(clowderIdx);
                    componentTotalSize[root] += clowderSize[c];
                }
                
                // Find maximum component size that includes query clowders
                for (char c : queryClowders) {
                    if (mergedClowders.count(c)) {
                        int clowderIdx = clowderToIdx[c];
                        int root = dsu.find(clowderIdx);
                        maxSize = max(maxSize, componentTotalSize[root]);
                    }
                }
            }
            
            cout << maxSize << "\n";
        }
    }
    
    return 0;
}

