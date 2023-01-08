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
/* #endregion */

#define B1 100000007
#define B2 1000000007

void solve(string const& S, int m){
    // B^mを用意する
    ull pow_B_m_1 = 1, pow_B_m_2 = 1;
    for(int k = 0; k < m; k++){
        pow_B_m_1 *= B1, pow_B_m_2 *= B2;
    }

    // sとtの先頭m文字のハッシュ値sh,thを計算
    ull sh1 = 0, sh2 = 0, th1 = 0, th2 = 0;
    for(int k = 0; k < m; k++){
        sh1 = sh1 * B1 + S[k], sh2 = sh2 * B2 + S[k];
        th1 = th1 * B1 + S[S.size()-k-1], th2 = th2 * B2 + S[S.size()-k-1];
    }

    // sをずらしてハッシュ値を更新
    for(int k = 0; m + k < S.length(); k++){
        debug(k, m+k);
        debug(sh1, sh2);
        debug(th1, th2);
        if(sh1 == th1 && sh2 == th2) {
            debug(k);
            print(S.substr(k, m));
            print(k);
            return;
        }
        sh1 = sh1 * B1 + S[m + k] - S[k] * pow_B_m_1;
        sh2 = sh2 * B2 + S[m + k] - S[k] * pow_B_m_2;

        th1 = th1 * B1 + S[k] - S[m + k];
        th2 = th2 * B2 + S[k] - S[m + k];
    }
    print(-1);
    return;
}

signed main() {
    int n; cin >> n;
    string s; cin >> s;
    solve(s, n);
    return 0;
}
