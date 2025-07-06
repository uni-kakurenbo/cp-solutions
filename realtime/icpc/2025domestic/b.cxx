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
    i32 n;
    input >> n;
    if(n == 0)exit(0);
    string s;
    input >> s;
    i32 num=0;
    REPD(i,n){
        if(s.substr(0, i)== s.substr(n-i, i)){
            print << s;
                REP(j, i, n) {
                    print << s[j];
                }print << "\n";
                return;
        }
    }
}
