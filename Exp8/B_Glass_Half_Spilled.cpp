#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <numeric>
#include <climits>
#include <cassert>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n), b(n);
    int S = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        S += b[i];
    }

    int maxA = 100 * 100; // max possible total capacity

    // dp[j][cap] = max sum of b using j glasses with total capacity = cap
    vector<vector<int>> dp(n + 1, vector<int>(maxA + 1, -1));
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= 0; j--) {
            for (int cap = 0; cap <= maxA - a[i]; cap++) {
                if (dp[j][cap] == -1) continue;
                dp[j + 1][cap + a[i]] = max(
                    dp[j + 1][cap + a[i]],
                    dp[j][cap] + b[i]
                );
            }
        }
    }

    cout << fixed << setprecision(10);

    for (int k = 1; k <= n; k++) {
        double best = 0;

        for (int cap = 0; cap <= maxA; cap++) {
            if (dp[k][cap] == -1) continue;

            double sum_b = dp[k][cap];
            double value = min((double)cap, (S + sum_b) / 2.0);
            best = max(best, value);
        }

        cout << best << " ";
    }

    cout << "\n";
    return 0;
}