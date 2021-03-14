// Closest Points
//
// O(N*log(N)*log(N))
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
struct point {
    int64_t x, y;
    point operator-(point a) {
        return {x - a.x, y - a.y};
    }
    int64_t dist() {
        return x * x + y * y;
    }
};
bool by_x(point& a, point& b) {
    return a.x < b.x;
}
bool by_y(point& a, point& b) {
    return a.y < b.y;
}
int64_t n, x;
vector<point>vec(maxn);
vector<int64_t>pre(maxn);
int64_t solve2(int64_t l, int64_t r) {
    if (l == r) {
        return (int64_t)1e18;
    }
    int64_t mid = (l + r) / 2;
    sort(vec.begin() + l, vec.begin() + r + 1, by_x);
    int64_t d = min(solve2(l, mid), solve2(mid + 1, r));
    int64_t midx = vec[mid].x;
    vector<point>strip;
    forn(i, l, r) {
        if (point{vec[i].x - midx, 0} .dist() < d)
            strip.push_back(vec[i]);
    }
    sort(all(strip), by_y);
    rep(i, strip.size()) {
        forn(j, i + 1, strip.size() - 1) {
            if (point{0, strip[i].y - strip[j].y} .dist() > d)
                break;
            d = min((strip[i] - strip[j]).dist(), d);
        }
    }
    return d;
}
void solve() {
    cin >> n;
    rep(i, n) {
        cin >> x;
        pre[i + 1] = pre[i] + x;
    }
    rep(i, n) {
        vec[i] = point{i + 1, pre[i + 1]};
    }
    cout << solve2(0, n - 1);
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int64_t t = 1;
    rep(i, t) {
        solve();
    }
    return 0;
}
// https://codeforces.com/contest/429/problem/D