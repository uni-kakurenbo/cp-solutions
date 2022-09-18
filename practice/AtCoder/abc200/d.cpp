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
/* #endregion */

#include <atcoder/modint>
using mint = atcoder::static_modint<200>;
ostream& operator<<(ostream& out, const mint val) { return out << val.val(); }

template <class T = int> struct Matrix : vector<vector<T>> {
    Matrix(size_t h, size_t w, T init = T()) : vector<vector<T>> (h, vector<T> (w, init)) {}
    inline T& operator()(size_t i, size_t j) { return (*this)[i][j]; }
};

constexpr int MAX_N = 200;

signed main() {
    int n; cin >> n;
    vector<int> a(n); ITRR(v, a) cin >> v;

    array<int,200> ans0;
    fill(ALL(ans0), 0);

    FOR(mask, 1, (1 << min(8,n)) - 1) {
        pair<int,int> tmp;
        REP(i, min(8,n)) {
            if(!(mask & (1 << i))) continue;
            tmp.$F = (tmp.$F + a[i]) % 200, tmp.$S |= 1 << i;
        }
        if(ans0[tmp.$F] > 0) {
            debug(tmp, ans0[tmp.$F]);
            cout << "Yes" << ln;
            cout << __builtin_popcount(ans0[tmp.$F]) << spc;
            REP(i, min(8,n)) if(ans0[tmp.$F] & (1 << i)) cout << i+1 << spc;
            cout << ln << __builtin_popcount(tmp.$S) << spc;
            REP(i, min(8,n)) if(tmp.$S & (1 << i)) cout << i+1 << spc;
            return 0;
        }
        ans0[tmp.$F] = tmp.$S;
    }

    cout << "No" << ln;
    return 0;

    return 0;
}
