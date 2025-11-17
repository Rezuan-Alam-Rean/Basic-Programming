#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;
    
    for (int i = 0; i < N; i++) {
        string input;
        cin >> input;
        
        // Convert input string to actual C string representation
        // Replace \0 sequences with actual null characters
        vector<char> line;
        for (int j = 0; j < (int)input.length(); j++) {
            if (input[j] == '\\' && j + 1 < (int)input.length() && input[j + 1] == '0') {
                // Found \0 sequence, add null character
                line.push_back('\0');
                j++; // Skip the '0'
            } else {
                line.push_back(input[j]);
            }
        }
        // Add implicit null terminator (C automatically adds this)
        line.push_back('\0');
        
        // Calculate strlen: length up to first null character
        int strlen_value = 0;
        for (int j = 0; j < (int)line.size(); j++) {
            if (line[j] == '\0') {
                break;
            }
            strlen_value++;
        }
        
        // Calculate sizeof: total size of the array (including all null characters)
        int sizeof_value = line.size();
        
        cout << sizeof_value << " " << strlen_value << "\n";
    }
    
    return 0;
}


