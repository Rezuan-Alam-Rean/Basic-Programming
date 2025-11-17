#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

long long modInverse(long long a, long long mod) {
    return modPow(a, mod - 2, mod);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    while (T--) {
        int N, K;
        cin >> N >> K;
        
        vector<string> perception(N);
        for (int i = 0; i < N; i++) {
            cin >> perception[i];
        }
        
        // Generate all permutations
        vector<int> perm(N);
        iota(perm.begin(), perm.end(), 0);
        
        long long totalScore = 0;
        
        do {
            // Calculate unhappiness for each person in this permutation
            vector<int> unhappiness(N, 0);
            
            for (int i = 0; i < N; i++) {
                int person = perm[i];
                // Count people ahead (positions 0 to i-1) that this person thinks are weaker
                for (int j = 0; j < i; j++) {
                    int aheadPerson = perm[j];
                    if (perception[person][aheadPerson] == 'W') {
                        unhappiness[person]++;
                    }
                }
            }
            
            // Sort unhappiness scores in ascending order
            sort(unhappiness.begin(), unhappiness.end());
            
            // Sum the largest K scores
            long long score = 0;
            for (int i = N - K; i < N; i++) {
                score = (score + unhappiness[i]) % MOD;
            }
            
            totalScore = (totalScore + score) % MOD;
            
        } while (next_permutation(perm.begin(), perm.end()));
        
        // Expected value = totalScore / N!
        long long fact = 1;
        for (int i = 1; i <= N; i++) {
            fact = (fact * i) % MOD;
        }
        
        long long expected = (totalScore * modInverse(fact, MOD)) % MOD;
        cout << expected << "\n";
    }
    
    return 0;
}

