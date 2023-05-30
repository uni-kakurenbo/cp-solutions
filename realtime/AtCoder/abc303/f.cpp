/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

void solve();

signed main() {
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

// inline bool operator< (const spair<i64>& a, const spair<i64>& b) {
//     return a.first * a.second < b.first * b.second;
// }

#include "numeric/boundary_seeker.hpp"

void solve() {
    i64 n, h; cin >> n >> h;

    struct Magic {
        i64 t, d;
        Magic(i64 t = 0, i64 d = 0) : t(t), d(d) {}

        bool operator<(const Magic& other) const { return this->t * this->d < other.t * other.d; }

        std::pair<i64,i64> _debug() const { return { t, d }; }
    };

    map<i64,Magic> mp;

    REP(i, n) {
        int t, d; cin >> t >> d;
        if(mp[t].d < d) mp[t] = { t, d };
    }
    debug(mp);

    auto can = [&](i64 limit) -> bool {
        debug(limit);
        std::priority_queue<Magic> usable;
        ITR(t, td, mp) usable.emplace(std::min(td.t, limit), td.d);

        i64 sum = 0;

        FORD(rem, limit) {
            if(rem == 0) break;
            while(usable.top().t > rem) {
                usable.emplace(rem, usable.top().d);
                usable.pop();
            }

            sum += usable.top().t * usable.top().d;

            if(sum >= h) return true;
        }
        return false;
    };

    lib::boundary_seeker<i64> seeker(can);
    print(seeker.bound<true>(0, 100));
}
