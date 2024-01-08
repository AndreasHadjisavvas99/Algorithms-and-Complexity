#include <iostream>
#include <vector>

using namespace std;

// Function to maximize profit by buying and selling stocks
void maximizeProfit(int N, int K, vector<int>& prices) {
    // If the number of transactions allowed is zero or the number of days is less than 2, no profit can be made
    if (K == 0 || N < 2) {
        cout << "0" << endl;
        return;
    }

    // Create a 2D DP array to store the maximum profit at each transaction and day
    vector<vector<int>> dp(K + 1, vector<int>(N, 0));

    // Iterate over each transaction
    for (int i = 1; i <= K; i++) {
        int maxDiff = -prices[0];

        // Iterate over each day
        for (int j = 1; j < N; j++) {
            // Calculate the maximum profit that can be obtained by either not selling on the current day
            // or selling on the current day
            dp[i][j] = max(dp[i][j - 1], prices[j] + maxDiff);

            // Update the maximum difference to consider for the next iteration
            maxDiff = max(maxDiff, dp[i - 1][j] - prices[j]);
        }
    }

    cout << dp[K][N - 1] << endl;
}

int main() {
    int N, K;

    // Input number of days and transactions allowed
    cin >> N;

    cin >> K;

    // Input prices for each day
    vector<int> prices(N);
    for (int i = 0; i < N; i++) {
        cin >> prices[i];
    }

    // Call the function to maximize profit
    maximizeProfit(N, K, prices);

    return 0;
}
