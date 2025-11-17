#include <bits/stdc++.h>
using namespace std;

struct Node {
    int left, right;
    int color; // 0 = white, 1 = black
    int parent;
    
    Node() : left(-1), right(-1), color(0), parent(-1) {}
};

vector<Node> nodes;

// Find root of tree containing node x
int findRoot(int x) {
    while (nodes[x].parent != -1) {
        x = nodes[x].parent;
    }
    return x;
}

// Find leftmost leftless node using pre-order traversal
int findLeftmostLeftless(int root) {
    if (nodes[root].left == -1) {
        return root;
    }
    
    // Pre-order: root, left, right
    // Use recursion for cleaner pre-order traversal
    function<int(int)> dfs = [&](int node) -> int {
        if (nodes[node].left == -1) {
            return node;
        }
        // Try left subtree first
        int leftResult = dfs(nodes[node].left);
        if (leftResult != -1) return leftResult;
        // Then try right subtree
        if (nodes[node].right != -1) {
            return dfs(nodes[node].right);
        }
        return -1;
    };
    
    int result = dfs(root);
    return (result != -1) ? result : root;
}

// Check if node is a flower root
bool isFlowerRoot(int node) {
    if (nodes[node].color == 1) return false; // Black nodes can't be flower roots
    if (nodes[node].parent == -1) return true; // White node with no parent
    if (nodes[nodes[node].parent].color == 1) return true; // White node with black parent
    return false;
}

// Extract flower structure starting from flower root
// Returns a canonical representation of the flower structure
string getFlowerStructure(int root) {
    if (root == -1) return "()";
    
    // Only traverse white nodes, stop at black nodes
    if (nodes[root].color == 1) return "()";
    
    // Get left and right subtrees
    string left = "()";
    if (nodes[root].left != -1 && nodes[nodes[root].left].color == 0) {
        left = getFlowerStructure(nodes[root].left);
    }
    
    string right = "()";
    if (nodes[root].right != -1 && nodes[nodes[root].right].color == 0) {
        right = getFlowerStructure(nodes[root].right);
    }
    
    return "(" + left + "," + right + ")";
}

// Find all flowers in a tree and count unique shapes
int countUniqueFlowerShapes(int treeRoot) {
    // Find all nodes in this tree using BFS/DFS
    set<int> treeNodes;
    queue<int> q;
    q.push(treeRoot);
    treeNodes.insert(treeRoot);
    
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        
        if (nodes[curr].left != -1 && treeNodes.find(nodes[curr].left) == treeNodes.end()) {
            treeNodes.insert(nodes[curr].left);
            q.push(nodes[curr].left);
        }
        if (nodes[curr].right != -1 && treeNodes.find(nodes[curr].right) == treeNodes.end()) {
            treeNodes.insert(nodes[curr].right);
            q.push(nodes[curr].right);
        }
    }
    
    // Find all flower roots in this tree
    set<string> uniqueShapes;
    
    for (int node : treeNodes) {
        if (isFlowerRoot(node)) {
            string structure = getFlowerStructure(node);
            uniqueShapes.insert(structure);
        }
    }
    
    return uniqueShapes.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, Q;
        cin >> N >> Q;
        
        nodes.clear();
        nodes.resize(N + 1);
        
        // Read node information
        for (int i = 1; i <= N; i++) {
            int left, right, color;
            cin >> left >> right >> color;
            nodes[i].left = left;
            nodes[i].right = right;
            nodes[i].color = color;
            nodes[i].parent = -1;
            
            // Set parent pointers
            if (left != -1) {
                nodes[left].parent = i;
            }
            if (right != -1) {
                nodes[right].parent = i;
            }
        }
        
        cout << "Case " << t << ":\n";
        
        // Process queries
        for (int q = 0; q < Q; q++) {
            int type;
            cin >> type;
            
            if (type == 1) {
                // Type 1: Merge trees
                int X, Y;
                cin >> X >> Y;
                
                int rootX = findRoot(X);
                int leftmostY = findLeftmostLeftless(findRoot(Y));
                
                // Add rootX as left child of leftmostY
                nodes[leftmostY].left = rootX;
                nodes[rootX].parent = leftmostY;
                
            } else if (type == 2) {
                // Type 2: Count unique flower shapes
                int X;
                cin >> X;
                
                int treeRoot = findRoot(X);
                int answer = countUniqueFlowerShapes(treeRoot);
                cout << answer << "\n";
            }
        }
    }
    
    return 0;
}

