#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int i=0; i<(n); ++i)
#define FOR(i, a, b) for(auto i=(a); i<=(b); ++i)

const int INF = 1 << 30;

int main() {
    int n; cin >> n;
    valarray<int> a(n), b(n);
    REP(i, n) cin >> a[i];
    REP(i, n) cin >> b[i];

    valarray<int> min_l(-INF, n+1), min_r(-INF, n+1);
    REP(i, n) {
        min_l[i+1] = max(min_l[i], -a[i]);
        min_r[i+1] = max(min_r[i], -a[n-i-1]);
    }

    for(int v : min_l) cerr << v << " ";
    cerr << "\n";
    for(int v : min_r) cerr << v << " ";
    cerr << "\n";

    valarray<int> l(n), r(n);
    REP(i, n) {
        l[i] = upper_bound(begin(min_r) + i, end(min_r), -b[i]) - begin(min_r) - 1;
        cerr << l[i] << " ";
        // r[i] = upper_bound(begin(min_l), end(min_l), b[i]);
    }
    cerr << "\n";

    cout << "Yes\n";
}
