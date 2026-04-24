#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <limits>
#include <iomanip>
#include <functional>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> L(n), R(n), coords;

    // Input
    for (int i = 0; i < n; i++) {
        cin >> L[i] >> R[i];
        coords.push_back(L[i]);
        coords.push_back(R[i] + 1); // important
    }

    // Coordinate compression
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());

    // Difference array
    vector<int> diff(coords.size(), 0);

    for (int i = 0; i < n; i++) {
        int l = lower_bound(coords.begin(), coords.end(), L[i]) - coords.begin();
        int r = lower_bound(coords.begin(), coords.end(), R[i] + 1) - coords.begin();

        diff[l]++;   // start
        diff[r]--;   // end
    }

    // Answer array
    vector<long long> ans(n + 1, 0);

    int cur = 0;
    for (int i = 0; i < (int)coords.size() - 1; i++) {
        cur += diff[i];
        long long length = coords[i + 1] - coords[i];
        ans[cur] += length;
    }

    // Output
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";

    return 0;
}