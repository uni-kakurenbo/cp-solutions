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

template<class T1, class T2> inline auto mod(T1 x, T2 r) { return (x%r+r)%r; }

template<class T> inline bool chmax(T &a, T b) { return (a<b ? a=b, true : false); }
template<class T> inline bool chmin(T &a, T b) { return (a>b ? a=b, true : false); }
/* #endregion */


namespace Internal {
    template<class T> T max(T a, T b) { return std::max(a, b); }
    template<class T> T min(T a, T b) { return std::min(a, b); }
}

template<class T, T (*op)(T,T)> struct Apply {
    Apply(T v) : _v(v) {}
    template<class U> Apply& operator=(U&& val) & noexcept {
        _v = op(_v, forward<U>(val));
        return *this;
    }
    T val() const { return _v; }

  private:
    T _v;
};

template<class T> using Max = Apply<T,Internal::max<T>>;
template<class T> using Min = Apply<T,Internal::min<T>>;

struct Edge {
    int to; ll cost;
    Edge(int t, ll w) : to(t), cost(w) {}
    vector<ll> _debug() { return { to, cost }; };
};
template <class T> using Graph = vector<vector<T>>;

void dijkstra(const Graph<Edge> &G, int s, vector<ll> *dists) {
    using State = pair<ll,int>;
    priority_queue<State,vector<State>,greater<State>> que;

    que.emplace(0, s), (*dists)[s] = 0;

    while(!que.empty()) {
        ll d; int u; tie(d, u) = que.top(), que.pop();

        if((*dists)[u] < d) continue;

        for(const Edge &e : G[u]) {
            int v = e.to; ll cost = e.cost;

            if((*dists)[v] <= d + cost) continue;

            (*dists)[v] = d + cost;
            que.emplace((*dists)[v], v);
        }
    }

    return;
}

signed main() {
    int n, m; cin >> n >> m;
    vector<ll> h(n); ITRR(v, h) cin >> v;

    Graph<Edge> G(n);
    LOOP(m) {
        int u, v; cin >> u >> v; --u, --v;
        if(h[v] > h[u]) swap(u, v);
        G[v].emplace_back(u, h[u]-h[v]), G[u].emplace_back(v, 0);
    }
    debug(G);

    vector<ll> res(n, INF64);
    dijkstra(G, 0, &res);

    debug(res);

    Max<ll> ans = 0;
    REP(i, n) ans = h[0] - h[i] - res[i];

    cout << ans.val() << ln;

    return 0;
}
