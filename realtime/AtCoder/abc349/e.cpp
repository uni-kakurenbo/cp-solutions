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

void solve() {
    lib::grid<i32> a(3, 3), b(3, 3); input >> a;

    i64 x = 0, y = 0;

    auto judge = [&](auto b) {
        REP(2) {
            REP(i, 3) {
                auto check = [&](i32 t) {
                    REP(j, 3) if(b[i][j] != t) return false;
                    return true;
                };
                if(check(-1)) return -1;
                if(check(1)) return 1;
            }
            b.rotate();
        }

        REP(2) {
            auto check = [&](i32 t) {
                REP(i, 3) if(b[i][i] != t) return false;
                return true;
            };
            if(check(-1)) return -1;
            if(check(1)) return 1;
            b.rotate();
        }

        REP(i, 3) REP(j, 3) {
            if(b[i][j] == 0) return 0;
        }

        if(x < y) return -1;
        else return 1;
    };

    auto dfs = [&](auto&& dfs, i32 turn) {
        bool win = false;

        i32 res = judge(b);
        // debug(b, res, x, y);

        if(res != 0) return res == turn;

        auto& v = (turn == 1 ? x : y);

        REP(i, 3) REP(j, 3) {
            if(b[i][j] != 0) continue;

            b[i][j] = turn;
            v += a[i][j];

            win |= !dfs(dfs, -turn);

            b[i][j] = 0;
            v -= a[i][j];
        }

        return win;
    };

    print(dfs(dfs, 1) ? "Takahashi" : "Aoki");
}
