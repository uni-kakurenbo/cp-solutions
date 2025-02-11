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
#include "action/range_affine_range_sum.hpp"

void solve() {
    string s; input >> s;
    i32 n = s.size();

    std::stack<pair<char, i32>> stk;

    uni::dynamic_sequence<uni::actions::range_affine_range_sum<i32>> data;
    REP(i, n) {
        char v = s[i];
        if(v == '(' or v == ')') continue;

        if('A' <= v && v <= 'Z') {
            data.push_back(v - 'A' + 1);
        }
        else {
            data.push_back(-(v - 'a' + 1));
        }
    }
    debug(data);

    i32 pos = 0;
    REP(i, n) {
        char v = s[i];
        if(v != '(' and v != ')') CONTINUE(pos++);

        if(!stk.empty() and v == ')' and stk.top().first == '(') {

            i32 l = stk.top().second;
            i32 r = pos;
            debug(l, r);

            data(l, r) *= std::make_pair(-1, 0);
            data.reverse(l, r);

            stk.pop();
        }
        else {
            stk.emplace(v, pos);
        }
    }

    string ans;

    ITR(v, data) {
        i32 x = v.val();
        if(x >= 0) {
            ans += 'A' + x - 1;
        }
        else {
            ans += 'a' + -x - 1;
        }
    }

    print(ans);
}
