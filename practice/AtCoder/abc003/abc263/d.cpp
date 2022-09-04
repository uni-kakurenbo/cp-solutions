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

template<class I, class T = typename iterator_traits<I>::value_type, class C = vector<T>> struct PrefixSum : C {
    PrefixSum(I first, I last, T head = T()) {
        this->assign(distance(first,last)+1, head);
        for(auto i=size_t(1), itr=first; itr!=last; i++) {
            (*this)[i] = (*this)[i-1] + *itr++;
        }
    }
    inline T operator()(size_t left, size_t right) {
        return (*this)[right] - (*this)[left];
    }
};

signed main() {
    ll n, l, r; cin >> n >> l >> r;
    vector<ll> a(n); REP(i, n) cin >> a[i];

    PrefixSum sum_l(ALL(a), 0LL);
    PrefixSum sum_r(RALL(a), 0LL);
    debug(sum_l, sum_r);

    vector<ll> lv(n+1), rv(n+1);
    FOR(i, 0, n) {
        lv[i] = sum_l[i] - l*i;
        rv[i] = sum_r[i] - r*i;
    }

    FOR(i, 1, n) rv[i] = max(rv[i-1], rv[i]);
    debug(lv, rv);

    ll ans = INF64;
    REP(x, n+1) {
        chmin(ans, sum_l.back() - lv[x] - rv[n-x]);
    }

    cout << ans << "\n";

    return 0;
}
