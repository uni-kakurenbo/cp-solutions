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

#include "template.hpp"
#include "input.hpp"
#include "output.hpp"

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

using Pos = float;
using PosInt = int32_t;
using Arg = float;

constexpr Pos RADIUS = 1000000000;
constexpr Pos RADIUS2 = RADIUS*RADIUS;

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

struct Point {
    Pos x, y;

    Point(const Pos x, const Pos y) : x(x), y(y) {}
    Point() : Point(0, 0) {}

    inline PosInt int_x() const {
        return static_cast<PosInt>(this->x);
    }
    inline PosInt int_y() const {
        return static_cast<PosInt>(this->y);
    }

    inline bool valid() {
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

struct Line {
    Arg arg;
    Pos cst;
    Point p;
    Arg arg_tan, arg_sin, arg_cos;

    Line(Arg arg, Pos cst) : arg(arg), cst(cst) {
        this->arg_tan = tan(arg);
        this->arg_sin = sin(arg);
        this->arg_cos = cos(arg);
    }
    Line(Point p, Arg arg) : Line(arg, 0) {
        this->cst = -this->arg_tan*p.x + p.y;
        this->p = p;
    }

    inline bool has_intsec(const Line &t) const {
        return this->arg != t.arg;
    }

    inline Point intsec(const Line &t) const {
        Point res;
        res.x = (this->cst - t.cst) / (t.arg_tan - this->arg_tan);
        res.y = this->arg_tan * res.x + this->cst;
        return res;
    }

    inline pair<Pos, Pos> _debug() const {
        return { this->arg_tan, this->cst };
    }
};

struct LineCollector {
    vector<Line> buf;
    vector<Point> ints;

    LineCollector(const size_t resv) {
        buf.reserve(resv);
        buf.reserve((resv) * (resv - 1) / 2);
    }

    inline void add(const Line &line) {
        buf.push_back(line);
    }

    inline Point pop_ints() {
        Point res = this->ints.back(); this->ints.pop_back();
        return res;
    }
};

RandomEngine random_engine;

constexpr int QUERIES = 500;

signed main() {
    double rho; cin >> rho;

    LineCollector lines(500);

    REP(query, QUERIES) {
        Point log;

        do {
            log.x = random_engine(-RADIUS, RADIUS);
            log.y = random_engine(-RADIUS, RADIUS);
        } while(log.x*log.x + log.y*log.y > RADIUS2);
        print(log.int_x(), log.int_y());


        int16_t type; cin >> type;
        if(type == 0) {  // HINTED
            Arg theta; cin >> theta;

            Line line = { log, theta };
            if(query < 500) lines.add(line);
        }
        if(type > 0) {  // DETECTED
            Pos x, y; cin >> x >> y;
            if(type > 1) return 0;
        }
    }

    REPF(i, 0UL, lines.buf.size()) REPF(j, i+1, lines.buf.size()) {
        auto line0 = lines.buf[i], line1 = lines.buf[j];
        if(not line0.has_intsec(line1)) continue;
        Point p = line0.intsec(line1);
        if(not p.valid()) continue;
        // debug(line0);
        if((line0.arg_cos > 0) ^ (p.x > line0.p.x)) continue;
        if((line0.arg_sin > 0) ^ (p.y > line0.p.y)) continue;
        auto dx0 = p.x-line0.p.x;
        auto dy0 = p.y-line0.p.y;
        if(dx0*dx0 + dy0*dy0 > RADIUS2/5) continue;
        auto dx1 = p.x-line1.p.x;
        auto dy1 = p.y-line1.p.y;
        if(dx1*dx1 + dy1*dy1 > RADIUS2/5) continue;
        print("#c", p.int_x(), p.int_y(), 255, 255, 100);
    }

    print(0, 0);

    return 0;
}
