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
using ll = long long;

ll check(vector<ll>& arr, ll max_val) {
    ll steps2 = 0, steps1 = 0;

    for (ll x : arr) {
        if (x == max_val) continue;
        ll diff = max_val - x;
        steps2 += diff / 2;
        steps1 += diff % 2;
    }

    if (steps1 > steps2) {
        return 2 * steps1 - 1;
    } else {
        ll sm = steps1 + 2 * steps2;
        if (sm % 3 == 0) return (sm / 3) * 2;
        if (sm % 3 == 1) return (sm / 3) * 2 + 1;
        return ((sm + 1) / 3) * 2;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<ll> arr(n);
        for (int i = 0; i < n; i++) cin >> arr[i];

        ll mx = *max_element(arr.begin(), arr.end());

        ll t1 = check(arr, mx);
        ll t2 = check(arr, mx + 1);

        cout << min(t1, t2) << '\n';
    }
}