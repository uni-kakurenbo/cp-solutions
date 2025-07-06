/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

#include "template/small.hpp"

// #include "template/debug.hpp"
// #include "snippet/aliases.hpp"
// #include <bits/stdc++.h>
// using namespace std;

using i32 = int;
using i64 = long;

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 0;
    while(true) {
        debug_("Case: #" + std::to_string($++));
        solve();
    }
    return 0;
}

#include "template/warnings.hpp"
void solve() {
    i64 n, m;
    input >> n >> m;
    if(n == 0 && m == 0)exit(0);
    vector<i64> a(n);
    input >>a;
    a.sort().unique();
    i64 shuu = m/7;
    i64 remain = m%7;
    i64 yasumi = shuu*2;
    if(remain == 6)yasumi++;
    ITR(x, a){
        if(x<=m && (x%7 != 6 && x%7 !=0))yasumi++;
    }
    print << m-yasumi << "\n";
}
