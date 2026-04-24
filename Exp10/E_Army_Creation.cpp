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

// Persistent Segment Tree on coordinate: values 0..n (prev_k = 0 means "doesn't exist")
// Each node stores count of elements in range

struct Node {
    int left, right, cnt;
} tree[20000000];

int tot = 0;
int roots[100005];

int build(int l, int r) {
    int cur = ++tot;
    tree[cur] = {0, 0, 0};
    if (l == r) return cur;
    int mid = (l + r) / 2;
    tree[cur].left = build(l, mid);
    tree[cur].right = build(mid+1, r);
    return cur;
}

int update(int prev, int l, int r, int pos) {
    int cur = ++tot;
    tree[cur] = tree[prev];
    tree[cur].cnt++;
    if (l == r) return cur;
    int mid = (l + r) / 2;
    if (pos <= mid)
        tree[cur].left = update(tree[prev].left, l, mid, pos);
    else
        tree[cur].right = update(tree[prev].right, mid+1, r, pos);
    return cur;
}

// query count of values in [ql, qr] between version r and version l-1
int query(int vl, int vr, int l, int r, int ql, int qr) {
    if (ql > qr || l > qr || r < ql) return 0;
    if (ql <= l && r <= qr) return tree[vr].cnt - tree[vl].cnt;
    int mid = (l + r) / 2;
    return query(tree[vl].left, tree[vr].left, l, mid, ql, qr)
         + query(tree[vl].right, tree[vr].right, mid+1, r, ql, qr);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    // For each position i, find prev_k[i] = position of k-th previous same type
    // Use a map from type -> list of positions seen so far
    vector<int> prev_k(n+1, 0); // 0 means doesn't exist (before position 1)
    map<int, vector<int>> positions;
    
    for (int i = 1; i <= n; i++) {
        int t = a[i];
        auto& v = positions[t];
        if ((int)v.size() >= k) {
            prev_k[i] = v[v.size() - k];
        } else {
            prev_k[i] = 0;
        }
        v.push_back(i);
    }
    
    // Build persistent segment tree
    // Values range: 0..n (prev_k[i] in [0, n])
    roots[0] = build(0, n);
    for (int i = 1; i <= n; i++) {
        roots[i] = update(roots[i-1], 0, n, prev_k[i]);
    }
    
    int q;
    cin >> q;
    
    long long last = 0;
    while (q--) {
        long long x, y;
        cin >> x >> y;
        int l = (int)((x + last) % n) + 1;
        int r = (int)((y + last) % n) + 1;
        if (l > r) swap(l, r);
        
        // Count positions i in [l,r] where prev_k[i] < l
        // i.e., prev_k[i] in [0, l-1]
        last = query(roots[l-1], roots[r], 0, n, 0, l-1);
        cout << last << "\n";
    }
    
    return 0;
}