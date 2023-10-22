/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

int N, D, Q;
int query_count = 0;

template<std::ranges::range R0, std::ranges::range R1>
int query(const R0& r0, const R1& r1) noexcept {
    cout << std::ranges::size(r0) << " " << std::ranges::size(r1) << " ";
    print << r0 << " " << r1;
    cout << std::endl;

    char res; cin >> res;

    ++query_count;
    debug(query_count, r0, r1, res);

    if(res == '<') return 1;
    if(res == '=') return 0;
    if(res == '>') return -1;

    assert(false);
}


signed main() {
    cin >> N >> D >> Q;
    debug(N, D, Q);

    valarray<int> inds(N); std::iota(ALL(inds), 0);

    auto comp = [&](int i, int j) -> bool {
        if(query_count >= Q) return lib::rand() % 2;
        const int res = query(std::array<int,1>{ i }, std::array<int,1>{ j });
        return res <= 0;
    };

    inds.stable_sort(comp);
    debug(inds);

    REP(Q - query_count) {
        cout << "1 1 0 1" << std::endl;
        char _; cin >> _;
    }

    valarray<int> divide(N);
    REP(i, N) divide[inds[i]] = i % D;
    debug(divide);

    print(divide);
}
