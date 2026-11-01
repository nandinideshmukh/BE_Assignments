#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// problem statement:
// Given weights and values of n items, put these items in a knapsack of capacity W
// to get the maximum total value in the knapsack. In other words, given two integer arrays
//  val[0..n-1] and wt[0..n-1]
// which represent values and weights associated with n items respectively. Also given an integer W which represents knapsack capacity, find out the maximum value subset of val[] such that sum of the weights of this subset is smaller than or equal to W. You cannot break an item, either pick the complete item or don’t pick it (0-1 property).
class Knapsack
{
public:
    int solveKnapsack(int W, const vector<int> &weights, const vector<int> &values, int n)
    {
        vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
        // this is a bottom-up dynamic programming approach to solve the 0/1 Knapsack problem
        // try out every item and every weight capacity from 1 to W, and fill the dp table accordingly
        for (int i = 1; i <= n; i++)
        {
            for (int w = 1; w <= W; w++)
            {
                if (weights[i - 1] <= w)
                {
                    dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
                }
                else
                {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
        return dp[n][W];
    }
};

int main()
{
    Knapsack solver;

    vector<int> values = {60, 100, 120};
    vector<int> weights = {10, 20, 30};
    int W = 50;
    int n = values.size();

    int max_value = solver.solveKnapsack(W, weights, values, n);

    cout << "Maximum value that can be obtained: " << max_value << endl;

    return 0;
}
