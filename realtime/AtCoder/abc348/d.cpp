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
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "graph/parse_grid.hpp"
#include "graph/shortest_path.hpp"

void solve() {
    int h, w; input >> h >> w;
    lib::grid<char, string> a(h, w); input >> a;

    int n; input >> n;
    std::deque<int> r(n), c(n), e(n); input >> lib::views::zip(r, c, e);
    ITRR(x, r) --x;
    ITRR(x, c) --x;
    debug(r, c, e);

    int si, sj, ti, tj;
    REP(i, h) REP(j, w) {
        if(a(i, j) == 'S') si = i, sj = j;
        if(a(i, j) == 'T') ti = i, tj = j;
    }
    debug(si, sj, ti, tj);

    r.push_back(si), c.push_back(sj), e.push_back(0);
    r.push_back(ti), c.push_back(tj), e.push_back(0);

    // std::map<spair<int>, int> p;
    // REP(i, n) p[{ r[i], c[i] }] = i;
    // debug(p);

    // if(!p.contains({ si, sj })) {
    //     print.no();
    //     return;
    // }

    lib::graph<int> g(h * w);
    REP(i, h) REP(j, w) {
        if(a(i, j) == '#') continue;
        ITR(ni, nj, a.vicinities4(i, j)) {
            if(a(ni, nj) == '#') continue;
            g.add_edge(i * w + j, ni * w + nj);
        }
    }

    lib::graph<int> k(n + 2);

    REP(i, n + 2) {
        auto dists = g.shortest_path_without_cost(r[i] * w + c[i]);
        REP(j, n + 2) {
            if(dists[r[j] * w + c[j]] <= e[i]) {
                k.add_edge(i, j);
            }
        }
    }

    auto dd = k.shortest_path_without_cost(n);
    print.yesno(dd[n + 1] < INF32);
}
