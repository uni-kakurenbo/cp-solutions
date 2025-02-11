/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}


#include "numeric/boundary_seeker.hpp"
#include "data_structure/dynamic_sequence.hpp"
#include "data_structure/dynamic_set.hpp"
#include "action/range_add_range_sum.hpp"

#include "template/warnings.hpp"
void solve() {
    i64 n; input >> n;

    vector<i64> x(n); input >> x;
    uni::dynamic_set<uni::actions::range_add_range_sum<uni::i64>> ps;
    REP(i, n) ps.insert(x[i] - i);
    debug(ps);

    auto get_pos = [&](i64 ind) {
        auto v = ps.get(ind);
        return v + ind;
    };

    auto move_r = [&](i64 ind, i64 pos) {
        debug("r", ind, pos);

        auto ok = [&](auto v) {
            return pos + (v - ind) > get_pos(v);
        };
        uni::boundary_seeker<i64> seeker(ok);
        auto bound = seeker.bound(ind, n);
        debug(bound);

        auto prev = ps.fold().val();

        ps.erase(ind, bound + 1);
        ps.insert(pos - ind, bound - ind + 1);

        debug(ps);

        return ps.fold().val() - prev;
    };


    auto move_l = [&](i64 ind, i64 pos) {
        debug("l", ind, pos);
        auto prev = ps.fold().val();

        auto ok = [&](auto v) {
            return get_pos(v) > pos - (ind - v);
        };
        uni::boundary_seeker<i64> seeker(ok);
        auto bound = seeker.bound(ind, -1);
        debug(bound);

        ps.erase(bound , ind + 1);
        ps.insert(pos - ind, ind - bound + 1);
        debug(ps);

        return prev - ps.fold().val();
    };

    auto move = [&](i64 ind, i64 pos) -> i64 {
        auto cur = get_pos(ind);
        if(cur < pos) return move_r(ind, pos);
        if(cur > pos) return move_l(ind, pos);
        return 0;
    };

    i64 ans = 0;

    i64 q; input >> q;
    REP(q) {
        i64 t, g; input >> t >> g; --t;
        auto cost = move(t, g);
        debug(cost);
        ans += cost;
    }

    print(ans);
}
