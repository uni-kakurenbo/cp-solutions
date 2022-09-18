/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region tmplate */
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL_JUDGE
    #include<debug>
    #define debug(...) Debug::debug(Debug::split(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
    #define DEBUG(...) do { Debug::DEBUG(nullptr, "\033[3;35m#" + to_string(__LINE__) + "\033[m  "); Debug::DEBUG(__VA_ARGS__); Debug::DEBUG(nullptr, "\033[m\n"); } while(0);
#else
    #define debug(...) { ; }
    #define DEBUG(...) { ; }
#endif

#define INF32 2147483647
#define INF64 9223372036854775807LL

#define until(...) while(!(__VA_ARGS__))

#define REP(i,n) for(int i=0, i##_length=int(n); i<i##_length; ++i)
#define REPD(i,n) for(int i=(n)-1; i>=0; --i)
#define LOOP(n) REP(_$, (n))
#define FOR(i,l,r) for(ll i=(l), i##_last=ll(r); i<=i##_last; ++i)
#define FORD(i,l,r) for(ll i=(l), i##_last=ll(r); i>=i##_last; --i)

#define ITRP(x,v) for(auto x : (v))
#define ITRR(x,v) for(auto &x : (v))
#define ITR(x,v) for(const auto &x : (v))
#define ITRMP(x,y,v) for(auto [x, y] : (v))
#define ITRMR(x,y,v) for(auto &[x, y] : (v))
#define ITRM(x,y,v) for(const auto [x, y] : (v))

#define ALL(x) begin((x)),end((x))
#define RALL(x) rbegin((x)),rend((x))

#define $F first
#define $S second

using ll = long long;
using ull = unsigned long long;
using ld = long double;

constexpr char ln = '\n';
constexpr char spc = ' ';

template<class T1, class T2> inline auto mod(T1 x, T2 r) { return (x%r+r)%r; }

template<class T> inline bool chmax(T &a, T b) { return (a<b ? a=b, true : false); }
template<class T> inline bool chmin(T &a, T b) { return (a>b ? a=b, true : false); }

template<class T> auto operator<<(ostream &out, const T &val) -> decltype(val.val(), out)& {
    return out << val.val();
}
/* #endregion */

signed main() {
    int n, m; cin >> n >> m;

    vector<string> S(n);
    unordered_set<string> T(m);

    ITRR(s, S) cin >> s;
    LOOP(m) { string t; cin >> t; T.emplace(t); }

    stack<pair<bitset<8>,string>> stk;
    stk.emplace(0, "");

    until(stk.empty()) {
        auto [used, curr] = stk.top(); stk.pop();
        // debug(curr);

        if(curr.size() > 16) continue;

        if((int)used.count() == n-1) {
            int i=0;
            while(used.test(i)) ++i;

            curr += S[i];

            int sz = curr.size();
            if(sz < 3 || 16 < sz) continue;

            if(T.count(curr)) continue;

            cout << curr << ln;
            return 0;
        }

        REP(i, n) {
            if(used.test(i)) continue;
            FOR(j, 1, 16-(int)curr.size()) {
                // debug(j);
                stk.emplace(used | bitset<8>().set(i), curr + S[i] + string(j,'_'));
            }
        }
    }

    cout << -1 << ln;

    return 0;
}
