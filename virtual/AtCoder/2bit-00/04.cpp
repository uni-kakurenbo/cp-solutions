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

template <class T = int> struct Matrix : vector<vector<T>> {
    Matrix(size_t h, size_t w, T init = T()) : vector<vector<T>> (h, vector<T> (w, init)) {}
    inline T& operator()(size_t i, size_t j) { return (*this)[i][j]; }
};
using Point = pair<int,int>;

signed main() {
    int h, w; cin >> h >> w;
    Matrix<int> G(h, w);
    REP(i, h) REP(j, w) {
        char a; cin >> a;
        G(i,j) = (a == '#');
    }

    queue<Point> que;
    vector<int> dists(h*w, -1);

    REP(i, h) REP(j, w) {
        if(!G(i,j)) continue;
        que.emplace(i, j), dists[i*w+j] = 0;
    }

    constexpr int DI[] = { 0, 1, 0, -1 }, DJ[] = { 1, 0, -1, 0 };

    while(!que.empty()) {
        auto [i, j] = que.front(); que.pop();
        REP(d, 4) {
            int ni = i + DI[d], nj = j + DJ[d];
            if(ni < 0 or ni >= h or nj < 0 or nj >= w) continue;
            if(G(ni,nj) or dists[ni*w+nj] >= 0) continue;
            dists[ni*w+nj] = dists[i*w+j] + 1;
            que.emplace(ni, nj);
        }
    }
    debug(dists);

    cout << *max_element(ALL(dists)) << ln;

    return 0;
}
