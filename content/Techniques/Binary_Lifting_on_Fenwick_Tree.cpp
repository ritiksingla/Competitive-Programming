// Binary Lift Fenwick
//
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1 << 20 + 1;
int ft[maxn], a[maxn];
int n, q;
const int lg = 20;
void add(int idx, int val)
{
    for(; idx <= n; idx += idx & -idx)
    {
        ft[idx] += val;
    }
}
int binary_lifting(int x)
{
    int sum{};
    int pos = 0;
    for(int h = lg; h >= 0; h--)
    {
        if( (pos + (1 << h)) < n && sum + ft[(pos + (1 << h))] < x)
        {
            sum += ft[(pos + (1 << h))];
            pos += (1 << h);
        }
    }
    return pos + 1;
}