/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

#include "template/small.hpp"

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
    int n;
    std::cin >> n;
    if(n == 0)exit(0);
    int a;
    vector<int> t(1e5,false);
    for(int i = 0; i < n; i++){
        std::cin >> a;
        a--;
        t[a] = true;
    }
    for(int i = 0; i< 1e5; i++){
        if(t[i] != true){
            std::cout << i +1 << std::endl;
            return;
        }
    }

}
