/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
#include "input.hpp"
#include "output.hpp"

Input _input;
Output _print;
#define input _input
#define print _print
/* #endregion */

signed main() {
    int q; cin >> q;
    stack<string> stk;
    LOOP(q) {
        string book; cin >> book;
        if(book == "READ") print(stk.top()), stk.pop();
        else stk.push(book);
    }
    return 0;
}
