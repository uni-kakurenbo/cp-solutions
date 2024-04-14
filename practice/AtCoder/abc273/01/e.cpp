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

#include "data_structure/persistent_stack.hpp"

void solve() {
    int q; input >> q;

    using persistent_stack = lib::pmr::persistent_stack<int>;

    std::pmr::unsynchronized_pool_resource mr;

    persistent_stack stack(&mr);
    std::pmr::unordered_map<int, persistent_stack> storage(&mr);


    REP(q) {
        string t; input >> t;
        if(t == "ADD") {
            int x; input >> x;
            stack.push(x);
        }
        if(t == "DELETE") {
            if(not stack.empty()) stack.pop();
        }
        if(t == "SAVE") {
            int x; input >> x;
            storage[x] = stack;
        }
        if(t == "LOAD") {
            int x; input >> x;
            stack = storage[x];
        }
        debug(stack.size());
        print(stack.top_or(-1));
    }
}
