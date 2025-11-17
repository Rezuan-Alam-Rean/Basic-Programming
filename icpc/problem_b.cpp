#include <bits/stdc++.h>
using namespace std;

inline long long computeGcd(long long a, long long b) {
    return b == 0 ? a : __gcd(a, b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<long long> a(n);
        unordered_map<long long, int> freq;
        
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            freq[a[i]]++;
        }
        
        // Get unique values
        vector<long long> uniqueVals;
        uniqueVals.reserve(freq.size());
        for (auto& p : freq) {
            uniqueVals.push_back(p.first);
        }
        
        long long maxGcd = 0;
        long long count = 0;
        
        // Check all unique pairs of values
        int m = uniqueVals.size();
        for (int i = 0; i < m; i++) {
            long long x = uniqueVals[i];
            long long freqX = freq[x];
            for (int j = 0; j < m; j++) {
                long long y = uniqueVals[j];
                long long xorVal = x ^ y;
                long long andVal = x & y;
                long long g = andVal == 0 ? xorVal : computeGcd(xorVal, andVal);
                
                if (g > maxGcd) {
                    maxGcd = g;
                    count = (long long)freqX * freq[y];
                } else if (g == maxGcd) {
                    count += (long long)freqX * freq[y];
                }
            }
        }
        
        cout << maxGcd << " " << count << "\n";
    }
    
    return 0;
}
