#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 1000001;

vector<bool> isPrime;
vector<int> primes;
vector<long long> fact, invFact;
vector<int> mobius;

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

void precomputePrimes() {
    isPrime.assign(MAXN, true);
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i < MAXN; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j < MAXN; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

void precomputeFactorials() {
    fact.resize(MAXN);
    invFact.resize(MAXN);
    
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i-1] * i) % MOD;
    }
    
    invFact[MAXN-1] = modPow(fact[MAXN-1], MOD-2, MOD);
    for (int i = MAXN-2; i >= 0; i--) {
        invFact[i] = (invFact[i+1] * (i+1)) % MOD;
    }
}

void precomputeMobius() {
    mobius.assign(MAXN, 1);
    vector<bool> isSquareFree(MAXN, true);
    vector<int> primeCount(MAXN, 0);
    
    for (int p : primes) {
        for (int j = p; j < MAXN; j += p) {
            primeCount[j]++;
        }
        for (long long j = (long long)p * p; j < MAXN; j += (long long)p * p) {
            isSquareFree[j] = false;
        }
    }
    
    for (int i = 2; i < MAXN; i++) {
        if (!isSquareFree[i]) {
            mobius[i] = 0;
        } else {
            mobius[i] = (primeCount[i] % 2 == 0) ? 1 : -1;
        }
    }
}

long long nCr(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (n < 0) return 0;
    return (fact[n] * ((invFact[k] * invFact[n-k]) % MOD)) % MOD;
}

vector<int> getPrimeDivisors(int n) {
    vector<int> result;
    int temp = n;
    for (int p : primes) {
        if (p * p > temp) break;
        if (temp % p == 0) {
            result.push_back(p);
            while (temp % p == 0) {
                temp /= p;
            }
        }
    }
    if (temp > 1) {
        result.push_back(temp);
    }
    return result;
}

vector<int> getDivisors(int n) {
    vector<int> result;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            result.push_back(i);
            if (i != n / i) {
                result.push_back(n / i);
            }
        }
    }
    return result;
}

long long countPartitionsWithGcd1(int m, int k) {
    if (m < k + 1) return 0;
    
    long long result = 0;
    vector<int> divs = getDivisors(m);
    
    for (int d : divs) {
        int m_d = m / d;
        if (m_d < k + 1) continue;
        long long ways = nCr(m_d - 1, k);
        result = (result + mobius[d] * ways) % MOD;
    }
    
    return (result + MOD) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Precomputation
    precomputePrimes();
    precomputeFactorials();
    precomputeMobius();
    
    int T;
    cin >> T;
    
    while (T--) {
        int n, k;
        cin >> n >> k;
        
        if (k + 1 > n) {
            cout << "0\n";
            continue;
        }
        
        vector<int> primeDivs = getPrimeDivisors(n);
        long long answer = 0;
        
        for (int p : primeDivs) {
            int m = n / p;
            if (m < k + 1) continue;
            answer = (answer + countPartitionsWithGcd1(m, k)) % MOD;
        }
        
        cout << answer << "\n";
    }
    
    return 0;
}

