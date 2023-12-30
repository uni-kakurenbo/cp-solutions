/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

using point = lib::point<ld>;

void solve() {
    int n, k; input >> n >> k;
    point s; input >> s;
    valarray<point> ps(n + 1); input(ps.begin(), ps.end() - 1);
    ps[n] = s;

    ld ans = 0;

    point now = s;
    i64 cnt = k;

    std::priority_queue<std::pair<int, ld>> pq;
    REP(i, n) {
        ld d = lib::distance(now, ps[i]);
        ans += d;
        debug(now, ps[i], d, cnt, ans);
        if(i < n-1 and --cnt <= 0) {
            while(true) {
                auto [ j, dist ] = pq.top(); pq.pop();
                dist *= -1;
                if(i - j > k) continue;
                debug(dist, j);
                ans += dist;
                cnt += k - (i - j);
                break;
            }
        };
        debug(ans, cnt);
        now = ps[i];
        pq.emplace(i, -(lib::distance(s, ps[i]) + lib::distance(s, ps[i + 1]) - lib::distance(ps[i], ps[i+1])));
    }
    ans += lib::distance(s, now);

    print(ans);
}
