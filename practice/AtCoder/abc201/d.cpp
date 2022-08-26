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

template <class T = int> struct UnfoldedMatrix : vector<T> {
    UnfoldedMatrix(size_t h = 0, size_t w = 0, T init = T()) : vector<T> (h*w, init), height(h), width(w), buffer_size(h*w) {};
    inline T& operator()(size_t i, size_t j) { return (*this)[i*width+j]; }
  private:
    size_t height, width, buffer_size;
};

signed main() {
    int h, w; cin >> h >> w;

    UnfoldedMatrix<int> grid(h, w);

    REP(i, h) REP(j, w) {
        char v; cin >> v;
        grid(i,j) = v == '+' ? 1 : -1;
    }

    UnfoldedMatrix<ll> dp(h+1, w+1);
    REPD(i, h) REPD(j, w) {
        if(i == h-1 and j == w-1) continue;
        if((i+j) % 2 == 0) {
            dp(i,j) = -INF32;
            if(i < h-1) chmax(dp(i,j), dp(i+1, j) + grid(i+1,j));
            if(j < w-1) chmax(dp(i,j), dp(i, j+1) + grid(i,j+1));
        } else {
            dp(i,j) = INF32;
            if(i < h-1) chmin(dp(i,j), dp(i+1, j) - grid(i+1,j));
            if(j < w-1) chmin(dp(i,j), dp(i, j+1) - grid(i,j+1));
        }
        debug(dp);
    }

    ll diff = dp(0,0);
    debug(diff);

    if(diff == 0) { cout << "Draw" << "\n"; return 0; }
    cout << (diff > 0 ? "Takahashi" : "Aoki") << "\n";

    return 0;
}
