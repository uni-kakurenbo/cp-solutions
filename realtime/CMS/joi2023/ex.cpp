/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

/* #expanded [template.hpp] */
/* #expanded [aliases.hpp] */
/* #expanded [types.hpp] */
using ll = long long;using ull = unsigned long long;using ld = long double;
/* [types.hpp] */
#define until(...) while(!(__VA_ARGS__))
#define ALL(x) std::begin((x)),std::end((x))
#define RALL(x) std::rbegin((x)),std::rend((x))
#define $F first
#define $S second
constexpr char ln = '\n';constexpr char spc = ' ';
#include <utility>
constexpr std::pair<int,int> DIRS4[] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };constexpr std::pair<int,int> DIRS8[] = { { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 } };template<class T1, class T2> inline auto mod(T1 x, T2 r) { return (x%r+r)%r; }template<class T1, class T2> inline bool chmax(T1 &a, T2 b) { return (a<b ? a=b, true : false); }template<class T1, class T2> inline bool chmin(T1 &a, T2 b) { return (a>b ? a=b, true : false); }
/* [aliases.hpp] */
/* #expanded [iterations.hpp] */
/* #expanded [overload.hpp] */
#define $OVERLOAD2(arg0, arg1, cmd, ...) cmd
#define $OVERLOAD3(arg0, arg1, arg2, cmd, ...) cmd
#define $OVERLOAD4(arg0, arg1, arg2, arg3, cmd, ...) cmd
#define $OVERLOAD5(arg0, arg1, arg2, arg3, arg4, cmd, ...) cmd
/* [overload.hpp] */
#define LOOP(n) REPI($_, (n))
#define REPI(i,n) for(int i=0, i##_length=int(n); i<i##_length; ++i)
#define REPF(i,l,r) for(auto i=(l), i##_last=(r); i!=i##_last; ++i)
#define REPIS(i,l,r,s) for(auto i=(l), i##_last=(r); i!=i##_last; i+=(s))
#define REPR(i,n) for(auto i=(n); --i>=0;)
#define REPB(i,l,r) for(auto i=(r), i##_last=(l); --i>=i##_last;)
#define REPRS(i,l,r,s) for(auto i=(r), i##_last=(l); (i-=(s))>=i##_last;)
#define REP(...) $OVERLOAD4(__VA_ARGS__, REPIS, REPF, REPI, LOOP)(__VA_ARGS__)
#define REPD(...) $OVERLOAD4(__VA_ARGS__, REPRS, REPB, REPR)(__VA_ARGS__)
#define FORI(i,l,r) for(auto i=(l), i##_last=(r); i<=i##_last; ++i)
#define FORIS(i,l,r,s) for(auto i=(l), i##_last=(r); i<=i##_last; i+=(s))
#define FORR(i,l,r) for(auto i=(r), i##_last=(l); i>=i##_last; --i)
#define FORRS(i,l,r,s) for(auto i=(r), i##_last=(l); i>=i##_last; i-=(s))
#define FOR(...) $OVERLOAD4(__VA_ARGS__, FORIS, FORI)(__VA_ARGS__)
#define FORD(...) $OVERLOAD4(__VA_ARGS__, FORRS, FORR)(__VA_ARGS__)
#define ITR1(e0,v) for(const auto &e0 : (v))
#define ITRP1(e0,v) for(auto e0 : (v))
#define ITRR1(e0,v) for(auto &e0 : (v))
#define ITR2(e0,e1,v) for(const auto [e0, e1] : (v))
#define ITRP2(e0,e1,v) for(auto [e0, e1] : (v))
#define ITRR2(e0,e1,v) for(auto &[e0, e1] : (v))
#define ITR3(e0,e1,e2,v) for(const auto [e0, e1, e2] : (v))
#define ITRP3(e0,e1,e2,v) for(auto [e0, e1, e2] : (v))
#define ITRR3(e0,e1,e2,v) for(auto &[e0, e1, e2] : (v))
#define ITR4(e0,e1,e2,e3,v) for(const auto [e0, e1, e2, e3] : (v))
#define ITRP4(e0,e1,e2,e3,v) for(auto [e0, e1, e2, e3] : (v))
#define ITRR4(e0,e1,e2,e3,v) for(auto &[e0, e1, e2, e3] : (v))
#define ITR(...) $OVERLOAD5(__VA_ARGS__, ITR4, ITR3, ITR2, ITR1)(__VA_ARGS__)
#define ITRP(...) $OVERLOAD5(__VA_ARGS__, ITRP4, ITRP3, ITRP2, ITRP1)(__VA_ARGS__)
#define ITRR(...) $OVERLOAD5(__VA_ARGS__, ITRR4, ITRR3, ITRR2, ITRR1)(__VA_ARGS__)
/* [iterations.hpp] */
/* #expanded [fast_io.hpp] */
#include <iostream>
#ifdef __GNUC__
__attribute__((constructor)) inline void fast_io() { std::ios::sync_with_stdio(false), std::cin.tie(nullptr); }
#else
inline void fast_io() { std::ios::sync_with_stdio(false), std::cin.tie(nullptr); }
#endif
/* [fast_io.hpp] */
#ifdef LOCAL_JUDGE
#include<debug>
#define debug(...) debugger::debug(debugger::split(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#define DEBUG(...) do { debugger::DEBUG(nullptr, "\033[3;35m#" + to_string(__LINE__) + "\033[m "); debugger::DEBUG(__VA_ARGS__); debugger::DEBUG(nullptr, "\033[m\n"); } while(0);
#else
#define debug(...) ({ ; })
#define DEBUG(...) ({ ; })
#endif
/* #expanded [input.hpp] */
/* #expanded [modint] */
/* #expanded [modint.hpp] */
#include <cassert>
#include <numeric>
#include <type_traits>
#ifdef _MSC_VER
#include <intrin.h>
#endif
/* #expanded [internal_math] */
/* #expanded [internal_math.hpp] */
#include <utility>
#ifdef _MSC_VER
#include <intrin.h>
#endif
namespace atcoder {namespace internal {constexpr long long safe_mod(long long x, long long m) {x %= m;if (x < 0) x += m;return x;}struct barrett {unsigned int _m;unsigned long long im;explicit barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}unsigned int umod() const { return _m; }unsigned int mul(unsigned int a, unsigned int b) const {unsigned long long z = a;z *= b;
#ifdef _MSC_VER
unsigned long long x;_umul128(z, im, &x);
#else
unsigned long long x =(unsigned long long)(((unsigned __int128)(z)*im) >> 64);
#endif
unsigned int v = (unsigned int)(z - x * _m);if (_m <= v) v += _m;return v;}};constexpr long long pow_mod_constexpr(long long x, long long n, int m) {if (m == 1) return 0;unsigned int _m = (unsigned int)(m);unsigned long long r = 1;unsigned long long y = safe_mod(x, m);while (n) {if (n & 1) r = (r * y) % _m;y = (y * y) % _m;n >>= 1;}return r;}constexpr bool is_prime_constexpr(int n) {if (n <= 1) return false;if (n == 2 || n == 7 || n == 61) return true;if (n % 2 == 0) return false;long long d = n - 1;while (d % 2 == 0) d /= 2;constexpr long long bases[3] = {2, 7, 61};for (long long a : bases) {long long t = d;long long y = pow_mod_constexpr(a, t, n);while (t != n - 1 && y != 1 && y != n - 1) {y = y * y % n;t <<= 1;}if (y != n - 1 && t % 2 == 0) {return false;}}return true;}template <int n> constexpr bool is_prime = is_prime_constexpr(n);constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {a = safe_mod(a, b);if (a == 0) return {b, 0};long long s = b, t = a;long long m0 = 0, m1 = 1;while (t) {long long u = s / t;s -= t * u;m0 -= m1 * u;auto tmp = s;s = t;t = tmp;tmp = m0;m0 = m1;m1 = tmp;}if (m0 < 0) m0 += b / s;return {s, m0};}constexpr int primitive_root_constexpr(int m) {if (m == 2) return 1;if (m == 167772161) return 3;if (m == 469762049) return 3;if (m == 754974721) return 11;if (m == 998244353) return 3;int divs[20] = {};divs[0] = 2;int cnt = 1;int x = (m - 1) / 2;while (x % 2 == 0) x /= 2;for (int i = 3; (long long)(i)*i <= x; i += 2) {if (x % i == 0) {divs[cnt++] = i;while (x % i == 0) {x /= i;}}}if (x > 1) {divs[cnt++] = x;}for (int g = 2;; g++) {bool ok = true;for (int i = 0; i < cnt; i++) {if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {ok = false;break;}}if (ok) return g;}}template <int m> constexpr int primitive_root = primitive_root_constexpr(m);unsigned long long floor_sum_unsigned(unsigned long long n,unsigned long long m,unsigned long long a,unsigned long long b) {unsigned long long ans = 0;while (true) {if (a >= m) {ans += n * (n - 1) / 2 * (a / m);a %= m;}if (b >= m) {ans += n * (b / m);b %= m;}unsigned long long y_max = a * n + b;if (y_max < m) break;n = (unsigned long long)(y_max / m);b = (unsigned long long)(y_max % m);std::swap(m, a);}return ans;}}}
/* [internal_math.hpp] */
/* [internal_math] */
/* #expanded [internal_type_traits] */
/* #expanded [internal_type_traits.hpp] */
#include <cassert>
#include <numeric>
#include <type_traits>
namespace atcoder {namespace internal {
#ifndef _MSC_VER
template <class T>using is_signed_int128 =typename std::conditional<std::is_same<T, __int128_t>::value ||std::is_same<T, __int128>::value,std::true_type,std::false_type>::type;template <class T>using is_unsigned_int128 =typename std::conditional<std::is_same<T, __uint128_t>::value ||std::is_same<T, unsigned __int128>::value,std::true_type,std::false_type>::type;template <class T>using make_unsigned_int128 =typename std::conditional<std::is_same<T, __int128_t>::value,__uint128_t,unsigned __int128>;template <class T>using is_integral = typename std::conditional<std::is_integral<T>::value ||is_signed_int128<T>::value ||is_unsigned_int128<T>::value,std::true_type,std::false_type>::type;template <class T>using is_signed_int = typename std::conditional<(is_integral<T>::value &&std::is_signed<T>::value) ||is_signed_int128<T>::value,std::true_type,std::false_type>::type;template <class T>using is_unsigned_int =typename std::conditional<(is_integral<T>::value &&std::is_unsigned<T>::value) ||is_unsigned_int128<T>::value,std::true_type,std::false_type>::type;template <class T>using to_unsigned = typename std::conditional<is_signed_int128<T>::value,make_unsigned_int128<T>,typename std::conditional<std::is_signed<T>::value,std::make_unsigned<T>,std::common_type<T>>::type>::type;
#else
template <class T> using is_integral = typename std::is_integral<T>;template <class T>using is_signed_int =typename std::conditional<is_integral<T>::value && std::is_signed<T>::value,std::true_type,std::false_type>::type;template <class T>using is_unsigned_int =typename std::conditional<is_integral<T>::value &&std::is_unsigned<T>::value,std::true_type,std::false_type>::type;template <class T>using to_unsigned = typename std::conditional<is_signed_int<T>::value,std::make_unsigned<T>,std::common_type<T>>::type;
#endif
template <class T>using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;template <class T>using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;template <class T> using to_unsigned_t = typename to_unsigned<T>::type;}}
/* [internal_type_traits.hpp] */
/* [internal_type_traits] */
namespace atcoder {namespace internal {struct modint_base {};struct static_modint_base : modint_base {};template <class T> using is_modint = std::is_base_of<modint_base, T>;template <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;}template <int m, std::enable_if_t<(1 <= m)>* = nullptr>struct static_modint : internal::static_modint_base {using mint = static_modint;public:static constexpr int mod() { return m; }static mint raw(int v) {mint x;x._v = v;return x;}static_modint() : _v(0) {}template <class T, internal::is_signed_int_t<T>* = nullptr>static_modint(T v) {long long x = (long long)(v % (long long)(umod()));if (x < 0) x += umod();_v = (unsigned int)(x);}template <class T, internal::is_unsigned_int_t<T>* = nullptr>static_modint(T v) {_v = (unsigned int)(v % umod());}unsigned int val() const { return _v; }mint& operator++() {_v++;if (_v == umod()) _v = 0;return *this;}mint& operator--() {if (_v == 0) _v = umod();_v--;return *this;}mint operator++(int) {mint result = *this;++*this;return result;}mint operator--(int) {mint result = *this;--*this;return result;}mint& operator+=(const mint& rhs) {_v += rhs._v;if (_v >= umod()) _v -= umod();return *this;}mint& operator-=(const mint& rhs) {_v -= rhs._v;if (_v >= umod()) _v += umod();return *this;}mint& operator*=(const mint& rhs) {unsigned long long z = _v;z *= rhs._v;_v = (unsigned int)(z % umod());return *this;}mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }mint operator+() const { return *this; }mint operator-() const { return mint() - *this; }mint pow(long long n) const {assert(0 <= n);mint x = *this, r = 1;while (n) {if (n & 1) r *= x;x *= x;n >>= 1;}return r;}mint inv() const {if (prime) {assert(_v);return pow(umod() - 2);} else {auto eg = internal::inv_gcd(_v, m);assert(eg.first == 1);return eg.second;}}friend mint operator+(const mint& lhs, const mint& rhs) {return mint(lhs) += rhs;}friend mint operator-(const mint& lhs, const mint& rhs) {return mint(lhs) -= rhs;}friend mint operator*(const mint& lhs, const mint& rhs) {return mint(lhs) *= rhs;}friend mint operator/(const mint& lhs, const mint& rhs) {return mint(lhs) /= rhs;}friend bool operator==(const mint& lhs, const mint& rhs) {return lhs._v == rhs._v;}friend bool operator!=(const mint& lhs, const mint& rhs) {return lhs._v != rhs._v;}private:unsigned int _v;static constexpr unsigned int umod() { return m; }static constexpr bool prime = internal::is_prime<m>;};template <int id> struct dynamic_modint : internal::modint_base {using mint = dynamic_modint;public:static int mod() { return (int)(bt.umod()); }static void set_mod(int m) {assert(1 <= m);bt = internal::barrett(m);}static mint raw(int v) {mint x;x._v = v;return x;}dynamic_modint() : _v(0) {}template <class T, internal::is_signed_int_t<T>* = nullptr>dynamic_modint(T v) {long long x = (long long)(v % (long long)(mod()));if (x < 0) x += mod();_v = (unsigned int)(x);}template <class T, internal::is_unsigned_int_t<T>* = nullptr>dynamic_modint(T v) {_v = (unsigned int)(v % mod());}unsigned int val() const { return _v; }mint& operator++() {_v++;if (_v == umod()) _v = 0;return *this;}mint& operator--() {if (_v == 0) _v = umod();_v--;return *this;}mint operator++(int) {mint result = *this;++*this;return result;}mint operator--(int) {mint result = *this;--*this;return result;}mint& operator+=(const mint& rhs) {_v += rhs._v;if (_v >= umod()) _v -= umod();return *this;}mint& operator-=(const mint& rhs) {_v += mod() - rhs._v;if (_v >= umod()) _v -= umod();return *this;}mint& operator*=(const mint& rhs) {_v = bt.mul(_v, rhs._v);return *this;}mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }mint operator+() const { return *this; }mint operator-() const { return mint() - *this; }mint pow(long long n) const {assert(0 <= n);mint x = *this, r = 1;while (n) {if (n & 1) r *= x;x *= x;n >>= 1;}return r;}mint inv() const {auto eg = internal::inv_gcd(_v, mod());assert(eg.first == 1);return eg.second;}friend mint operator+(const mint& lhs, const mint& rhs) {return mint(lhs) += rhs;}friend mint operator-(const mint& lhs, const mint& rhs) {return mint(lhs) -= rhs;}friend mint operator*(const mint& lhs, const mint& rhs) {return mint(lhs) *= rhs;}friend mint operator/(const mint& lhs, const mint& rhs) {return mint(lhs) /= rhs;}friend bool operator==(const mint& lhs, const mint& rhs) {return lhs._v == rhs._v;}friend bool operator!=(const mint& lhs, const mint& rhs) {return lhs._v != rhs._v;}private:unsigned int _v;static internal::barrett bt;static unsigned int umod() { return bt.umod(); }};template <int id> internal::barrett dynamic_modint<id>::bt(998244353);using modint998244353 = static_modint<998244353>;using modint1000000007 = static_modint<1000000007>;using modint = dynamic_modint<-1>;namespace internal {template <class T>using is_static_modint = std::is_base_of<internal::static_modint_base, T>;template <class T>using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;template <class> struct is_dynamic_modint : public std::false_type {};template <int id>struct is_dynamic_modint<dynamic_modint<id>> : public std::true_type {};template <class T>using is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;}}
/* [modint.hpp] */
/* [modint] */
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <utility>
/* #expanded [resolving_rank.hpp] */
namespace lib {namespace internal {template<int P> struct resolving_rank : resolving_rank<P-1> {};template<> struct resolving_rank<0> {};}}
/* [resolving_rank.hpp] */
template<class source = std::istream>struct input_adapter {private:template<class T>auto _set(lib::internal::resolving_rank<3>, T *const val) -> decltype(std::declval<source>() >> *val, 0) {*this->in >> *val;return 0;}template<class T>auto _set(lib::internal::resolving_rank<2>, T *const val) -> decltype(std::begin(*val), std::end(*val), 0) {(*this)(std::begin(*val), std::end(*val));return 0;}template<class T>auto _set(lib::internal::resolving_rank<1>, T *const val) -> decltype(val->first, val->second, 0) {(*this)(&*val);return 0;}template<class T>auto _set(lib::internal::resolving_rank<0>, T *const val) -> std::enable_if_t<atcoder::internal::is_modint<T>::value,int> {long long v; std::cin >> v;*val = { v };return 0;}protected:template<class T>source *set(T *const val) {this->_set(lib::internal::resolving_rank<3>{}, val);return this->in;}public:using char_type = typename source::char_type;source *in;input_adapter(source *in = &std::cin) : in(in) {}template<class T> inline input_adapter& operator>>(T &s) {this->set(&s);return *this;}template<class T> inline T one() {T val; *this >> val;return val;}template<class T> inline void operator()(T*const val) {*this >> *val;}template<class T, class ...Args> inline void operator()(T*const head, Args*const ...tail) {*this >> *head;(*this)(tail...);}template<class I, class = typename I::value_type> inline void operator()(I first, I last) {for(I itr=first; itr!=last; ++itr) *this >> *itr;}template<class F, class S> inline void operator()(std::pair<F,S> *const p) {(*this)(&p->first, &p->second);}};
/* [input.hpp] */
/* #expanded [output.hpp] */
#include <iostream>
#include <string>
#include <vector>

template<class destination = std::ostream, class Terminator = std::string, class Separator = std::string>struct output_adapter {private:template<class T>auto _put(lib::internal::resolving_rank<2>, const T &val) -> decltype(std::declval<destination>() << val, 0) {*this->out << val;return 0;}template<class T>auto _put(lib::internal::resolving_rank<1>, const T &val) -> decltype(val.val(), 0) {*this->out << val.val();return 0;}template<class T>auto _put(lib::internal::resolving_rank<0>, const T &val) -> decltype(std::begin(val), std::end(val), 0) {(*this)(std::begin(val), std::end(val), false);return 0;}protected:template<class T>destination *put(const T &val) {this->_put(lib::internal::resolving_rank<2>{}, val);return this->out;}public:using char_type = typename destination::char_type;static constexpr auto sendl = std::endl<char_type,std::char_traits<char_type>>;destination *out;Terminator endline;Separator separator;output_adapter(destination *out = &std::cout, Terminator endline = "\n", Separator separator = " "): out(out), endline(endline), separator(separator) {}inline void seekp(const typename destination::off_type off, const std::ios_base::seekdir dir = std::ios_base::cur) { this->out->seekp(off, dir); };template<class T> inline output_adapter& operator<<(const T &s) {this->put(s);return *this;}template<class T = std::string> inline void operator()(const T &val = "") {*this << val << this->endline;}template<class T, class ...Args> inline void operator()(const T &head, const Args& ...tail) {*this << head << this->separator;(*this)(tail...);}template<class I, class = typename I::iterator_category> inline void operator()(const I first, const I last, const bool terminate = true) {for(I itr=first; itr!=last;) {*this << *itr;if(++itr == last) {if(terminate) *this << this->endline;}else *this << this->separator;}}template<class T> inline void operator()(const std::initializer_list<T> vals) {std::vector wrapped(vals.begin(), vals.end());(*this)(wrapped.begin(), wrapped.end());}template<class F, class S> inline void operator()(const std::pair<F,S> &p) {(*this)(p.first, p.second);}};
/* [output.hpp] */
input_adapter _input;output_adapter _print;
#define input _input
#define print _print
/* [template.hpp] */
/* #endregion */

/* #expanded [graph.hpp] */
#include <tuple>
#include <vector>

/* #expanded [dev_assert.hpp] */
#ifdef LOCAL_JUDGE
#include <cassert>
#define dev_assert(...) assert(__VA_ARGS__)
#else
#define dev_assert(...) ({ ; })
#endif
/* [dev_assert.hpp] */
/* #expanded [types.hpp] */
#include <cstdint>
namespace lib {namespace internal {using size_t = std::int32_t;using int128_t = __int128_t;using uint128_t = __uint128_t;}}
/* [types.hpp] */
namespace lib {namespace internal {namespace graph_lib {template<class cost_t = ll, class vertex = internal::size_t> struct edge {using cost_type = cost_t;const vertex from, to; const cost_t cost;edge(const vertex u, const vertex v, const cost_t w) : from(u), to(v), cost(w) {}std::tuple<vertex,vertex,cost_t> _debug() const { return { from, to, cost }; };};}}template<class cost_type = ll>struct graph : std::vector<std::vector<internal::graph_lib::edge<cost_type>>> {using vertex = internal::size_t;using size_type = internal::size_t;using edge = typename internal::graph_lib::edge<cost_type>;enum class edge_type { undirected, directed };private:size_type _directed_edge_count, _undirected_edge_count;protected:inline void _add_edge(const vertex u, const vertex v, const cost_type w) {this->operator[](u).emplace_back(u, v, w);++this->_directed_edge_count;}public:explicit graph(const vertex n = 0) : std::vector<std::vector<edge>>(n) {}inline vertex vertexes() const { return this->size(); }inline size_type edges() const { return this->inputted.size(); }template<const edge_type EDGE_TYPE = edge_type::directed>inline void add_edge(const vertex u, const vertex v, const cost_type w = 0) {dev_assert(0 <= u and u < this->vertexes()), dev_assert(0 <= v and v < this->vertexes());this->_add_edge(u, v, w);if constexpr(EDGE_TYPE == edge_type::undirected) this->_add_edge(v, u, w);++this->_undirected_edge_count;}inline void add_edge_bidirectionally(const vertex u, const vertex v, const cost_type w = 0) {this->add_edge<edge_type::undirected>(u, v, w);}template<bool WEIGHTED = false, bool ONE_ORIGIN = true, const edge_type EDGE_TYPE = edge_type::directed, class Stream = std::istream>void inline read(const size_type edges, Stream *const ist = &std::cin) {REP(edges) {vertex u, v; cost_type w = 0; *ist >> u >> v; if(ONE_ORIGIN) --u, --v;if(WEIGHTED) *ist >> w;this->add_edge<EDGE_TYPE>(u, v, w);}}template<bool WEIGHTED = false, bool ONE_ORIGIN = true, class Stream = std::istream>void inline read_bidirectionally(const size_type edges, Stream *const ist = &std::cin) {REP(edges) {vertex u, v; cost_type w = 0; *ist >> u >> v; if(ONE_ORIGIN) --u, --v;if(WEIGHTED) *ist >> w;this->add_edge<edge_type::undirected>(u, v, w);}}template<class cost_t = cost_type> inline void bfs(const vertex, std::vector<cost_t> *const) const;template<class cost_t = cost_type> inline std::vector<cost_t> bfs(const vertex) const;template<class cost_t = cost_type> inline void dijkstra(const vertex, std::vector<cost_t> *const) const;template<class cost_t = cost_type> inline std::vector<cost_t> dijkstra(const vertex) const;inline bool sort_topologically(std::vector<vertex> *const ) const;inline bool sort_topologically() const;template<class> inline bool sort_topologically_with_priority(std::vector<vertex> *const) const;template<class> inline bool sort_topologically_with_priority() const;inline vertex minimum_paph_cover_size_as_dag() const;template<class cost_t = cost_type>inline cost_t minimum_spanning_tree_cost() const;template<class cost_t = cost_type>inline cost_t maximum_spanning_tree_cost() const;inline vertex count_components() const;template<class G, class U = char>inline void from_grid(const G&, U = '.');template<class distance_type = cost_type, class = internal::size_t>inline distance_type build_manhattan_mst(const std::vector<distance_type>&, const std::vector<distance_type>&);};}
/* [graph.hpp] */
/* #expanded [minimum_paph_cover.hpp] */
#include <memory>


/* #expanded [maximum_bipartite_matching.hpp] */
/* #expanded [maxflow] */
/* #expanded [maxflow.hpp] */
#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <vector>
/* #expanded [internal_queue] */
/* #expanded [internal_queue.hpp] */
#include <vector>
namespace atcoder {namespace internal {template <class T> struct simple_queue {std::vector<T> payload;int pos = 0;void reserve(int n) { payload.reserve(n); }int size() const { return int(payload.size()) - pos; }bool empty() const { return pos == int(payload.size()); }void push(const T& t) { payload.push_back(t); }T& front() { return payload[pos]; }void clear() {payload.clear();pos = 0;}void pop() { pos++; }};}}
/* [internal_queue.hpp] */
/* [internal_queue] */
namespace atcoder {template <class Cap> struct mf_graph {public:mf_graph() : _n(0) {}explicit mf_graph(int n) : _n(n), g(n) {}int add_edge(int from, int to, Cap cap) {assert(0 <= from && from < _n);assert(0 <= to && to < _n);assert(0 <= cap);int m = int(pos.size());pos.push_back({from, int(g[from].size())});int from_id = int(g[from].size());int to_id = int(g[to].size());if (from == to) to_id++;g[from].push_back(_edge{to, to_id, cap});g[to].push_back(_edge{from, from_id, 0});return m;}struct edge {int from, to;Cap cap, flow;};edge get_edge(int i) {int m = int(pos.size());assert(0 <= i && i < m);auto _e = g[pos[i].first][pos[i].second];auto _re = g[_e.to][_e.rev];return edge{pos[i].first, _e.to, _e.cap + _re.cap, _re.cap};}std::vector<edge> edges() {int m = int(pos.size());std::vector<edge> result;for (int i = 0; i < m; i++) {result.push_back(get_edge(i));}return result;}void change_edge(int i, Cap new_cap, Cap new_flow) {int m = int(pos.size());assert(0 <= i && i < m);assert(0 <= new_flow && new_flow <= new_cap);auto& _e = g[pos[i].first][pos[i].second];auto& _re = g[_e.to][_e.rev];_e.cap = new_cap - new_flow;_re.cap = new_flow;}Cap flow(int s, int t) {return flow(s, t, std::numeric_limits<Cap>::max());}Cap flow(int s, int t, Cap flow_limit) {assert(0 <= s && s < _n);assert(0 <= t && t < _n);assert(s != t);std::vector<int> level(_n), iter(_n);internal::simple_queue<int> que;auto bfs = [&]() {std::fill(level.begin(), level.end(), -1);level[s] = 0;que.clear();que.push(s);while (!que.empty()) {int v = que.front();que.pop();for (auto e : g[v]) {if (e.cap == 0 || level[e.to] >= 0) continue;level[e.to] = level[v] + 1;if (e.to == t) return;que.push(e.to);}}};auto dfs = [&](auto self, int v, Cap up) {if (v == s) return up;Cap res = 0;int level_v = level[v];for (int& i = iter[v]; i < int(g[v].size()); i++) {_edge& e = g[v][i];if (level_v <= level[e.to] || g[e.to][e.rev].cap == 0) continue;Cap d =self(self, e.to, std::min(up - res, g[e.to][e.rev].cap));if (d <= 0) continue;g[v][i].cap += d;g[e.to][e.rev].cap -= d;res += d;if (res == up) return res;}level[v] = _n;return res;};Cap flow = 0;while (flow < flow_limit) {bfs();if (level[t] == -1) break;std::fill(iter.begin(), iter.end(), 0);Cap f = dfs(dfs, t, flow_limit - flow);if (!f) break;flow += f;}return flow;}std::vector<bool> min_cut(int s) {std::vector<bool> visited(_n);internal::simple_queue<int> que;que.push(s);while (!que.empty()) {int p = que.front();que.pop();visited[p] = true;for (auto e : g[p]) {if (e.cap && !visited[e.to]) {visited[e.to] = true;que.push(e.to);}}}return visited;}private:int _n;struct _edge {int to, rev;Cap cap;};std::vector<std::pair<int, int>> pos;std::vector<std::vector<_edge>> g;};}
/* [maxflow.hpp] */
/* [maxflow] */


namespace lib {struct maximum_bipartite_matching {using vertex = internal::size_t;protected:using MF = atcoder::mf_graph<vertex>;vertex _n;MF mf;public:maximum_bipartite_matching(vertex n = 0) : _n(n), mf(2*n+2) {REP(i, n) {this->mf.add_edge(2*n, i, 1);this->mf.add_edge(n+i, 2*n+1, 1);}}void add(vertex i, vertex j) {this->mf.add_edge(i, this->_n+j, 1);}vertex solve() {return this->mf.flow(2*this->_n, 2*this->_n+1);}};}
/* [maximum_bipartite_matching.hpp] */
template<class edge_cost>typename lib::graph<edge_cost>::vertex lib::graph<edge_cost>::minimum_paph_cover_size_as_dag() const {lib::maximum_bipartite_matching bm(this->size());REP(i, this->size()) ITR(j, (*this)[i]) {bm.add(i, j.to);}return this->size() - bm.solve();}
/* [minimum_paph_cover.hpp] */

signed main() {
    int n; cin >> n;

    vector<ll> X(n), E(n);
    REP(i, n) input >> X[i] >> E[i];
    debug(X, E);

    if(set(ALL(E)).size() == 1) {
        print(set(ALL(X)).size());
        return 0;
    }

    vector<int> XmE(n), XpE(n);
    iota(ALL(XmE), 0), iota(ALL(XpE), 0);

    auto compXmE = [&](int i, int j) { return X[i] - E[i] < X[j] - E[j]; };
    auto compXpE = [&](int i, int j) { return X[i] + E[i] < X[j] + E[j]; };

    sort(ALL(XmE), compXmE);
    sort(ALL(XpE), compXpE);

    debug(XmE, XpE);

    vector<bitset<500000>> u(n);

    REP(i, n) {
        auto a = lower_bound(ALL(XmE), i, compXmE);
        auto b = upper_bound(ALL(XpE), i, compXpE);

        bitset<500000> s, t;
        REPD(i, a, XmE.end()) s.set(*i);
        REP(i, XpE.begin(), b) t.set(*i);

        u[i] = s & t;
    }

    bitset<500000> covd;
    REP(i, n) {
        covd |= *max_element(ALL(u), [](const auto& a, const auto& b) { return a.count() < b.count(); });

        if(covd.count() >= n) {
            print(i+1);
            return 0;
        }

        REP(i, n) u[i] &= ~covd;
    }

    return 0;
}
