/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

// #include "template/standard.hpp"

// #include "template/warnings.hpp"
// #include "template/debug.hpp"
#include <bits/stdc++.h>
// #include "template/using.hpp"

void solve();

signed main() {
    // debug(R);

    // debug(__cplusplus);
    // int $ = 1;
    // std::cin >> $;
    while(true) {
        // debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

bool VALS[12]{};

bool literal(std::string &s, int &i) {
    auto val = s[i++];
    if(val == 'T') return true;
    if(val == 'F') return false;
    return VALS[val - 'a'];
}

bool is_literal(char x) {
    return x == 'T' || x == 'F' || ('a' <= x && x <= 'z');
}

bool formula(std::string &s, int &i) {
    // std::cerr << s[i] << "\n";

    if(is_literal(s[i])) return literal(s, i);

    if(s[i] == '-') {
        ++i;
        return !formula(s, i);
    }

    assert(s[i++] == '(');

    auto val = formula(s, i);

    bool res;

    if(s[i] == '*') {
        ++i;
        // std::cerr << "*: " << s[i] << "; ";
        // std::cerr << is_literal(s[i]) << "\n";

        auto val1 = formula(s, i);
        res = val && val1;
    }
    else if(s[i] == '+') {
        ++i;
        auto val1 = formula(s, i);
        res = val || val1;
    }
    else if(s[i] == '-') {
        ++i;

        assert(s[i++] == '>');

        auto val1 = formula(s, i);
        res = !val || val1;
    }

    assert(s[i++] == ')');

    return res;
}

void solve() {
    std::string s; std::cin >> s;

    if(s == "#") {
        exit(0);
    }

    int t = s.find('=');
    std::string s0 = s.substr(0, t), s1 = s.substr(t + 1);
    // std::cerr << s0 << ", " << s1 << "\n";

    for(int x=0; x<=(1L << 11); ++x) {
        for(int i=0; i<11; ++i) {
            VALS[i] = (x >> i) & 1;
        }

        int i0 = 0;
        int i1 = 0;

        bool a = formula(s0, i0), b = formula(s1, i1);

        if(a != b) {
            // std::cerr << a << ", " << b << "\n";
            std::cout << "NO\n";
            return;
        }
    }

    std::cout << "YES" << "\n";
}
