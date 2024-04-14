/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */

#include <bits/stdc++.h>

#include "snippet/aliases.hpp"

void solve();

signed main() {
    int $ = 1;
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        solve();
    }
    return 0;
}



void solve() {
    int n; std::cin >> n;
    std::string s; std::cin >> s;

    std::vector<std::string> seq;
    std::string cur;
    for(const auto& c : s) {
        if(c == '-') {
            if(cur != "") {
                seq.push_back(cur);
                cur.clear();
            }
            continue;
        };
        cur += c;
    }
    if(cur != "") {
        seq.push_back(cur);
    }

    int p = 0;
    int k = 0;
    int m = 0;

    for(const auto& v : seq) {
        // std::cerr << v << "\n";
        if(v.front() == 'P' and v.back() == 'P') {
            p++;
        }
        else if(v.front() == 'K' and v.back() == 'K') {
            k++;
        }
    }

    std::cout << (p > k ? "P" : "K") << "\n";
}
