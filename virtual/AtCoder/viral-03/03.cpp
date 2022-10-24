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


template<class I, class T = typename iterator_traits<I>::value_type, class L = int, class C = vector<pair<T,L>>> struct RLE : C {
    RLE(const I first, const I last) {
        this->clear();
        L cnt=0;;
        for(I itr=first, prev=itr; itr!=last; itr++) {
            if(*prev != *itr) this->emplace_back(*prev, cnt), cnt = 1;
            else cnt++;
            prev = itr;
        }
        this->emplace_back(*prev(last), cnt);
    }
};

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<int> S(n), T(m);
    REP(i, n) cin >> S[i];
    REP(i, m) cin >> T[i];

    RLE rle(ALL(S));

    if(rle.size() == 1) {
        if(count(ALL(T), rle[0].$F) < T.size()) {
            cout << -1 << ln;
            return 0;
        }
    }

    int s = S[0];

    int d = rle[0].$S;
    if(S[0] == S[n-1]) chmin(d, rle.rbegin()->$S + 1);
    else d = 1;

    debug(d);

    int ans = 0, f = 1;
    REP(i, m) {
        if(T[i] != s) {
            if(f) {
                ans += d;
                f = 0;
            }
            else ++ans;
            s = 1 - s;
        }
        ++ans;
    }

    cout << ans << ln;

    return 0;
}
