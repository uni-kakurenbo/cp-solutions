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

template <class T = int> struct UnfoldedMatrix : vector<T> {
    UnfoldedMatrix(size_t h = 0, size_t w = 0, T init = T()) : vector<T> (h*w, init), height(h), width(w), buffer_size(h*w) {};
    inline T& operator()(size_t i, size_t j) { return (*this)[i*width+j]; }
  private:
    size_t height, width, buffer_size;
};

template<class I, class T = typename iterator_traits<I>::value_type, class C = vector<T>>
struct Compress : C {
    vector<T> values;
    Compress() {}
    Compress(const I first, const I last) {
        this->values.assign(first, last);
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
        this->resize(distance(first, last));
        for(auto itr=this->begin(),val=values.begin(),e=first; e!=last; ++itr,++val,++e) {
            *itr = distance(values.begin(), lower_bound(values.begin(), values.end(), *e));
        }
    }
    inline T operator()(const T e) const {
        return values[e];
    }
};

template<class I, class T = typename iterator_traits<I>::value_type, class C = unordered_map<T,int>>
struct Counter : C {
    Counter(const I first, const I last) {
        for(auto itr=first; itr!=last; ++itr) ++(*this)[*itr];
    }
    inline T operator()(T val) const {
        return (*this)[val];
    }
};

namespace Internal {
    template<class T> T max(T a, T b) { return std::max(a, b); }
    template<class T> T min(T a, T b) { return std::min(a, b); }
}

template<class T, T (*op)(T,T)> struct Apply {
    Apply(T&& v) : _v(v) {}
    template<class U> Apply& operator<<=(U&& val) & noexcept {
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
    int n, k; cin >> n >> k;

    UnfoldedMatrix<int> A(n,n);
    REP(i, n) REP(j, n) cin >> A(i,j);
    Compress comped(ALL(A));

    Min<int> ans = INF32;

    REP(i, n) {

    }

    return 0;
}
