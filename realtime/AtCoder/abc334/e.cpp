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

using mint = lib::modint998244353;

#include "data_structure/disjoint_set_union.hpp"

#include "numeric/leveler.hpp"

void solve() {
    i64 h, w; input >> h >> w;
    lib::grid<char, string> G(h, w); input >> G;

    lib::dsu ds(h * w + 1);
    lib::leveler level(h, w);
    REP(i, h) REP(j, w) {
        if(G(i,j) == '#') {
            if(i+1 < h and G(i+1, j) == '#') ds.merge(level.convert(i+1, j), level.convert(i, j));
            if(j+1 < w and G(i, j+1) == '#') ds.merge(level.convert(i, j+1), level.convert(i, j));
        }
        else {
            ds.merge(level.convert(i, j), level.sup());
        }
    }

    i64 sz = ds.group_count();

    mint ans = 0;

    i64 cnt = 0;
    REP(i, h) REP(j, w) {
        if(G(i, j) == '#') continue;
        ++cnt;
        lib::set<i64> lds;
        ITR(di, dj, DIRS4) {
            if(not G.is_valid(i + di, j + dj)) continue;
            if(G(i + di, j + dj) == '.') continue;
            lds.insert(ds.leader(level.convert(i + di, j + dj)));
        }
        debug(i, j, lds, sz - lds.size());
        ans += sz - lds.size();
    }
    ans /= cnt;

    print(ans);
}
