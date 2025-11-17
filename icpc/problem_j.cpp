#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const double PERSONAL_ALLOWANCE = 12500.0;
const double BASIC_RATE_LIMIT = 50000.0;
const double HIGHER_RATE_LIMIT = 150000.0;
const double REDUCTION_THRESHOLD = 100000.0;

// Calculate tax for a given income
double calculateTax(double income) {
    if (income <= 0) return 0.0;
    
    double tax = 0.0;
    
    // Calculate taxable income after personal allowance
    double taxable = max(0.0, income - PERSONAL_ALLOWANCE);
    
    // Basic rate (20%): income from 12,500 to 50,000
    double basicAmount = min(taxable, BASIC_RATE_LIMIT - PERSONAL_ALLOWANCE);
    if (basicAmount > 0) {
        tax += basicAmount * 0.20;
        taxable -= basicAmount;
    }
    
    // Higher rate (40%): income from 50,000 to 150,000
    double higherAmount = min(taxable, HIGHER_RATE_LIMIT - BASIC_RATE_LIMIT);
    if (higherAmount > 0) {
        tax += higherAmount * 0.40;
        taxable -= higherAmount;
    }
    
    // Additional rate (45%): income above 150,000
    if (taxable > 0) {
        tax += taxable * 0.45;
    }
    
    // Special rule: Personal allowance reduction for income > 100,000
    if (income > REDUCTION_THRESHOLD) {
        double reduction = (income - REDUCTION_THRESHOLD) / 2.0;
        // The reduced portion is taxed at 40% (higher rate)
        tax += reduction * 0.40;
    }
    
    return tax;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(2);
    
    int T;
    cin >> T;
    
    while (T--) {
        double targetTax;
        cin >> targetTax;
        
        // Binary search for income
        double left = 0.0;
        double right = 1e10; // Upper bound for income
        
        // Binary search with sufficient iterations for precision
        for (int iter = 0; iter < 100; iter++) {
            double mid = (left + right) / 2.0;
            double tax = calculateTax(mid);
            
            if (tax < targetTax) {
                left = mid;
            } else {
                right = mid;
            }
        }
        
        // Output the income
        cout << left << "\n";
    }
    
    return 0;
}
