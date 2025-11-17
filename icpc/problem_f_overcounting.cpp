#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = s[i] - '0';
        }
        sort(a.begin(), a.end());
        
        long long total = 0;
        do {
            vector<int> f1(n, 0);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < i; j++) {
                    if (a[j] > a[i]) f1[i]++;
                }
            }
            
            vector<int> f2(n, 0);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < i; j++) {
                    if (f1[j] > f1[i]) f2[i]++;
                }
            }
            
            int g = 0;
            for (int x : f2) g = (g + x) % MOD;
            total = (total + g) % MOD;
        } while (next_permutation(a.begin(), a.end()));
        
        cout << total << "\n";
    }
    
    return 0;
}
