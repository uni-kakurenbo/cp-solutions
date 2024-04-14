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
    int n, a, b; input >> n >> a >> b;
    vector<char> s(2 * n); input >> s;
    chmin(a, 2 * b);

    i64 ans = 0;

    debug(s);

    {
        vector<char> t;

        ITR(v, s) {
            t.push_back(v);
            if(t.size() >= 2 and t[-2] == '(' and t[-1] == ')') {
                REP(2) t.pop_back();
            }
        }
        debug(t);
        s = t;
    }

    {
        vector<char> t;
        ITR(v, s) {
            t.push_back(v);
            if(t.size() >= 4 and t[-4] == ')' and t[-3] == ')' and t[-2] == '(' and t[-1] == '(') {
                ans += a;
                REP(4) t.pop_back();
            }
        }
        debug(t);
        s = t;
    }

    {
        vector<char> t;
        ITR(v, s) {
            t.push_back(v);
            if(t.size() >= 2 and t[-2] == ')' and t[-1] == '(') {
                ans += a;
                REP(2) t.pop_back();
            }
        }
        debug(t);
        s = t;
    }

    ans += b * s.size() / 2;

    print(ans);
}
