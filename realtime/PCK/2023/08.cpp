#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int i=0; i<(n); ++i)
#define FOR(i, a, b) for(auto i=(a); i<=(b); ++i)

using ld = long double;

ld intersect_x(
    ld dx0, ld dy0, ld x0, ld y0,
    ld dx1, ld dy1, ld x1, ld y1
)
{
    const ld det = dx1 * dy0 - dx0 * dy1;
    const ld p = dx1 * (dy0 * x0 - y0) - dx0 * (dy1 * x1 - y1);
    return p / det;
}

pair<ld,ld> intersect(
    ld dx0, ld dy0, ld x0, ld y0,
    ld dx1, ld dy1, ld x1, ld y1
) {
    const ld x = intersect_x(dx0, dy0, x0, y0, dx1, dy1, x1, y1);
    const ld y = intersect_x(dy0, dx0, y0, x0, dy1, dx1, y1, x1);
    return { x, y };
}


ld time(
    ld v,
    ld dx0, ld dy0, ld x0, ld y0,
    ld dx1, ld dy1, ld x1, ld y1
) {
    cerr << "Int arg: " << dx0 << " " << dy0 << " " << x0 << " " << y0 << "\n";
    cerr << "Int arg: " << dx1 << " " << dy1 << " " << x1 << " " << y1 << "\n";

    auto [ x, y ] = intersect(dx0, dy0, x0, y0, dx1, dy1, x1, y1);

    if(dx1 * y0 == dy1 * (x0 - x1) + y1) {
        return hypot(x0 - x1, y0 - y1) / hypot(dx1 - dx0, dy1 - dy0);
    }

    cerr << "Int: " << x << " " << y << "\n";

    const ld dx = x - x0, dy = y - y0;
    return hypot(dx, dy) / v;
}

const ld EPS = 10e-8;
const ld INF = std::numeric_limits<ld>::infinity();

ld get(ld v, ld& x0, ld& y0, ld x1, ld y1, ld s, ld t) {
    ld low = 0, high = 2 * M_PI;

    ld res = INF;

    while(abs(low - high) > 6) {
        const ld mid_l = (low + high) / 3;
        const ld mid_r = (low + high) * 2 / 3;
        cerr << "l: " << mid_l << " r: " << mid_r << "\n";
        ld val0 = time(v, cos(mid_l), sin(mid_l), x0, y0, s, t, x1, y1);
        ld val1 = time(v, cos(mid_r), sin(mid_r), x0, y0, s, t, x1, y1);
        if(val0 < val1) low = mid_l;
        else high = mid_r;
        res = min(val0, val1);
    }

    cerr << "angle: " << low << "\n";

    x0 += v * cos(low);
    y0 += v * sin(low);

    return res;
}

int main() {
    long n, v; cin >> n >> v;

    long x[n], y[n], s[n], t[n];
    REP(i, n) cin >> x[i] >> y[i] >> s[i] >> t[i];

    int p[n]; iota(p, p + n, 0);

    ld ans = INF;

    do {
        ld ans = 0;
        ld xi = 0, yi  = 0;
        ld now = 0;

        for(int i : p) cerr << i << " ";
        cerr << "\n";

        REP(i, n) {
            ld dt = get(v, xi, yi, x[p[i]] + s[p[i]] * now, y[p[i]] + t[p[i]] * now, s[p[i]], t[p[i]]);
            cerr << dt << "\n";
            now += dt;
        }

        ans = min(ans, now);
    } while(next_permutation(p, p + n));

    cout << ans << "\n";
}
