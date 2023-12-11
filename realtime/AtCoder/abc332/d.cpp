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

void solve() {
    int h, w; input >> h >> w;
    lib::grid<int> A(h, w), B(h, w); input >> A >> B;
    debug(A, B);

    auto row = [&](auto& v, int i) {
        assert(0 <= i and i < h-1);
        std::swap(v[i], v[i+1]);
    };

    auto col = [&](auto& v, int j) {
        assert(0 <= j and j < w-1);
        REP(i, h) std::swap(v[i][j], v[i][j+1]);
    };

    std::queue<lib::grid<int>> que;
    map<lib::grid<int>, int> dists;
    dists.set_default(-1);

    que.push(A), dists[A] = 0;

    while(!que.empty()) {
        auto v = que.front(); que.pop();
        int d = dists[v];
        auto c = v;
        assert(d >= 0);
        REP(i, h-1) {
            row(v, i);
            if(dists[v] >= 0) CONTINUE(row(v, i));
            dists[v] = d + 1;
            que.push(v);
            row(v, i);
        }
        // assert(c == v);
        REP(i, w-1) {
            col(v, i);
            if(dists[v] >= 0) CONTINUE(col(v, i));
            dists[v] = d + 1;
            que.push(v);
            col(v, i);
        }
        // assert(c == v);
    }
    // debug(dists);

    print(dists[B]);
}
