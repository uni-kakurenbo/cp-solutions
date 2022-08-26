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

template<class T> inline T mod(T x, T r) { return (x%r+r)%r; }

template<class T> inline bool chmax(T &a, T b) { return (a<b ? a=b, true : false); }
template<class T> inline bool chmin(T &a, T b) { return (a>b ? a=b, true : false); }
/* #endregion */

template<class I, class T = typename iterator_traits<I>::value_type, class L = int, class C = vector<pair<T,L>>> struct RLE : C {
    RLE(I first, I last) {
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

bool solve(string ss) {
    vector<char> s;
    for(char c : ss) s.emplace_back(c);
    int n = s.size();

    debug(s);
    FORD(i, n-1, 1) {
        if(s[n-i-1] == 'B' and (s[n-i] == 'A' or s[i] == 'A')) {
            s[i] = 'B', s[i-1] = 'A';
        }
        debug(s);
    }

    vector<char> t = s;
    reverse(ALL(t));

    return s == t;
}

signed main() {
    int n; cin >> n;
    string s; cin >> s;
    cout << (solve(s) ? "Yes" : "No") << "\n";
    return 0;
}
