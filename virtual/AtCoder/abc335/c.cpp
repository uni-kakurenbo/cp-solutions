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
    int n, q; input >> n >> q;

    std::deque<spair<i32>> que;
    REP(i, n) {
        que.push_back({ i + 1, 0 });
    }

    REP(q) {
        int t; input >> t;
        if(t == 1) {
            char c; input >> c;
            auto& [ x, y ] = que.front();
            que.pop_back();
            if(c == 'R') que.emplace_front(x + 1, y);
            if(c == 'L') que.emplace_front(x - 1, y);
            if(c == 'U') que.emplace_front(x, y + 1);
            if(c == 'D') que.emplace_front(x, y - 1);
        }
        if(t == 2) {
            i32 p; input >> p; --p;
            print(que[p]);
        }
        debug(que);
    }
}
