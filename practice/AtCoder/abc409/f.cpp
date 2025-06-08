/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
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

#include "template/warnings.hpp"
void solve() {
    i32 n, q; input >> n >> q;
    using point = uni::point<i64>;

    uni::disjoint_set ds(n + q);

    uni::priority_queue_rev<pair<i64, spair<i32>>> pq;
    vector<point> ps(n); input >> ps;

    REP(i, n) {
        REP(j, i + 1, n) {
            pq.emplace(uni::manhattan_distance(ps[i], ps[j]), std::make_pair(i, j));
        }
    }

    REP(q) {
        i32 t; input >> t;
        if(t == 1) {
            point p; input >> p;
            ps.push_back(p);

            REP(i, n) {
                pq.emplace(uni::manhattan_distance(ps[i], p), std::make_pair(i, n));
            }

            ++n;
        }
        if(t == 2) {
            while(!pq.empty() && ds.same(pq.top().second.first, pq.top().second.second)) pq.pop();
            if(pq.empty()) CONTINUE(print(-1));

            auto [ d, p ] = pq.top();

            while(!pq.empty() && d == pq.top().first) {
                auto [ _, v ] = pq.top();
                debug(v);
                ds.merge(v.first, v.second);
                pq.pop();
            }
            print(d);
        }
        if(t == 3) {
            i32 u, v; input >> u >> v; --u, --v;
            print.yesno(ds.same(u, v));
        }
    }
}
