#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <climits>
#include <numeric>
#include <unordered_map>

using namespace std;

class TravelingSalesman {
public:
    TravelingSalesman(const vector<vector<int>>& distances) : distances(distances), n(distances.size()) {}

    int findShortestRoute() {
        vector<int> path(n);
        iota(path.begin(), path.end(), 0);
        int minPathLength = numeric_limits<int>::max();

        do {
            int currentPathLength = 0;
            for (int i = 0; i < n - 1; ++i) {
                currentPathLength += distances[path[i]][path[i + 1]];
            }
            currentPathLength += distances[path[n - 1]][path[0]];

            minPathLength = min(minPathLength, currentPathLength);
        } while (next_permutation(path.begin() + 1, path.end()));

        return minPathLength;
    }

private:
    vector<vector<int>> distances;
    int n;
};

class CoinChangeUnlimited {
public:
    CoinChangeUnlimited(const vector<int>& coins) : coins(coins) {}

    int minCoins(int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;

        for (int i = 1; i <= amount; ++i) {
            for (const int& coin : coins) {
                if (i - coin >= 0) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }

        return dp[amount] > amount ? -1 : dp[amount];
    }

private:
    vector<int> coins;
};

class CoinChangeLimited {
public:
    CoinChangeLimited(const vector<int>& coins, const vector<int>& counts) : coins(coins), counts(counts) {}

    int minCoins(int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, amount + 1));
        dp[0][0] = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= amount; ++j) {
                dp[i][j] = dp[i - 1][j];
                for (int k = 1; k <= counts[i - 1] && k * coins[i - 1] <= j; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - k * coins[i - 1]] + k);
                }
            }
        }

        return dp[n][amount] > amount ? -1 : dp[n][amount];
    }

private:
    vector<int> coins;
    vector<int> counts;
};

class MatrixChainMultiplication {
public:
    int minMultiplications(const vector<int>& p) {
        int n = p.size() - 1;
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i < n - len + 1; ++i) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                for (int k = i; k < j; ++k) {
                    int cost = dp[i][k] + dp[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                    dp[i][j] = min(dp[i][j], cost);
                }
            }
        }

        return dp[0][n - 1];
    }
};

class MinimumTriangleSum {
public:
    int minTriangleSum(vector<vector<int>>& triangle) {
        if (triangle.empty()) return 0;

        for (int row = triangle.size() - 2; row >= 0; --row) {
            for (int col = 0; col < triangle[row].size(); ++col) {
                triangle[row][col] += min(triangle[row + 1][col], triangle[row + 1][col + 1]);
            }
        }

        return triangle[0][0];
    }
};

class WordForming {
public:
    bool canFormWord(const string& word, const string& alphabet) {
        unordered_map<char, int> alphabetCount;
        for (char c : alphabet) {
            alphabetCount[c]++;
        }

        for (char c : word) {
            if (alphabetCount[c] == 0) {
                return false;
            }
            alphabetCount[c]--;
        }

        return true;
    }
};


int main() {
    // vector<vector<int>> distances = {
    //     {0, 10, 15, 20},
    //     {10, 0, 35, 25},
    //     {15, 35, 0, 30},
    //     {20, 25, 30, 0}
    // };

    // TravelingSalesman ts(distances);
    // cout << "Shortest route: " << ts.findShortestRoute() << endl;

    
    // vector<int> coins = {1, 2, 5};
    // int amount = 11;

    // CoinChangeUnlimited cc(coins);
    // cout << "Minimum coins needed: " << cc.minCoins(amount) << endl;

    // vector<int> coins = {1, 2, 5};
    // vector<int> counts = {5, 2, 1};
    // int amount = 11;

    // CoinChangeLimited cc(coins, counts);
    // cout << "Minimum coins needed: " << cc.minCoins(amount) << endl;

    // vector<int> p = {1, 2, 3, 4};

    // MatrixChainMultiplication mcm;
    // cout << "Minimum number of multiplications: " << mcm.minMultiplications(p) << endl;

    // vector<vector<int>> triangle = {
    //     {2},
    //     {3, 4},
    //     {6, 5, 7},
    //     {4, 1, 8, 3}
    // };

    // MinimumTriangleSum mts;
    // cout << "Minimum triangle sum: " << mts.minTriangleSum(triangle) << endl;


    string word = "hello";
    string alphabet = "hleol";

    WordForming wf;
    cout << "Can form word: " << (wf.canFormWord(word, alphabet) ? "Yes" : "No") << endl;
    
}
