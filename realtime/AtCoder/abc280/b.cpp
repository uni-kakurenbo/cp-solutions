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

#include "iterable/adjacent_difference.hpp"

signed main() {
    int n; cin >> n;
    vector<int> a(n); input >> a;
    Lib::AdjacentDifference<int> diff(ALL(a), false);
    print(diff);
    return 0;
}
