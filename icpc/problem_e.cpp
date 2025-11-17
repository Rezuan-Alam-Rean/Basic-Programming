#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

// Convert n to binary representation (LSB first for easier processing)
vector<int> toBinaryLSB(long long n) {
    vector<int> bits;
    if (n == 0) {
        bits.push_back(0);
        return bits;
    }
    while (n > 0) {
        bits.push_back(n % 2);
        n /= 2;
    }
    return bits;
}


map<tuple<int, long long, bool>, long long> memo;

long long solve(int pos, long long carry, bool isLeadingZero, int k, const vector<int>& binary) {
    // Base case: processed all bits
    if (pos >= (int)binary.size()) {
        // Need carry to be 0 and have non-zero representation
        if (carry > 0) return 0;
        return isLeadingZero ? 0 : 1;
    }
    
    // Prune: if carry is too large, it's impossible
    // Maximum possible remaining value is k * (2^(remaining_bits) - 1)
    int remainingBits = binary.size() - pos;
    long long maxPossible = (1LL << remainingBits) - 1;
    if (carry > k * maxPossible) return 0;
    
    // Check memoization
    auto key = make_tuple(pos, carry, isLeadingZero);
    if (memo.count(key)) {
        return memo[key];
    }
    
    long long result = 0;
    int targetBit = binary[pos];
    
    
    for (int digit = 0; digit <= k; digit++) {
        long long totalAtThisPos = carry + digit;
        int currentBit = totalAtThisPos % 2;
        long long newCarry = totalAtThisPos / 2;
        
        // Check if bit matches
        if (currentBit != targetBit) continue;
        
        // Handle leading zeros
        bool newIsLeadingZero = isLeadingZero && (digit == 0);
        
        // If still leading zero and not last position, continue
        if (newIsLeadingZero && pos < (int)binary.size() - 1) {
            result = (result + solve(pos + 1, newCarry, true, k, binary)) % MOD;
        } else {
            // Non-zero digit or last position
            result = (result + solve(pos + 1, newCarry, false, k, binary)) % MOD;
        }
    }
    
    return memo[key] = result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    while (T--) {
        long long n;
        int k;
        cin >> n >> k;
        
        // Convert n to binary (LSB first)
        vector<int> binary = toBinaryLSB(n);
        
        // Clear memoization for new test case
        memo.clear();
        
        // Solve using digit DP (start from LSB with no carry)
        long long answer = solve(0, 0, true, k, binary);
        
        cout << answer << "\n";
    }
    
    return 0;
}

