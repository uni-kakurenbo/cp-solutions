/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

// #include "template/standard.hpp"

#include <bits/stdc++.h>
using namespace std;
namespace rng = std::ranges;

void solve();

signed main() {
    // debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    while(true) {
        // debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

// #include "template/warnings.hpp"
void solve() {
    int a1, a2, a3, a4;
    cin >> a1 >> a2 >> a3 >> a4;
    if(a1 == 0 && a2 == 0 && a3 == 0 && a4 == 0) {
        exit(0);
    }
    while(1){
        int s1 = a1;
        int s2 = a2;
        int s3 = a3;
        int s4 = a4;
        if(s1==0)s1=1e9;
        if(s2==0)s2=1e9;
        if(s3==0)s3=1e9;
        if(s4==0)s4=1e9;
        int MIN = min(s1, min(s2, min(s3, s4)));
        if(MIN == a1){
            a2-=a1;
            a3-=a1;
            a4-=a1;
        }else if(MIN == a2){
            a1-=a2;
            a3-=a2;
            a4-=a2;
        }else if(MIN == a3){
            a1-=a3;
            a2-=a3;
            a4-=a3;
        }else if(MIN == a4){
            a1-=a4;
            a2-=a4;
            a3-=a4;
        }
        if(a1<0)a1=0;
        if(a2<0)a2=0;
        if(a3<0)a3=0;
        if(a4<0)a4=0;
        int sum = a1 + a2 + a3 + a4;
        if(a1 == sum || a2 ==sum || a3 ==sum || a4 == sum) {
            cout << sum << endl;
            break;
        }
    }
}
