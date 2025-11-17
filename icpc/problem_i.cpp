#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;
        
        vector<long long> A(N + 1);
        for (int i = 1; i <= N; i++) {
            cin >> A[i];
        }
        
        // Precompute prefix maximums (max height from front to position i)
        vector<long long> prefixMax(N + 1, 0);
        for (int i = 1; i <= N; i++) {
            prefixMax[i] = max(prefixMax[i - 1], A[i]);
        }
        
        // Precompute suffix minimums (min height from position i to back)
        vector<long long> suffixMin(N + 2, LLONG_MAX);
        for (int i = N; i >= 1; i--) {
            suffixMin[i] = min(suffixMin[i + 1], A[i]);
        }
        
        // Find the frontmost kind person
        int kindPerson = -1;
        for (int i = 1; i <= N; i++) {
            // Check if strictly taller than everyone in front
            bool tallerThanFront = (i == 1) || (A[i] > prefixMax[i - 1]);
            
            // Check if strictly shorter than everyone behind
            bool shorterThanBack = (i == N) || (A[i] < suffixMin[i + 1]);
            
            if (tallerThanFront && shorterThanBack) {
                kindPerson = i;
                break; // Found frontmost kind person
            }
        }
        
        cout << "Case " << t << ": ";
        if (kindPerson == -1) {
            cout << "Humanity is doomed!\n";
        } else {
            cout << kindPerson << "\n";
        }
    }
    
    return 0;
}


