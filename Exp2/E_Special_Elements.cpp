#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        // mark which sums are possible
        vector<bool> found(n + 1, false);

        // generate all subarray sums (length >= 2)
        for (int i = 0; i < n; i++) {
            int sum = a[i];
            for (int j = i + 1; j < n; j++) {
                sum += a[j];

                if (sum > n) break;   // no need to continue
                found[sum] = true;
            }
        }

        // count valid elements
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] <= n && found[a[i]]) {
                count++;
            }
        }

        cout << count << endl;
    }

    return 0;
}