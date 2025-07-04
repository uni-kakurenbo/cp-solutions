/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

// #include "template/small.hpp"
#include <bits/stdc++.h>
using namespace std;

void solve();

signed main() {
    // debug(__cplusplus);
    int $ = 0;
    // while(true) {
        // debug_("Case: #" + std::to_string($++));
        solve();
    // }
    return 0;
}

// #include "template/warnings.hpp"
void solve() {
    long n;
    cin >> n;
    long ans = 0;
    vector<long> A(n);
    for (int i=0; i<n; i++) {
        cin >> A[i];
    }
    sort(A.begin(), A.end());
    for (int i=0; i<(n+1)/2; i++) {
        if (A.back() > 0) {
            ans += A.back();
            A.pop_back();
        } else {
            break;
        }
    }
    cout << ans << endl;
}
