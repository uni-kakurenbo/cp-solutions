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

struct Edge {
    int id, to; ll cost;
    Edge(int i, int t, ll w) : id(i), to(t), cost(w) {}
};
template <class T> using Graph = vector<vector<T>>;

void dijkstra(const Graph<Edge> &G, const vector<vector<int>> &dict, vector<ll> *dists) {
    using State = tuple<ll,int,int>;
    priority_queue<State,vector<State>,greater<State>> que;

    que.emplace(0, -1, 0), (*dists)[0] = 0;

    while(!que.empty()) {
        auto [d, p, u] = que.top(); que.pop();
        debug(d, p, u);

        if((*dists)[u] < d) continue;

        for(const Edge &e : G[u]) {
            int i = e.id, v = e.to; ll cost = e.cost;
            debug(i, v, cost);

            if((*dists)[v] < d + cost) continue;

            auto np_itr = upper_bound(ALL(dict[i]), p);
            if(np_itr == dict[i].end()) continue;

            (*dists)[v] = d + cost;
            que.emplace((*dists)[v], *np_itr, v);
        }
    }

    return;
}

constexpr ll MAX_COST = 1000000000000000LL;

signed main() {
    int n, m, k; cin >> n >> m >> k;

    Graph<Edge> G(n);
    REP(i, m) {
        int a, b, c; cin >> a >> b >> c; --a, --b;
        G[a].emplace_back(i, b, c);
    }

    vector<int> e(k);
    REP(i, k) {
        cin >> e[i];
        --e[i];
    }

    vector<vector<int>> dict(m);
    REP(i, k) {
        dict[e[i]].push_back(i);
    }
    debug(dict);

    REP(i, n) sort(RALL(G[i]), [&](Edge &a, Edge &b) { return dict[a.id].size() < dict[b.id].size(); });

    vector<ll> dists(n, MAX_COST);
    dijkstra(G, dict, &dists);
    debug(dists);

    if(dists[n-1] >= MAX_COST) {
        cout << -1 << ln;
        return 0;
    }

    cout << dists[n-1] << ln;

    return 0;
}
