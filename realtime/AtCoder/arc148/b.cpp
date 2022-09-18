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

string f(string s) {
    int n = s.size();
    string t(n, ' ');
    REP(i, n) t[i] = s[n-i-1] == 'p' ? 'd' : 'p';
    return t;
}

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

signed main() {
    int n; cin >> n;
    string s; cin >> s;


    RLE rle(ALL(s));
    debug(rle);

    if(rle[0].$F == 'p') {
        string t = s;
        string u = f(s.substr(0, rle[0].$S));
        REP(i, rle[0].$S) t[i] = u[i];
        cout << min(s, t) << ln;
    }

    if(rle[0].$F == 'd') {
        int m = 0, ind = 0, c = 0, isum = 0;
        FORD(i, rle.size()-1, 1) {
            isum += rle[i].$S;
            if(rle[i].$F == 'd') continue;
            if(chmax(m, rle[i].$S)) {
                ind = isum;
                c = i;
            }
        }
        debug(m, c, ind);
        int l = rle[0].$S, r = n - ind + m;
        debug(l, r);
        string t = s;
        string u = f(s.substr(l, r-l));
        REP(x, r-l) t[l+x] = u[x];
        cout << min(s, t) << ln;
    }

    #ifndef LOCAL_JUDGE
        return 0;
    #endif

    Min<string> ans = s;

    FOR(i, 0, n-1) FOR(j, i, n) {
        string u = f(s.substr(i, j-i));
        // debug(i, j, u, s.substr(i, j-i));
        string t = s;
        REP(x, j-i) t[i+x] = u[x];
        ans = t;
    }

    debug(ans.val());

    return 0;
}
