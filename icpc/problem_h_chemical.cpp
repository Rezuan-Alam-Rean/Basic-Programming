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
        
        set<long long> chemicals;
        for (int i = 0; i < n; i++) {
            long long c;
            cin >> c;
            chemicals.insert(c);
        }
        
        map<pair<long long, long long>, long long> reactions;
        for (int i = 0; i < m; i++) {
            long long x, y, z;
            cin >> x >> y >> z;
            if (x > y) swap(x, y);
            reactions[{x, y}] = z;
        }
        
        bool changed = true;
        while (changed) {
            changed = false;
            set<long long> newChemicals = chemicals;
            
            for (auto it1 = chemicals.begin(); it1 != chemicals.end(); ++it1) {
                for (auto it2 = it1; it2 != chemicals.end(); ++it2) {
                    long long x = *it1;
                    long long y = *it2;
                    if (x > y) swap(x, y);
                    
                    if (reactions.count({x, y})) {
                        long long z = reactions[{x, y}];
                        if (chemicals.find(z) == chemicals.end()) {
                            newChemicals.insert(z);
                            changed = true;
                        }
                    }
                }
            }
            
            chemicals = newChemicals;
        }
        
        cout << chemicals.size() << "\n";
    }
    
    return 0;
}

