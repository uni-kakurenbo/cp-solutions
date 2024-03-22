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

#include "data_structure/dynamic_sequence.hpp"
#include "data_structure/dynamic_set.hpp"
#include "action/range_sequence_hash.hpp"

void solve() {
    int n, k; input >> n >> k;
    vector<int> p(n); input >> p;

    lib::dynamic_sequence<lib::actions::range_sequence_hash<>, lib::treap_context<lib::i32>> seq(p);
    lib::dynamic_set<lib::actions::range_sequence_hash<>, lib::treap_context<lib::i32>> set(p | std::views::take(k));

    std::set<lib::actions::range_sequence_hash<>::operand> vs;
    FOR(i, k, n) {
        vs.emplace(seq(0, i - k).fold() + set.fold() + seq.fold(i, n));
        if(i == n) break;
        set.erase(p[i - k]);
        set.insert(p[i]);
    }

    print(vs.size());
}
