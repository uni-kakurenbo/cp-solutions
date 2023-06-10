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
#define FOR(i,a,b) for(ll i=(a), i##_last=ll(b); i<=i##_last; ++i)
#define FORD(i,a,b) for(ll i=(a), i##_last=ll(b); i>=i##_last; --i)

#define ALL(x) begin((x)),end((x))
#define RALL(x) rbegin((x)),rend((x))

#define F$ first
#define S$ second

using ll = long long;
using ull = unsigned long long;
using ld = long double;

template<class T1, class T2> inline auto mod(T1 x, T2 r) { return (x%r+r)%r; }

template<class T> inline bool chmax(T &a, T b) { return (a<b ? a=b, true : false); }
template<class T> inline bool chmin(T &a, T b) { return (a>b ? a=b, true : false); }
/* #endregion */

#include <atcoder/dsu>
using namespace atcoder;

using Bomb = pair<int,int>;
template <class T> using Graph = vector<vector<T>>;

signed main() {
    int n, r; cin >> n >> r;
    vector<Bomb> bombs(n);
    REP(i, n) cin >> bombs[i].F$ >> bombs[i].S$;

    Graph<int> G(n); // G[i] := i が爆発したときに誘爆される爆発物の集合

    FOR(i, 0, n-2) FOR(j, i+1, n-1) {
        auto [xi, yi] = bombs[i];
        auto [xj, yj] = bombs[j];
        int dx = abs(xi - xj), dy = abs(yi - yj);
        if(1LL*dx*dx + 1LL*dy*dy <= 1LL*r*r) G[i].emplace_back(j), G[j].emplace_back(i); // 距離が r 以内なら，G[i] に j を，G[j] に i を追加．
    }

    vector<int> now, nxt; // now := 爆破するものの集合, nxt := 次に爆破するものの集合
    vector<bool> exploded(n); // 爆破したか？

    now.emplace_back(0), exploded[0] = true; // 起爆装置のついているものを now に追加．爆発したことにしておく．

    while(!now.empty()) { // 爆破するものがあれば
        for(int v : now) { // now をすべて見て，
            for(int nv : G[v]) { // 誘爆されるものが
                if(exploded[nv]) continue; // まだ爆破されていなければ，
                exploded[nv] = true; // 爆破したことにしておく．
                nxt.emplace_back(nv); // 次の時刻で周りを誘爆させるようにする．
            }
        }
        now = nxt; // 時刻を進める．
        nxt.clear();
    }

    REP(i, n) {
        std::cout << (exploded[i] ? "Yes" : "No") << "\n";
    }

    return 0;
}
