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


namespace Internal {
    template<class T> T max(T a, T b) { return std::max(a, b); }
    template<class T> T min(T a, T b) { return std::min(a, b); }
}

template<class T, T (*op)(T,T)> struct Applier {
    Applier(T v) : _v(v) {}
    template<class U> Applier& operator=(U&& val) & noexcept {
        _v = op(_v, forward<U>(val));
        return *this;
    }
    T val() const { return _v; }

  private:
    T _v;
};

template<class T> using Max = Applier<T,Internal::max<T>>;
template<class T> using Min = Applier<T,Internal::min<T>>;

template<class T> vector<T> divisors(T n) {
    vector<T> res;
    for (T i=1; i*i<=n; i++) {
        if (n%i == 0) {
            res.emplace_back(i);
            if(i*i < n) res.emplace_back(n/i);
        }
    }
    sort(ALL(res));
    return res;
}

template<class T = int, class C = vector<T>> struct Primes : C {
    Primes(size_t max) : is_prime(max+1, true) {
        is_prime[0] = is_prime[1] = false;
        for(size_t p=2; p<=max; p++) if(is_prime[p]) {
            for(size_t i=p*p; i<=max; i+=p) is_prime[i] = false;
            this->emplace_back(p);
        }
    }
    bool operator()(size_t index) {
        return is_prime[index];
    }
  private:
    vector<bool> is_prime;
};

signed main() {
    int n; cin >> n;
    vector<int> a(n); ITRR(v, a) cin >> v;
    sort(ALL(a));

    vector<int> b(n-1);
    REP(i, n-1) {
        b[i] = a[i+1] - a[i];
    }
    debug(b);

    int accgcd = *a.rbegin() - a[0];
    ITR(v, a) accgcd = gcd(accgcd, *a.rbegin() - v);
    ITR(v, a) accgcd = gcd(accgcd, v - a[0]);
    ITR(v, b) accgcd = gcd(accgcd, v);
    debug(accgcd);


    if(accgcd != 1) {
        cout << 1 << ln;
        return 0;
    }

    cout << 2 << ln;

    return 0;
}
