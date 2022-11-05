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
#include "output.hpp"

Output _print;
#define print _print
/* #endregion */

signed main() {
    int n; cin >> n;
    vector<int> a(n-1), b(n-1), c(n);
    REP(i, n-1) cin >> a[i] >> b[i], --a[i], --b[i];
    REP(i, n) cin >> c[i];
    sort(ALL(c));

    vector<int> degs(n);
    REP(i, n-1) ++degs[a[i]], ++degs[b[i]];

    debug(degs);

    queue<int> que;
    REP(i, n) if(degs[i] == 1) que.push(i);

    vector<int> ans(n);
    REP(i, n) {
        assert(not que.empty());
        auto v = que.front(); que.pop();
        ans[v] = c[i];
        REP(j, n-1) {
            if(a[j] == v and --degs[b[j]] == 1) que.push(b[j]);
            if(b[j] == v and --degs[a[j]] == 1) que.push(a[j]);
        }
    }
    assert(que.empty());

    print(reduce(ALL(c)) - c.back());
    print(ALL(ans));

    return 0;
}
