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

inline void fast_io() { ios::sync_with_stdio(false), cin.tie(nullptr); }

template<class T1, class T2> inline auto mod(T1 x, T2 r) { return (x%r+r)%r; }

template<class T> inline bool chmax(T &a, T b) { return (a<b ? a=b, true : false); }
template<class T> inline bool chmin(T &a, T b) { return (a>b ? a=b, true : false); }

template<class T> auto operator<<(ostream &out, const T &val) -> decltype(val.val(), out)& {
    return out << val.val();
}
/* #endregion */

template <class T = int> struct Matrix : vector<vector<T>> {
    Matrix(size_t h, size_t w, T init = T()) : vector<vector<T>> (h, vector<T> (w, init)) {}
    inline T& operator()(size_t i, size_t j) { return (*this)[i][j]; }
};

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<int> x(n+1), y(n+1), p(m), q(m);

    REP(i, n) cin >> x[i+1] >> y[i+1];
    REP(i, m) cin >> p[i] >> q[i];

    ++n;

    Matrix<double> dp(1 << (n+m), n+m, INF64);

    // 上位 m bit: 宝箱

    auto dist = [&](int sp, int x0, int x1, int y0, int y1) {
        return hypot(x0 - x1, y0 - y1) / sp;
    };

    dp[0][0] = 0;

    REP(j, 1 << m) {
        int sp = 1 <<  __builtin_popcount(j);
        REP(k, 1 << n) {
            int l = (j << n) + k;
            REP(i, n+m) {
                int px = (i < n ? x[i] : p[i-n]);
                int py = (i < n ? y[i] : q[i-n]);
                REP(t, n+m) {
                    if(t < n) {
                        chmin(dp[l | (1 << t)][t], dp[l][i] + dist(sp, x[t], px, y[t], py));
                    }
                    else {
                        chmin(dp[l | (1 << t)][t], dp[l][i] + dist(sp, p[t-n], px, q[t-n], py));
                    }
                }
            }
        }
    }

    double ans = INF64;

    REP(i, 1 << m) {
        chmin(ans, dp[(i << n) + ((1 << n) - 1)][0]);
    }

    printf("%.18f\n", ans);


    return 0;
}
