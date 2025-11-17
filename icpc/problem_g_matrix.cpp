#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, m;
        cin >> n >> m;
        
        vector<vector<long long>> mat(n, vector<long long>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> mat[i][j];
            }
        }
        
        vector<long long> rowXor(n, 0);
        vector<long long> colXor(m, 0);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                rowXor[i] ^= mat[i][j];
                colXor[j] ^= mat[i][j];
            }
        }
        
        long long totalDanger = 0;
        for (long long x : rowXor) totalDanger += x;
        for (long long x : colXor) totalDanger += x;
        
        long long minDanger = totalDanger;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                long long oldRow = rowXor[i];
                long long oldCol = colXor[j];
                long long bestSum = oldRow ^ oldCol;
                long long newTotal = totalDanger - oldRow - oldCol + bestSum;
                minDanger = min(minDanger, newTotal);
            }
        }
        
        cout << minDanger << "\n";
    }
    
    return 0;
}

