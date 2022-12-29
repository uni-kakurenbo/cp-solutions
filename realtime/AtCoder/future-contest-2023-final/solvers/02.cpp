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
#include <iostream>
#include <utility>
#ifdef LOCAL_JUDGE
#include<debug>
#define debug(...) Debug::debug(Debug::split(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#define DEBUG(...) do { Debug::DEBUG(nullptr, "\033[3;35m#" + to_string(__LINE__) + "\033[m "); Debug::DEBUG(__VA_ARGS__); Debug::DEBUG(nullptr, "\033[m\n"); } while(0);
#else
#define debug(...) ({ ; })
#define DEBUG(...) ({ ; })
#endif
#define INF32 2147483647
#define INF64 9223372036854775807LL
#define until(...) while(!(__VA_ARGS__))
#define REP(i,n) for(int i=0, i##_length=int(n); i<i##_length; ++i)
#define REPF(i,l,r) for(auto i=(l), i##_last=(r); i<i##_last; ++i)
#define REPB(i,l,r) for(auto i=(r), i##_last=(l); --i>=i##_last;)
#define REPD(i,n) for(auto i=(n); --i>=0;)
#define LOOP(n) REP($_, (n))
#define FOR(i,l,r) for(auto i=(l), i##_last=(r); i<=i##_last; ++i)
#define FORD(i,l,r) for(auto i=(l), i##_last=(r); i>=i##_last; --i)
#define ITR(x,v) for(const auto &x : (v))
#define ITRP(x,v) for(auto x : (v))
#define ITRR(x,v) for(auto &x : (v))
#define ITRM(x,y,v) for(const auto [x, y] : (v))
#define ITRMP(x,y,v) for(auto [x, y] : (v))
#define ITRMR(x,y,v) for(auto &[x, y] : (v))
#define ALL(x) std::begin((x)),std::end((x))
#define RALL(x) std::rbegin((x)),std::rend((x))
#define $F first
#define $S second
using ll = long long;using ull = unsigned long long;using ld = long double;constexpr char ln = '\n';constexpr char spc = ' ';constexpr std::pair<int,int> DIRS4[] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };constexpr std::pair<int,int> DIRS8[] = { { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 } };__attribute__((constructor)) inline void fast_io() { std::ios::sync_with_stdio(false), std::cin.tie(nullptr); }template<class T1, class T2> inline auto mod(T1 x, T2 r) { return (x%r+r)%r; }template<class T1, class T2> inline bool chmax(T1 &a, T2 b) { return (a<b ? a=b, true : false); }template<class T1, class T2> inline bool chmin(T1 &a, T2 b) { return (a>b ? a=b, true : false); }
/* [template.hpp] */
/* #expanded [input.hpp] */
#include <iostream>
#include <string>
#include <vector>
template<class Stream = std::istream>struct Input {private:template<class T>auto _set(int, T * const val) -> decltype(declval<Stream>() >> *val, 0) {*this->in >> *val;return 0;}template<class T>int _set(bool, T * const val) {(*this)(std::begin(*val), std::end(*val));return 0;}protected:template<class T>Stream *set(T * const val) {this->_set(0, val);return this->in;}public:using char_type = typename Stream::char_type;Stream *in;Input(Stream *in = &std::cin) : in(in) {}template<class T> inline Input& operator>>(T &s) {this->set(&s);return *this;}template<class T> inline T one() {T val; *this >> val;return val;}template<class T> inline void operator()(T* const val) {*this >> *val;}template<class T, class ...Args> inline void operator()(T* const head, Args* const ...tail) {*this >> *head;(*this)(tail...);}template<class I, class = typename I::value_type> inline void operator()(I first, I last) {for(I itr=first; itr!=last; ++itr) *this >> *itr;}template<class F, class S> inline void operator()(std::pair<F,S> * const p) {(*this)(&p->first, &p->second);}};
/* [input.hpp] */
/* #expanded [output.hpp] */
#include <iostream>
#include <string>
#include <vector>
/* #expanded [dev_resolving_rank.hpp] */
namespace Lib {namespace Internal {template<int P> struct Rank : Rank<P-1> {};template<> struct Rank<0> {};}}
/* [dev_resolving_rank.hpp] */
template<class Stream = std::ostream, class Terminator = std::string, class Separator = std::string>struct Output {private:template<class T>auto _put(Lib::Internal::Rank<2>, const T &val) -> decltype(declval<Stream>() << val, 0) {*this->out << val;return 0;}template<class T>auto _put(Lib::Internal::Rank<1>, const T &val) -> decltype(val.val(), 0) {*this->out << val.val();return 0;}template<class T>auto _put(Lib::Internal::Rank<0>, const T &val) -> decltype(std::begin(val), std::end(val), 0) {(*this)(std::begin(val), std::end(val), false);return 0;}protected:template<class T>Stream *put(const T &val) {this->_put(Lib::Internal::Rank<2>{}, val);return this->out;}public:using char_type = typename Stream::char_type;static constexpr auto sendl = std::endl<char_type,std::char_traits<char_type>>;Stream *out;Terminator endline;Separator separator;Output(Stream *out = &std::cout, Terminator endline = "\n", Separator separator = " "): out(out), endline(endline), separator(separator) {}template<class T> inline Output& operator<<(const T &s) {this->put(s);return *this;}template<class T = std::string> inline void operator()(const T &val = "") {*this << val << this->endline;}template<class T, class ...Args> inline void operator()(const T &head, const Args& ...tail) {*this << head << this->separator;(*this)(tail...);}template<class I, class = typename I::iterator_category> inline void operator()(const I first, const I last, const bool terminate = true) {for(I itr=first; itr!=last;) {*this << *itr;if(++itr == last) {if(terminate) *this << this->endline;}else *this << this->separator;}}template<class T> inline void operator()(const std::initializer_list<T> vals) {std::vector wrapped(vals.begin(), vals.end());(*this)(wrapped.begin(), wrapped.end());}template<class F, class S> inline void operator()(const std::pair<F,S> &p) {(*this)(p.first, p.second);}};
/* [output.hpp] */

Input _input;
Output _print(&cout, Output<>::sendl);
#define input _input
#define print _print

#ifdef LOCAL_JUDGE

#define dev_assert(...) assert(__VA_ARGS__)

constexpr bool DEVELOPMEMT_MODE = true;

#else

#define dev_assert(...) { ; }

constexpr bool DEVELOPMEMT_MODE = false;

#endif
/* #endregion */

struct Uncopyable {
    Uncopyable() {};
    Uncopyable(const Uncopyable&) = delete;
    Uncopyable& operator=(const Uncopyable&) = delete;
};

struct Xorshift {
    using result_type = std::uint32_t;

    static constexpr result_type MIN = std::numeric_limits<result_type>::min();
    static constexpr result_type MAX = std::numeric_limits<result_type>::max();

    static constexpr result_type min() { return MIN; }
    static constexpr result_type max() { return MAX; }

    inline void seed(unsigned int seed) { this->x = seed; }

    Xorshift() {};
    Xorshift(unsigned int seed) : x(seed) {};

    inline result_type operator()() {
        result_type t;

        t = x ^ (x << 11);
        x = y; y = z; z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

  private:
    result_type x = 123456789;
    result_type y = 362436069;
    result_type z = 521288629;
    result_type w = 88675123;
};

template<class Engine = Xorshift>
struct RandomEngine : private Uncopyable {
    using result_type = typename Engine::result_type;
    using signed_result_type = typename std::make_signed_t<result_type>;

  private:
    mutable Engine engine;

  public:
    static constexpr result_type MIN = Engine::min();
    static constexpr result_type MAX = Engine::max();

    static constexpr result_type min() { return MIN; }
    static constexpr result_type max() { return MAX; }

    RandomEngine() {};
    RandomEngine(unsigned long seed) { this->engine.seed(seed); };

    inline result_type operator()() const {
        return this->engine();
    }

    inline result_type operator()(result_type max) const {
        if(max == 0) return 0;
        return (*this)() % max;
    }
    inline signed_result_type operator()(signed_result_type min, signed_result_type max) const {
        dev_assert(min <= max);
        return min + (*this)(max - min);
    };

    template<class T = double> inline T real() const {
        constexpr T p = 1.0 + this->max();
        return static_cast<T>(this->engine() + 0.5) / p;
    }
};

struct Timer : private Uncopyable {
    using Time = std::int32_t;
    using Progress = double;

  private:
    const Time time_limit = 0;
    const Progress progress_duration = 0;

    std::chrono::system_clock::time_point clock_start, clock_end;

  public:

    Timer(const Time time_limit = 0) : time_limit(time_limit),
        progress_duration(
            static_cast<Progress>(
                std::chrono::duration_cast<std::chrono::system_clock::duration>(
                    std::chrono::milliseconds(time_limit)
                ).count()
            )
        )
    {
        this->reset();
    }

    inline Time limit() { return this->time_limit; }

    inline Timer* reset() {
        this->clock_start = std::chrono::system_clock::now();
        this->clock_end = clock_start + std::chrono::milliseconds(this->time_limit);
        return this;
    }

    inline Time elapsed() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - this->clock_start).count();
    }
    inline Time remaining () const {
        return time_limit - this->elapsed();
    }

    inline bool expired() const { return this->elapsed() > time_limit; }
    inline Progress progress() const {
        return (std::chrono::system_clock::now() - this->clock_start).count() / this->progress_duration;
    }
};


using Pos = int64_t;
using Arg = float;

constexpr int QUERIES = 1000;
constexpr ll RADIUS = 1'000'000'000;
constexpr ll RADIUS2 = RADIUS*RADIUS;

const double PI = 3.141592653589793;
constexpr ll ADV = 100000000;


struct Point {
    Pos x, y;

    Point(const Pos x, const Pos y) : x(x), y(y) {}
    Point() : Point(0, 0) {}

    inline bool valid() {
        if(abs(this->x) > RADIUS) return false;
        if(abs(this->y) > RADIUS) return false;
        return this->x * this->x + this->y * this->y <= RADIUS2;
    }

    inline bool operator==(const Point &other) const {
        return this->x == other.x and this->y == other.y;
    }
    inline bool operator!=(const Point &other) const {
        return not (*this == other);
    }

    inline pair<Pos, Pos> _debug() const {
        return { this->x, this->y };
    }
};

RandomEngine random_engine;

signed main() {
    double rho; cin >> rho;

    Point lod;
    Arg inv_theta = -1;

    Pos adv = ADV;

    REP(query, QUERIES) {
        debug(query);

        while(not lod.valid()) {
            lod.x = random_engine(-RADIUS, RADIUS), lod.y = random_engine(-RADIUS, RADIUS);
        };
        print(lod.x, lod.y);

        int16_t type; cin >> type;
        if(type == 0) {
            debug("HINTED");
            Arg theta; cin >> theta;
            lod.x += cos(theta)*adv;
            lod.y += sin(theta)*adv;

            debug(theta, inv_theta);

            if(abs(theta - inv_theta) < 0.1) {
                adv /= 2;
            }

            inv_theta = theta + PI;
            if(inv_theta >= 2*PI) inv_theta -= 2*PI;
        }
        if(type > 0) {
            debug("DETECTED");
            Pos x, y; cin >> x >> y;

            adv = ADV;
            do {
                lod.x = random_engine(-RADIUS, RADIUS), lod.y = random_engine(-RADIUS, RADIUS);
            } while(not lod.valid());
            if(type > 1) return 0;
        }
    }

    return 0;
}
