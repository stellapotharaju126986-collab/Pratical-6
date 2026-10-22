#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Struct to hold both the minimum cost table and the split tracking table
struct MCMResult {
    vector<vector<int>> m;
    vector<vector<int>> s;
};

/**
 * Computes the minimum multiplication cost and optimal split points.
 * p: vector containing the dimensions of the matrices.
 */
MCMResult matrixChainOrder(const vector<int>& p) {
    int n = p.size() - 1; // Number of matrices
    
    // m[i][j] stores the minimum multiplication cost for matrices i through j
    // s[i][j] stores the optimal split point (k) for matrices i through j
    vector<vector<int>> m(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> s(n + 1, vector<vector<int>>::value_type(n + 1, 0));

    // l is the chain length
    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;

            // Try all possible split points k between i and j-1
            for (int k = i; k < j; k++) {
                // cost = cost of left subchain + cost of right subchain + cost of multiplying them
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
    return {m, s};
}

/**
 * Prints the optimal parenthesization using the split table s.
 */
void printOptimalParenthesis(const vector<vector<int>>& s, int i, int j) {
    if (i == j) {
        cout << "A" << i;
    } else {
        cout << "(";
        printOptimalParenthesis(s, i, s[i][j]);
        printOptimalParenthesis(s, s[i][j] + 1, j);
        cout << ")";
    }
}

int main() {
    // Matrix dimensions: 
    // A1: 10x20, A2: 20x30, A3: 30x40, A4: 40x30
    vector<int> dimensions = {10, 20, 30, 40, 30};
    int numMatrices = dimensions.size() - 1;

    MCMResult result = matrixChainOrder(dimensions);

    cout << "Minimum number of multiplications: " << result.m[1][numMatrices] << endl;
    cout << "Optimal Parenthesization: ";
    printOptimalParenthesis(result.s, 1, numMatrices);
    cout << endl;

    return 0;
}
