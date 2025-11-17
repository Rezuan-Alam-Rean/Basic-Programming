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
    
    int N;
    cin >> N;
    
    vector<long long> A(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    
    int Q;
    cin >> Q;
    
    for (int q = 0; q < Q; q++) {
        int L, R, K;
        cin >> L >> R >> K;
        
        int len = R - L + 1;
        vector<long long> values;
        for (int i = L; i <= R; i++) {
            values.push_back(A[i]);
        }
        
        // Apply K increment moves optimally
        // Alice wants to maximize expected value
        // Strategy: distribute increments to maximize the equilibrium value
        
        // Sort to help with distribution
        vector<pair<long long, int>> indexed;
        for (int i = 0; i < len; i++) {
            indexed.push_back({values[i], i});
        }
        
        // Distribute K increments optimally
        // Use greedy: increment values that give best marginal improvement
        // For this game, we want to maximize the equilibrium expected value
        // which involves balancing the values
        
        // Simple strategy: distribute evenly or to maximize sum
        // Actually, for Nash equilibrium, we need to think about the game value
        
        // Distribute K increments greedily to maximize expected payoff
        long long remaining = K;
        while (remaining > 0) {
            // Find index that gives best improvement
            int bestIdx = 0;
            for (int i = 1; i < len; i++) {
                if (values[i] < values[bestIdx]) {
                    bestIdx = i;
                }
            }
            values[bestIdx]++;
            remaining--;
        }
        
        // In Nash equilibrium for this zero-sum game:
        // Both players choose indices with probabilities proportional to A[i]
        // p_i = A[i] / Σ A[j]
        // Expected value = Σ_i p_i * A[i] * (1 - p_i)
        //                = Σ_i (A[i]/S) * A[i] * (1 - A[i]/S)
        //                = (1/S) * Σ_i A[i]² - (1/S²) * Σ_i A[i]³
        
        long long sumValues = 0;
        long long sumSquares = 0;
        long long sumCubes = 0;
        
        for (long long v : values) {
            sumValues = (sumValues + v) % MOD;
            sumSquares = (sumSquares + (v * v) % MOD) % MOD;
            sumCubes = (sumCubes + ((v * v) % MOD * v) % MOD) % MOD;
        }
        
        if (sumValues == 0) {
            cout << "0\n";
            continue;
        }
        
        // Expected value = (sumSquares / sumValues) - (sumCubes / sumValues²)
        long long invSum = modInverse(sumValues, MOD);
        long long invSumSq = (invSum * invSum) % MOD;
        
        long long term1 = (sumSquares * invSum) % MOD;
        long long term2 = (sumCubes * invSumSq) % MOD;
        long long answer = (term1 - term2 + MOD) % MOD;
        
        cout << answer << "\n";
    }
    
    return 0;
}

