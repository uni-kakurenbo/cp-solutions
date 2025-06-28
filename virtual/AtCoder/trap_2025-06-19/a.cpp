/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

// #include "template/standard.hpp"

void solve();

signed main() {
    // debug(__cplusplus);
    int $ = 1;
     //std::cin >> $;
    while(true){
        // debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using i64 = long;

#include "template/warnings.hpp"

int N;
string V;

int f(const string& s, int& p) {
    auto v = s[p++];
    for(auto i : std::views::iota(0, N)) {
        if(v == V[i]) return i;
    }
    assert(false);
}

int e(const string& s, int& p) {
    if(s[p] == '(') {
        ++p;
        auto v0 = e(s, p);
        auto op = s[p++];
        auto v1 = e(s, p);
        ++p;
        if(op == '<') return std::max(v0, v1);
        if(op == '>') return std::min(v0, v1);
        assert(false);
    }
    else {
        return f(s, p);
    }
}

void solve() {
    std::cin >> N;
    if(N == 0) exit(0);
    std::cin >> V;

    string s, t; cin >> s >> t;
    std::ranges::sort(V);

    // int i = 0;
    // std::cout << e(s, i) << "\n";
    i64 ans = 0;
    do {
        int i = 0, j = 0;
        ans += e(s, i) == e(t, j);
    } while(std::ranges::next_permutation(V).found);

    std::cout << ans << "\n";
}
