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

template <class T> using Graph = vector<vector<T>>;

signed main() {
    int n, m; cin >> n >> m;
    int sqrt_m = ceil(sqrt(m));
    Graph<int> G(n*n);

    auto id = [&](int i, int j) { return i*n + j; };

    REP(i, n) REP(j, n) {
        auto &g = G[id(i,j)];
        FOR(ti, 0, sqrt_m+1) {
            int tj = sqrt(m - ti*ti);
            if (ti*ti + tj*tj == m) {
                int pi = i + ti, pj = j + tj;
                int qi = i + tj, qj = j + ti;
                int ri = i - ti, rj = j - tj;
                int si = i - tj, sj = j - ti;

                int wi = i - ti, wj = j + tj;
                int xi = i - tj, xj = j + ti;
                int yi = i + ti, yj = j - tj;
                int zi = i + tj, zj = j - ti;

                if(0 <= pi and pi < n and 0 <= pj and pj < n) g.push_back(id(pi,pj));
                if(0 <= qi and qi < n and 0 <= qj and qj < n) g.push_back(id(qi,qj));
                if(0 <= ri and ri < n and 0 <= rj and rj < n) g.push_back(id(ri,rj));
                if(0 <= si and si < n and 0 <= sj and sj < n) g.push_back(id(si,sj));

                if(0 <= wi and wi < n and 0 <= wj and wj < n) g.push_back(id(wi,wj));
                if(0 <= xi and xi < n and 0 <= xj and xj < n) g.push_back(id(xi,xj));
                if(0 <= yi and yi < n and 0 <= yj and yj < n) g.push_back(id(yi,yj));
                if(0 <= zi and zi < n and 0 <= zj and zj < n) g.push_back(id(zi,zj));
            }
        }
    }
    // debug(G);
    // debug(G[21]);

    queue<int> que;
    vector<int> dists(n*n, -1);

    que.push(0), dists[0] = 0;
    while(!que.empty()) {
        int v = que.front(); que.pop();
        // debug(v);
        for(int nv : G[v]) {
            // debug(nv);
            if(dists[nv] >= 0) continue;
            dists[nv] = dists[v] + 1;
            que.push(nv);
        }
    }

    REP(i, n) {
        REP(j, n) {
            cout << dists[id(i,j)] << spc;
        }
        cout << ln;
    }

    return 0;
}
