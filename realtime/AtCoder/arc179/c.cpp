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

#include "template/warnings.hpp"

map<spair<i32>, bool> memo;
bool comp(i32 i, i32 j) {
    if(memo.contains({ i, j })) return memo[{ i, j }];

    print("?", i, j).flush();
    i32 v; input >> v;
    assert(v >= 0);
    return memo[{ i, j }] = v;
}

i32 add(i32 i, i32 j) {
    print("+", i, j).flush();
    i32 v; input >> v;

    assert(v >= 0);
    return v;
}


void solve() {
    i32 n; input >> n;
    vector<i32> ids(n); std::iota(ALL(ids), 1);

    std::ranges::stable_sort(ids, comp);
    debug(ids);

    while(ids.size() > 1) {

        vector<spair<i32> next;

        REP(i, ids.size() / 2) {
            auto x = add(ids[i], ids[-i - 1]);
            auto itr = std::ranges::lower_bound(ids, x, comp);

        }
        if(ids.size() % 2 == 1) {
            next.push_back(ids[ids.size() / 2]);
        }

        ids = std::move(next);
    }

    print("!");
}
