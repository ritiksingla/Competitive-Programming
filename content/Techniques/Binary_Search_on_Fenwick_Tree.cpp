// Binary Search Fenwick
//
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 1;
int ft[maxn], a[maxn];
int n, x, q, l, r;
void add(int idx, int val) {
    for (idx; idx <= n; idx += idx & -idx) {
        ft[idx] += val;
    }
}
int query(int idx) {
    int sum{};
    for (; idx; idx -= idx & -idx) {
        sum += ft[idx];
    }
    return sum;
}
int binary_search(int x) {
    l = 1, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        int val = query(mid);
        if (val >= x) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}