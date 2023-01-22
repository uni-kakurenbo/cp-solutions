/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */

#ifdef LOCAL_JUDGE

#include<debug>
#define debug(...) debugger::debug(debugger::split(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#define DEBUG(...) do { debugger::DEBUG(nullptr, "\033[3;35m#" + to_string(__LINE__) + "\033[m  "); debugger::DEBUG(__VA_ARGS__); debugger::DEBUG(nullptr, "\033[m\n"); } while(0);

#define dev_assert(...) assert(__VA_ARGS__)

constexpr bool DEVELOPMEMT_MODE = true;

#else

#define debug(...) { ; }
#define DEBUG(...) { ; }
#define dev_assert(...) { ; }

constexpr bool DEVELOPMEMT_MODE = false;

#endif


#include <cstdint>
#include <limits>

#include <algorithm>
#include <chrono>

#include <array>
#include <string>
#include <vector>
#include <queue>

#include <iomanip>
#include <iostream>
#include <sstream>


namespace lib {


using size_type = std::int32_t;
using dir_type = std::int8_t;
using bool_type = bool; // std::vector<bool> の特殊化回避のために変更する可能性あり．

using score_type = std::int32_t;
using rank_type = std::int32_t;

constexpr size_type N = 50, M = 2500, S = N*N;
constexpr size_type DRS[4] = { 0, 1, 0, -1 }, DCS[4] = { 1, 0, -1, 0 }; // → ↓ ← ↑

enum {
    NONE = -1
};

struct uncopyable {
    uncopyable(){}
    uncopyable(const uncopyable&) = delete;
    uncopyable& operator=(const uncopyable&) = delete;
};


struct timer : private uncopyable {
    using time_type = std::int32_t;
    using Progress = double;

  private:
    const time_type time_limit = 0;
    const Progress progress_duration = 0;

    std::chrono::system_clock::time_point clock_start, clock_end;

  public:

    timer(const time_type time_limit = 0) : time_limit(time_limit),
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

    inline time_type limit() { return this->time_limit; }

    inline timer* reset() {
        this->clock_start = std::chrono::system_clock::now();
        this->clock_end = clock_start + std::chrono::milliseconds(this->time_limit);
        return this;
    }

    inline time_type elapsed() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - this->clock_start).count();
    }
    inline time_type remaining () const {
        return time_limit - this->elapsed();
    }

    inline bool expired() const { return this->elapsed() > time_limit; }
    inline Progress progress() const {
        return (std::chrono::system_clock::now() - this->clock_start).count() / this->progress_duration;
    }
};


struct xorshift : private uncopyable {
    using result_type = std::uint32_t;

    static constexpr result_type MIN = std::numeric_limits<result_type>::min();
    static constexpr result_type MAX = std::numeric_limits<result_type>::max();

    static constexpr result_type min() noexcept { return MIN; }
    static constexpr result_type max() noexcept { return MAX; }

    inline void seed(unsigned int seed) { this->w = seed; }

    xorshift() noexcept {};
    xorshift(const std::uint32_t seed) noexcept : w(seed) {};

    inline std::uint32_t operator()() noexcept {
        std::uint32_t t;

        t = x ^ (x << 11);
        x = y; y = z; z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

  private:
    std::uint32_t x = 123456789;
    std::uint32_t y = 362436069;
    std::uint32_t z = 521288629;
    std::uint32_t w = 88675123;
};


template<class Engine> struct random_engine : private uncopyable {
    using result_type = typename Engine::result_type;
    using signed_result_type = typename std::make_signed_t<result_type>;

  private:
    mutable Engine engine;

  public:
    static constexpr result_type MIN = Engine::min();
    static constexpr result_type MAX = Engine::max();

    static constexpr result_type min() noexcept { return MIN; }
    static constexpr result_type max() noexcept { return MAX; }

    random_engine() noexcept {};
    random_engine(unsigned long seed) noexcept { this->engine.seed(seed); };

    inline result_type operator()() const noexcept {
        return this->engine();
    }

    inline result_type operator()(result_type max) const noexcept {
        if(max == 0) return 0;
        return (*this)() % max;
    }
    inline signed_result_type operator()(signed_result_type min, signed_result_type max) const noexcept {
        dev_assert(min <= max);
        return min + (*this)(max - min);
    };

    template<class T = double> inline T real() const noexcept {
        return static_cast<T>(this->engine() + 0.5) / (1.0 + this->max());
    }
};


//Thanks to: atcoder::dsu
struct dsu {
  private:
    size_type _n = S, _group_count = S;
    // root node: -1 * component size
    // otherwise: parent
    mutable std::array<size_type,S> _parent_or_size;

  public:
    dsu() { this->_parent_or_size.fill(-1); }

    inline size_type size() const { return this->_n; }
    inline size_type group_count() const { return this->_group_count; }

    inline size_type merge(const size_type a, const size_type b) {
        dev_assert(0 <= a && a < _n);
        dev_assert(0 <= b && b < _n);
        size_type x = this->leader(a), y = this->leader(b);
        if (x == y) return x;
        --this->_group_count;
        if (-this->_parent_or_size[x] < -this->_parent_or_size[y]) std::swap(x, y);
        this->_parent_or_size[x] += this->_parent_or_size[y];
        this->_parent_or_size[y] = x;
        return x;
    }

    inline bool same(const size_type a, const size_type b) const {
        dev_assert(0 <= a && a < _n);
        dev_assert(0 <= b && b < _n);
        return this->leader(a) == this->leader(b);
    }

    inline size_type leader(const size_type a) const {
        dev_assert(0 <= a && a < _n);
        if (_parent_or_size[a] < 0) return a;
        return _parent_or_size[a] = this->leader(_parent_or_size[a]);
    }

    inline size_type size(const size_type a) const {
        dev_assert(0 <= a && a < _n);
        return -_parent_or_size[this->leader(a)];
    }

    inline std::vector<std::vector<size_type>> groups() const {
        std::vector<size_type> leader_buf(_n), group_size(_n);
        for (size_type i = 0; i < _n; i++) {
            leader_buf[i] = this->leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<size_type>> result(_n);
        for (size_type i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (size_type i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<size_type>& v) { return v.empty(); }),
            result.end());
        return result;
    }

    inline auto _debug() const noexcept { return this->groups(); }
};


struct point {
  private:
    size_type _row = -1, _col = -1;

  public:
    point(const size_type pos) noexcept : _row(pos/N), _col(pos%N) {}
    point(const size_type row, const size_type col) noexcept : _row(row), _col(col) {}

    inline size_type row() const noexcept { return this->_row; }
    inline size_type col() const noexcept { return this->_col; }
    inline size_type pos() const noexcept { return this->_row * N + this->_col; }

    explicit inline operator bool() const noexcept {  // 盤面外で false
        return 0 <= this->_row and this->_row < N and 0 <= this->_col and this->_col < N;
    }
};

template<class T> struct grid {
  private:
    T _data[S] = { 0 };

  public:
    grid() {}
    ~grid() {}

    template<class Stream> void read(Stream *const in) noexcept {
        for(size_type pos=0; pos<S; ++pos) *in >> this->_data[pos];
    }

    inline rank_type& operator[](const size_type pos) noexcept { return this->_data[pos]; }
    inline rank_type operator[](const size_type pos) const noexcept { return this->_data[pos]; }

    inline rank_type& operator[](const point& pos) noexcept { return this->_data[pos.pos()]; }
    inline rank_type operator[](const point& pos) const noexcept { return this->_data[pos.pos()]; }

    inline auto _debug() const noexcept {
        std::ostringstream res;
        res << "\n";
        auto itr = std::begin(this->_data);
        for(size_type i=0; i<N; ++i) {
            for(size_type j=0; j<N; ++j) res << std::setw(3) << std::setfill('0') << *(itr++) << " ";
            res << "\n";
        }
        return res.str();
    }
};

struct field {
   private:
    grid<rank_type> _ranks;

  public:
    field() {}

  public:
    template<class Stream> void read(Stream *const in) noexcept { this->_ranks.read(in); }

    inline rank_type rank(const size_type pos) const noexcept { return this->_ranks[pos]; }
    inline rank_type rank(const point& pos) const noexcept { return this->_ranks[pos]; }

    const dsu groups() const noexcept {
        dsu uf;

        auto connect = [this,&uf](const point& pos) -> void {
            for(dir_type d=0; d<2; ++d) {
                const point neighbor = { pos.row() + DRS[d], pos.col() + DCS[d] };

                if(not neighbor) continue;

                if(this->_ranks[pos] == this->_ranks[neighbor]) {
                    uf.merge(pos.pos(), neighbor.pos());
                }
            }
        };

        for(size_type pos=0; pos<S; ++pos) connect(pos);

        return uf;
    }

    void inline care(const size_type pos) noexcept { this->care(point{ pos }); }
    void inline care(const point& pos) noexcept {
        ++this->_ranks[pos];
    }

    score_type inline harvest(const size_type pos) noexcept {
        const rank_type rank = this->_ranks[pos];

        size_type count = 0;

        std::queue<point> que;
        bool_type seen[S] = { 0 };

        que.push(pos), seen[pos] = 0;

        while(!que.empty()) {
            auto v = que.front(); que.pop();

            for(dir_type d=0; d<4; ++d) {
                const point nv = { v.row() + DRS[d], v.col() + DCS[d] };

                if(not nv) continue;
                if(this->_ranks[nv] != rank) continue;

                if(seen[nv.pos()]) continue;
                seen[nv.pos()] = true;

                ++count;
                this->_ranks[nv] = NONE;

                que.push(std::move(nv));
            }
        }

        return static_cast<score_type>(count) * rank;
    }
    void inline harvest(const point& pos) noexcept { this->harvest(pos.pos()); }

    inline auto _debug() const noexcept { return this->_ranks._debug(); }
};

template<class Stream> struct outputter {
  private:
    size_type _count = 0;
    Stream *const out;

  public:
    outputter(Stream *const out) : out(out) {}

    inline size_type count() const { return this->_count; }

    inline void care(const size_type pos) noexcept { this->care(point{ pos }); }
    inline void care(const point pos) noexcept {
        ++this->_count;
        *this->out << "1 " << pos.row() << " " << pos.col() << "\n";
    }

    inline void harvest(const size_type pos) noexcept { this->harvest(point{ pos }); }
    inline void harvest(const point pos) noexcept {
        ++this->_count;
        *this->out << "2 " << pos.row() << " " << pos.col() << "\n";
    }
};


} //namespace lib

lib::random_engine<lib::xorshift> rnd;

signed main() {
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // N, M の入力を無視．

    lib::field field; field.read(&std::cin);  // A を受け取る
    debug(field);

    lib::outputter out(&std::cout);

    lib::timer timer(1900);
    while(not timer.expired() and out.count() < 2000) {  // 2000 クエリまで
        lib::size_type pos = static_cast<lib::size_type>(rnd(lib::S));
        auto temp = field;
        temp.care(pos);  // ランダムに手入れ
        if(temp.groups().group_count() < field.groups().group_count()) {  // 連結成分が減ったら
            field = std::move(temp);  // 採用
            out.care(pos);
        }
    }

    auto groups = field.groups().groups(); // 連結成分を昇順に．
    std::sort(groups.rbegin(), groups.rend(), [](const auto& a, const auto& b) { return a.size() < b.size(); });
    debug(groups);

    for(const auto& group : groups) {
        if(field.rank(group[0]) > static_cast<lib::rank_type>(group.size())) continue; // 収穫可能なら
        out.harvest(group[0]); // 収穫．
        if(out.count() >= 2500) break;
    }

    return EXIT_SUCCESS;
}
