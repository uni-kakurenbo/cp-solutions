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

constexpr int DIS[] = { 0, -1, 0, 1 }, DJS[] = { -1, 0, 1, 0 };

signed main() {
    int h, w; cin >> h >> w;
    int rs, cs; cin >> rs >> cs; --rs, --cs;
    int n; cin >> n;

    vector<int> r(n), c(n);
    REP(i, n) {
        cin >> r[i] >> c[i];
        --r[i], --c[i];
    }

    int q; cin >> q;
    vector<char> d(q);
    vector<int> l(q);

    REP(i, q) {
        cin >> d[i] >> l[i];
    }

    debug(h, w, q, d, l);

    unordered_map<int,vector<int>> walls_s, walls_v;

    REP(i, n) {
        walls_s[r[i]].push_back(c[i]);
        walls_v[c[i]].push_back(r[i]);
    }
    for(auto &[_, v] : walls_s) {
        v.push_back(-1), v.push_back(w);
        sort(ALL(v));
    }
    for(auto &[_, v] : walls_v) {
        v.push_back(-1), v.push_back(h);
        sort(ALL(v));
    }

    debug(walls_s, walls_v);

    int i = rs, j = cs;
    debug(i, j);
    REP(k, q) {
        if(walls_s[i].empty()) walls_s[i].push_back(-1), walls_s[i].push_back(w);
        if(walls_v[j].empty()) walls_v[j].push_back(-1), walls_v[j].push_back(h);
        debug(walls_s[i], walls_v[j]);

        char di = d[k];
        int ti = l[k];

        int dist = 0, d = 0;
        if(di == 'R') dist = *upper_bound(ALL(walls_s[i]), j) - j - 1, d = 2;
        if(di == 'L') dist = j - *prev(upper_bound(ALL(walls_s[i]), j)) - 1, d = 0;
        if(di == 'U') dist = i - *prev(upper_bound(ALL(walls_v[j]), i)) - 1, d = 1;
        if(di == 'D') dist = *upper_bound(ALL(walls_v[j]), i) - i - 1, d = 3;

        chmin(ti, dist);
        debug(di, *upper_bound(ALL(walls_v[j]), i), *upper_bound(ALL(walls_s[i]), j));

        i += DIS[d] * ti;
        j += DJS[d] * ti;
        debug(d, dist, ti, i, j);
        cout << i + 1 << spc << j + 1 << ln;
    }

    return 0;
}
