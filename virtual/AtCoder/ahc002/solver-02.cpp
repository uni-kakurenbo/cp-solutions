/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
 /* #language C++ GCC */

// #pragma GCC target("avx")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <iostream>

#include <cstdint>
#include <cassert>
#include <cmath>

#include <utility>
#include <tuple>
#include <chrono>
#include <random>

#include <algorithm>
#include <numeric>
#include <memory>
#include <optional>

#include <array>
#include <unordered_set>
#include <vector>
#include <stack>

#ifdef LOCAL_JUDGE

#include<debug>
#define debug(...) Debug::debug(Debug::split(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#define DEBUG(...) do { Debug::DEBUG(nintptr, "\033[3;35m#" + to_string(__LINE__) + "\033[m  "); Debug::DEBUG(__VA_ARGS__); Debug::DEBUG(nintptr, "\033[m\n"); } while(0);

#define dev_assert(...) assert(__VA_ARGS__)

constexpr bool DEVELOPMEMT_MODE = true;

#else

#define debug(...) { ; }
#define DEBUG(...) { ; }
#define dev_assert(...) { ; }

constexpr bool DEVELOPMEMT_MODE = false;

#endif

#define INF32 2147483647

using Position = std::int16_t;
using Direction = std::int16_t;

using Integer = std::int32_t;
using UnsignedInteger = std::uint32_t;

using Time = std::int32_t;
using Score = std::int32_t;
using Hash = std::uint32_t;

using Value = std::int16_t;
using Tile = std::int16_t;

constexpr Position SIZE = 50;

constexpr Position DRS[] = { -1, 0, 1, 0 }, DCS[] = { 0, 1, 0, -1 };
constexpr const char * DIRECTIONS = "URDL";

struct Uncopyable {
    Uncopyable(){}
    Uncopyable(const Uncopyable&) = delete;
    Uncopyable& operator=(const Uncopyable&) = delete;
};

template<class T>
struct Stack : protected std::stack<T,std::vector<T>> {
    using size_type = std::size_t;

    using std::stack<T,std::vector<T>>::empty;
    using std::stack<T,std::vector<T>>::size;
    using std::stack<T,std::vector<T>>::top;
    using std::stack<T,std::vector<T>>::push;
    using std::stack<T,std::vector<T>>::pop;

    void reserve(size_type n) { this->c.reserve(n); }
};

struct Timer : private Uncopyable {
  private:
    const Time time_limit;
    std::chrono::system_clock::time_point clock_start;

  public:
    using Progress = double;

    Timer(const Time time_limit = 0) : time_limit(time_limit), clock_start(std::chrono::system_clock::now()) {}

    inline Timer* reset() {
        clock_start = std::chrono::system_clock::now();
        return this;
    }

    inline Time elapsed() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - this->clock_start).count();
    }
    inline Time remaining () const {
        return time_limit - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - this->clock_start).count();
    }

    inline bool expired() const { return this->elapsed() > time_limit; }
    inline Progress progress() const { return static_cast<Progress>(this->elapsed()) / this->time_limit; }
};

template<class Engine = std::mt19937>
struct RandomEngine : private Uncopyable {
  private:
    mutable Engine engine;

  public:
    static constexpr UnsignedInteger MIN = Engine::min();
    static constexpr UnsignedInteger MAX = Engine::max();

    static constexpr UnsignedInteger min() { return MIN; }
    static constexpr UnsignedInteger max() { return MAX; }

    RandomEngine(UnsignedInteger seed = 3141592653UL) {
        this->engine.seed(seed);
    };

    inline UnsignedInteger operator()() const {
        return this->engine();
    }

    inline UnsignedInteger operator()(UnsignedInteger max) const {
        if(max == 0) return 0;
        return (*this)() % max;
    }
    inline Integer operator()(Integer min, Integer max) const {
        dev_assert(min <= max);
        return min + (*this)(max - min);
    };

    template<class T = double> inline T real() const {
        return static_cast<T>(this->engine()) / this->max();
    }
};

// 地点
struct Point {
    Position row, col;
    Point(const Position row = 0, const Position col = 0) : row(row), col(col) {}

    inline bool operator<(const Point& other) const {
        return std::pair{ this->row, this->col } < std::pair{ other.row, other.col };
    }
    inline bool operator==(const Point& other) const {
        return this->row == other.row && this->col == other.col;
    }

    inline std::pair<Position, Position> _debug() const {
        return { row, col };
    }
};

template<> struct std::hash<Point> {
    inline size_t operator()(Point key) const {
        return key.col * SIZE + key.row;
    }
};

// (i, j) → i * w + j
template<class T> struct Expander : private Uncopyable {
  private:
    const T N;

  public:
    Expander(const T N) : N(N) { dev_assert(N > 0); }
    inline T pair_to_id(const T a, const T b) const {
        dev_assert(0 <= a && a < N);
        dev_assert(0 <= b && b < N);
        return a * N + b;
    }
    inline T pair_to_id(const std::pair<T,T> p) const {
        return this->pair_to_id(p.first, p.second);
    }
    inline T id_to_first(const T id) const {
        dev_assert(0 <= id && id < N*N);
        return id / N;
    }
    inline T id_to_second(const T id) const {
        dev_assert(0 <= id && id < N*N);
        return id % N;
    }
};

// 入力された盤面の情報．コピーされない．
struct Grid : private Uncopyable {
  private:
    std::array<Tile,SIZE*SIZE> _tiles;
    std::array<Value,SIZE*SIZE> _value;

    Expander<Position> converter;

  public:
    Grid() : converter(SIZE) {}
    void read() {
        for(Position pos=0, last=SIZE*SIZE; pos < last; ++pos) {
            std::cin >> this->_tiles[pos];
        }
        for(Position pos=0, last=SIZE*SIZE; pos < last; ++pos) {
            std::cin >> this->_value[pos];
        }
    }

    inline Tile tile_number(const Position pos) const {
        return this->_tiles[pos];
    }
    inline Tile tile_number(const Position row, const Position col) const {
        return tile_number(this->converter.pair_to_id(row, col));
    }
    inline Tile tile_number(const Point point) const {
        return tile_number(this->converter.pair_to_id(point.row, point.col));
    }

    inline Value value(const Position pos) const {
        return this->_value[pos];
    }
    inline Value value(const Position row, const Position col) const {
        return value(this->converter.pair_to_id(row, col));
    }
    inline Value value(const Point point) const {
        return value(this->converter.pair_to_id(point.row, point.col));
    }
};

// 現在いる位置，得点，すでに通ったマスを保持．
struct Board {
    using History = Stack<Direction>;
    const Grid *grid;

    Point point;
    Score score;
    std::array<bool, SIZE*SIZE> visited;
    History history;

    Board(const Grid *grid, Point point) : grid(grid), point(point), score(this->grid->value(this->point)) {
        visited.fill(false);
        this->visited[this->grid->tile_number(this->point)] = true;
        history.reserve(SIZE*SIZE);
    }

    inline void move(const Direction dir) {
        dev_assert(this->can_move(dir));
        history.push(dir);
        this->point.row += DRS[dir], point.col += DCS[dir];
        this->visited[this->grid->tile_number(this->point)] = true;
        this->score += this->grid->value(this->point);
    }
    inline void remove() {
        auto dir = history.top(); history.pop();
        this->score -= this->grid->value(this->point);
        this->visited[this->grid->tile_number(this->point)] = false;
        this->point.row -= DRS[dir], point.col -= DCS[dir];
    }

    inline bool can_move(const Direction dir) {
        const Point moved_point(this->point.row + DRS[dir], this->point.col + DCS[dir]);
        if(moved_point.row < 0 or moved_point.row >= SIZE) return false;
        if(moved_point.col < 0 or moved_point.col >= SIZE) return false;
        const Tile next_tile = this->grid->tile_number(moved_point);
        return not this->visited[next_tile];
    }
};

inline void print_answer(std::ostream *out, const std::string answer) {
    *out << answer << "\n";
}

inline void print_answer(std::ostream *out, const std::string answer, std::ostream *log, const Score score) {
    *log << score << "\n";
    print_answer(out, answer);
}

struct Solver : private Uncopyable {
  private:
    const Position sr, sc;  // 初期位置
    const Grid *grid;  // 盤面

    static constexpr Time TIME_LIMIT_MS = 100;

    Score best_score;
    Board::History preliminary_answer;

  public:
    Solver(const Position sr, const Position sc, const Grid *grid) : sr(sr), sc(sc), grid(grid) {}

    Score solve(std::string *answer) {
        UnsignedInteger shuffles[][4] = { { 0, 1, 2, 3 }, { 1, 2, 3, 0 } };  // 進行方向の優先順位 (いくつか試す)

        Timer timer(this->TIME_LIMIT_MS / std::size(shuffles));
        for(const auto &shuffle : shuffles) {
            timer.reset();
            this->dfs(shuffle, timer);
            std::clog << "Best internal score: " << best_score << "\n";
        }

        this->build_answer(answer);

        return best_score;
    }

    inline void dfs(const UnsignedInteger shuffle[4], const Timer &timer) {
        using Priority = std::make_signed_t<Position>;

        Board board(grid, Point{sr, sc});

        Stack<Direction> stack; stack.reserve(5*SIZE*SIZE);
        stack.push(100);  // ひきかえし

        dev_assert(not stack.empty());

        int cnt = 0;
        while(!timer.expired()) {  // DFS
            ++cnt;
            auto motion = stack.top(); stack.pop();
            if(motion >= 0) {  // 上り
                if(motion < 4) board.move(motion);

                std::vector<std::pair<Priority, Direction>> dirs; dirs.reserve(4);
                for(Direction dir = 0; dir < 4; dir++) {
                    if(not board.can_move(shuffle[dir])) continue;
                    const Position dr = (board.point.row + DRS[shuffle[dir]]) - SIZE/2;
                    const Position dc = (board.point.col + DCS[shuffle[dir]]) - SIZE/2;
                    const Priority priority = (dr * dr + dc * dc);
                    dirs.emplace_back(priority, dir);
                }
                std::sort(dirs.begin(), dirs.end());  // 優先度の大きいものが後ろに来るように．

                stack.push(-1);
                for(const auto &[_, dir] : dirs) stack.push(shuffle[dir]);
            }
            else {  // 下り
                if(board.score > best_score) {
                    best_score = board.score;
                    preliminary_answer = board.history;
                }
                // auto _history = board.history;
                // std::string _answer; this->build_answer(&_answer, &_history); print_answer(&std::cout, _answer);
                board.remove();
            }
        }
        std::clog << "Loops: " << cnt << "\n";
    }

    void build_answer(std::string *answer) {
        this->build_answer(answer, &this->preliminary_answer);
    }
    void build_answer(std::string *answer, Board::History *source) {
        while(not source->empty()) {
            *answer += DIRECTIONS[source->top()];
            source->pop();
        }
        reverse(answer->begin(), answer->end());
    }
};

inline void fast_io() { std::ios::sync_with_stdio(false), std::cin.tie(nullptr); }

signed main() {
    fast_io();

    if constexpr (DEVELOPMEMT_MODE) std::clog << "Executed in development mode." << "\n";
    else std::clog << "Executed in non-development mode." << "\n";

    Position sr, sc; std::cin >> sr >> sc;
    Grid grid; grid.read();

    Solver solver(sr, sc, &grid);

    std::string answer;
    const Score score = solver.solve(&answer);

    print_answer(&std::cout, answer, &std::clog, score);

    return 0;
}
