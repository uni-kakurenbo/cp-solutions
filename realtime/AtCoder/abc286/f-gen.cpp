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

#include "numeric/prime_table.hpp"

inline long long mod(long long a, long long m) {
    return (a % m + m) % m;
}

long long extGcd(long long a, long long b, long long &p, long long &q) {
    if (b == 0) { p = 1; q = 0; return a; }
    long long d = extGcd(b, a%b, q, p);
    q -= a/b * p;
    return d;
}

// 中国剰余定理
// リターン値を (r, m) とすると解は x ≡ r (mod. m)
// 解なしの場合は (0, -1) をリターン
pair<long long, long long> ChineseRem(const vector<long long> &b, const vector<long long> &m) {
  long long r = 0, M = 1;
  for (int i = 0; i < (int)b.size(); ++i) {
    long long p, q;
    long long d = extGcd(M, m[i], p, q); // p is inv of M/d (mod. m[i]/d)
    if ((b[i] - r) % d != 0) return make_pair(0, -1);
    long long tmp = (b[i] - r) / d * p % (m[i]/d);
    r += M * tmp;
    M *= m[i]/d;
  }
  return make_pair(mod(r, M), M);
}

signed main() {

    int n; cin >> n;

    while(true) {
        int m; cin >> m;
        if(m == n) return 0;

        vector<int> a(m); input >> a;

        vector<int> b(m); iota(ALL(b), 1);
        REP(i, m) {
            REP(n) b[i] = a[b[i]-1];
        }
        print(b);
        cout << flush;
    }

    return 0;
}
