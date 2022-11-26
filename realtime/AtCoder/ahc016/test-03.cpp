/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */

#include <iostream>
#include <string>
#include <valarray>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <numeric>
#include <random>

#include "template.hpp"
#include "numeric/matrix.hpp"

struct Graph;
struct Solver;

void increasing_sequences(const int n, std::vector<std::vector<int>> *ans) {
    static std::vector<int> p;
    if((int)p.size() == n) {
        ans->push_back(p);
        return;
    }
    int l = p.empty() ? 0 : p.back();
    p.push_back(0);
    REPF(i, l, n) {
        p.back() = i;
        increasing_sequences(n, ans);
    }
    p.pop_back();
    return;
};

signed main() {
    int n; std::cin >> n;
    std::vector<std::vector<int>> ans;

    increasing_sequences(n, &ans);

    sort(ALL(ans));

    ITR(v, ans) {
        ITR(x, v) std::cout << x << " ";
        std::cout << "\n";
    }

    return 0;
}
