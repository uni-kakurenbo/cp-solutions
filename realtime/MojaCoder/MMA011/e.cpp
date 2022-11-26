/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
#include "output.hpp"

Output print;

struct Solver {
    ll solve(int n, int k, int s, int g) const {

    }
};

signed main() {
    int q; cin >> q;
    Solver solver;
    LOOP(q) {
        int n, k, s, g; cin >> n >> k >> s >> g;
        print(solver.solve(n, k, s, g));
    }
    return 0;
}
