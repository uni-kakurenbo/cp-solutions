/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n, m; input >> n >> m;
    string s; input >> s;
    string t; input >> t;

    string ss = s;
    FOR(i, n - m) {
        if(s.substr(i, m) == t) {
            REP(j, i, i+m) ss[j] = '#';
        }
    }
    debug(ss);

    REP(i, n) {
        if(ss[i] != '#') {
            int j = i;
            string tt;
            while(j < n and ss[j] != '#') tt += ss[j++];

            debug(i, j, tt);

            char l = ss[i], r = ss[j-1];
            if(i == 0 and l != t[0] or j == n and r != t[m-1]) {
                print.no();
                return;
            }

            if((t + t).find(tt) != std::string::npos) CONTINUE(i = j);

            int ii = i;
            while(ii < j) {
                int k = 0;
                while(ss[ii + k] == t[k]) ++k;
                if(k == 0) {
                    break;
                }
                ii += k;
            }
            debug(ii);
            if(ii == j) CONTINUE(i = j);

            int jj = j;
            while(jj >= i) {
                int k = 0;
                while(ss[jj-k-1] == t[m-k-1]) ++k;
                if(k == 0) break;
                jj -= k;
            }
            debug(jj);
            if(jj == i) CONTINUE(i = j);

            print.no();
            return;
        }
    }

    print.yes();
}
