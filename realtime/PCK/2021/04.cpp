#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int i=0; i<(n); ++i)

int main() {
    int h, w; cin >> h >> w;
    int n; cin >> n;
    int a[n], b[n];
    REP(i, n) cin >> a[i] >> b[i];
    int m; cin >> m;
    int c[m+1], d[m+1];
    REP(i, m) cin >> c[i] >> d[i];
    c[m] = 1 << 30;

    int now_h = a[0], now_m = b[0];

    now_m += 11;
    now_h += now_m / 60;
    now_m %= 60;

    // cerr << now_h << " " << now_m << "\n";

    REP(i, m+1) {
        if(make_pair(now_h, now_m) <= make_pair(c[i], d[i])) {
            now_h = c[i], now_m = d[i];
            break;
        }
    }

    now_m += 10;
    now_h += now_m / 60;
    now_m %= 60;

    // cerr << now_h << " " << now_m << "\n";

    cout << int(make_pair(now_h, now_m) <= make_pair(h, w)) << "\n";
}
