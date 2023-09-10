#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int i=0; i<(n); ++i)

int main() {
    int x[4], y[4];
    REP(i, 4) cin >> x[i] >> y[i];

    auto dist = [&](int x, int y) { return x * x + y * y; };

    auto angle = [&](int x0, int y0, int x1, int y1) {
        return x0 * x1 + y0 * y1;
    };

    int len = dist(x[0] - x[1], y[0] - y[1]);
    // cerr << len << "\n";

    REP(i, 4) {
        // cerr << i << " " << x[i] << " " << y[i] << "\n";
        // cerr << dist(x[i] - x[(i+1)%4], y[i] - y[(i+1)%4]) << "\n";
        // cerr << angle(x[i] - x[(i+1)%4], y[i] - y[(i+1)%4], x[i] - x[(i-1)%4], y[i] - y[(i-1)%4]) << "\n";

        if(len != dist(x[i] - x[(i+1)%4], y[i] - y[(i+1)%4])) {
            cout << "No" << "\n";
            return 0;
        }
        if(angle(x[(i+1)%4] - x[i], y[(i+1)%4] - y[i], x[(i+3)%4] - x[i], y[(i+3)%4] - y[i]) != 0) {
            cout << "No" << "\n";
            return 0;
        }
    }

    cout << "Yes\n";

    return 0;
}
