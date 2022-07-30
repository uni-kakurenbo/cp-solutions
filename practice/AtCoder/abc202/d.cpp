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
#define REPD(i,n) for(int i=n-1; i>=0; --i)
#define FOR(i,a,b) for(ll i=a, i##_last=ll(b); i<=i##_last; ++i)
#define FORD(i,a,b) for(ll i=a, i##_last=ll(b); i>=i##_last; --i)
#define FORA(i,I) for(auto& i:I)

#define ALL(x) begin(x),end(x)
#define RALL(x) rbegin(x),rend(x)

#define F$ first
#define S$ second

#define MOD$(x,r) ((x)%(r)+(r))%(r)

using ll = long long;
using ull = unsigned long long;

template<class T> inline T mod(T &x, T &r) { return (x%r+r)%r; }

template<class T> inline bool chmax(T &a, T b) { return (a<b ? a=b, true : false); }
template<class T> inline bool chmin(T &a, T b) { return (a>b ? a=b, true : false); }
/* #endregion */

map<pair<ll,ll>,ll> memo;

ll sum(ll lev, ll n) {
    if(memo[{lev,n}] > 0) return memo[{lev,n}];
    if(lev == 0) return 1;
    if(n == 0) return 0;
    return memo[{lev,n}] = sum(lev, n-1) + sum(lev-1, n);
}

signed main() {
    ll a, b, k; cin >> a >> b >> k;

    vector<int> vec(a+b);
    ll base = 0, p_j = 0, p_pos = a+b+1;
    FORD(i, a-1, 0) {
        ll top = 0;
        FORD(j, b+1-p_j, 0) {
            top += sum(i, j);
            ll t = sum(i, j);
            debug(i, j, base, t, top, base + top);
            if(base + top >= k) {
                base += top - sum(i, j);
                debug(base, p_pos, b+2-p_j-j, p_pos - (b+3-p_j-j));

                vec[p_pos - (b+3-p_j-j)] = 1;
                p_pos -= (b+2-p_j-j);
                p_j = b+1-p_j-j;
                break;
            }
        }
    }
    debug(vec);
    reverse(ALL(vec));

    string ans;
    FORA(v, vec) ans += v ? 'a' : 'b';
    cout << ans << "\n";

    return 0;
}
