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

template <class T = int> struct Matrix : vector<vector<T>> {
    Matrix(size_t h, size_t w, T init = T()) : vector<vector<T>> (h, vector<T> (w, init)) {}
    inline T& operator()(size_t i, size_t j) { return (*this)[i][j]; }
};

signed main() {
    int h1, w1; cin >> h1 >> w1;
    Matrix<int> A(h1, w1);
    REP(i, h1) REP(j, w1) cin >> A(i,j);

    int h2, w2; cin >> h2 >> w2;
    Matrix<int> B(h2, w2);
    REP(i, h2) REP(j, w2) cin >> B(i,j);

    debug(A, B);

    REP(mask_v, 1<<h1) {
        REP(mask_h, 1<<w1) {
            int cnt_v = 0, cnt_h = 0;
            Matrix C = A;
            REP(i, h1) {
                if((mask_v >> i) & 1) {
                    C.erase(C.begin() + i - cnt_v);
                    ++cnt_v;
                }
            }
            REP(j, w1) {
                if((mask_h >> j) & 1) {
                    for(vector<int> &row : C) row.erase(row.begin() + j - cnt_h);
                    ++cnt_h;
                }
            }
            if(C == B) {
                cout << "Yes" << "\n";
                return 0;
            }
        }
    }

    cout << "No" << "\n";

    return 0;
}
