#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

long long computeG(long long y) {
    if (y == 0) return 0;
    
    long long count = 0;
    
    for (int k = 1; k <= 18; k++) {
        long long pow10k = 1;
        for (int i = 0; i < k - 1; i++) pow10k *= 10;
        long long pow10km1 = (k > 1) ? (pow10k / 10) : 1;
        
        if (k == 1) {
            for (int d = 1; d <= 9; d++) {
                if ((y - d) % 9 == 0) {
                    long long a = (y - d) / 9;
                    if (a >= 1) {
                        count++;
                    }
                }
            }
        } else {
            if (k == 2 && y % 10 == 0) {
                long long a = y / 10;
                if (a >= 1 && a <= 9) {
                    count += 10;
                }
            }
            
            long long factor = 9 * pow10km1;
            for (int d = 0; d <= 9; d++) {
                long long rem = y - d * pow10km1;
                if (rem >= 0 && rem % factor == 0) {
                    long long L = rem / factor;
                    if (L >= 0) {
                        long long rMax = min(pow10km1 - 1, 10000LL);
                        for (long long r = 0; r <= rMax; r++) {
                            string LStr = to_string(L);
                            string rStr = to_string(r);
                            while ((int)rStr.length() < k - 1) {
                                rStr = "0" + rStr;
                            }
                            if ((int)rStr.length() == k - 1) {
                                string xStr = LStr + to_string(d) + rStr;
                                if (xStr.length() >= 2 && xStr[0] != '0') {
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return count % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    string a;
    cin >> a;
    
    int q;
    cin >> q;
    
    while (q--) {
        int p, d;
        cin >> p >> d;
        a[n - p] = '0' + d;
        
        long long y = 0;
        for (char c : a) {
            y = y * 10 + (c - '0');
        }
        
        cout << computeG(y) << "\n";
    }
    
    return 0;
}
