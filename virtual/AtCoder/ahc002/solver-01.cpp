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
    Uncopyable( const Uncopyable & ) = delete ;
    Uncopyable & operator = ( const Uncopyable & ) = delete ;
} ;

class Timer : private Uncopyable {
  private:
    const Time time_limit;
    std::chrono::system_clock::time_point clock_start;

  public:
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
};

template<class Engine = std::mt19937> struct RandomEngine : private Uncopyable {
  private:
    mutable Engine engine;

  public:
    static constexpr UnsignedInteger MIN = Engine::min();
    static constexpr UnsignedInteger MAX = Engine::max();

    static constexpr UnsignedInteger min() { return MIN; }
    static constexpr UnsignedInteger max() { return MAX; }

    RandomEngine(UnsignedInteger seed = 3141592653UL) {
        engine.seed(seed);
    };

    inline UnsignedInteger operator()() const {
        return engine();
    }

    inline UnsignedInteger operator()(UnsignedInteger max) const {
        if(max == 0) return 0;
        return (*this)() % max;
    }
    inline Integer operator()(Integer min, Integer max) const {
        dev_assert(min <= max);
        return min + (*this)(max - min);
    };
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

// 現在いる位置，得点，すでに通ったマスを保持．コピーされない．
struct Board : private Uncopyable {
  public:
    const Grid *grid;

    Point point;
    Score score;
    std::array<bool, SIZE*SIZE> visited;

    Board(const Grid *grid, Point point) : grid(grid), point(point), score(this->grid->value(this->point)) {
        visited.fill(false);
        this->visited[this->grid->tile_number(this->point)] = true;
    }

    inline void move(const Direction dir) {
        dev_assert(this->can_move(dir));
        this->point.row += DRS[dir], point.col += DCS[dir];
        this->visited[this->grid->tile_number(this->point)] = true;
        this->score += this->grid->value(this->point);
    }
    inline void remove(const Direction dir) {
        this->score -= this->grid->value(this->point);
        this->visited[this->grid->tile_number(this->point)] = false;
        this->point.row -= DRS[dir], point.col -= DCS[dir];
    }

    inline Score moved_score(const Direction dir) {
        const Point moved_point(this->point.row + DRS[dir], this->point.col + DCS[dir]);
        return score + grid->value(moved_point);
    }

    inline bool can_move(const Direction dir) {
        const Point moved_point(this->point.row + DRS[dir], this->point.col + DCS[dir]);
        if(moved_point.row < 0 or moved_point.row >= SIZE) return false;
        if(moved_point.col < 0 or moved_point.col >= SIZE) return false;
        const Tile next_tile = this->grid->tile_number(moved_point);
        return not this->visited[next_tile];
    }

    inline void find_all_can_move(bool res[4]) {
        for(Direction dir = 0; dir < 4; ++dir) res[dir] = this->can_move(dir);
    }
};


struct Node;

using Parent = std::optional<std::pair<Direction, std::shared_ptr<Node>>>;

struct Node {
    const Parent parent;
    const Score score;
    // Hash hash;

    Node(const Parent parent, const Score score) : parent(parent), score(score) {}
};


inline void print_answer(std::ostream *out, const std::vector<Direction> answer) {
    for(const Direction& dir : answer) (*out) << DIRECTIONS[dir];
}

inline void print_answer(std::ostream *out, const std::vector<Direction> answer, std::ostream *log, const Score score) {
    (*log) << score << "\n";
    print_answer(out, answer);
}

struct Solver {
  private:
    const Position sr, sc; // 初期位置
    const Grid *grid; // 盤面

    static constexpr Time TIME_LIMIT_MS = 100;

  public:
    Solver(const Position sr, const Position sc, const Grid *grid) : sr(sr), sc(sc), grid(grid) {}

    Score solve(std::vector<Direction> *answer) const {
        Score best_score = -1;
        std::shared_ptr<Node> preliminary_answer;

        UnsignedInteger shuffles[][4] = // 進行方向の優先順位 (いくつか試す)
            {
                { 0, 1, 2, 3 },
                { 1, 2, 3, 0 },
            };

        using Priority = std::make_signed_t<Position>;
        Priority priority_sign = 1;

        // { // 中心からの渦巻きはあまりよくなさそう
        //     Position dr = sr - SIZE/2;
        //     Position dc = sc - SIZE/2;
        //     if(dr*dr + dc*dc < SIZE*SIZE/4) priority_sign = -1;
        //     else priority_sign = 1;
        // }
        // debug(priority_sign);

        for(const auto &shuffle : shuffles) {
            Timer timer(TIME_LIMIT_MS/std::size(shuffles));

            Board board(grid, Point{sr, sc});

            std::stack<std::pair<std::shared_ptr<Node>, bool>> stack;
            stack.emplace(std::shared_ptr<Node>(new Node(Parent{}, board.score)), true);

            int cnt = 0;
            while(!timer.expired() and not stack.empty()) { // DFS
                ++cnt;
                auto [ node, preorder ] = stack.top(); stack.pop();
                if(preorder) {  // 上り
                    if(node->parent.has_value()) board.move(node->parent.value().first);

                    if(board.score > best_score) {
                        best_score = board.score;
                        preliminary_answer = node;
                    }

                    std::vector<std::pair<Priority, Direction>> dirs;
                    for(Direction dir = 0; dir < 4; dir++) {
                        if(not board.can_move(shuffle[dir])) continue;
                        const Position dr = (board.point.row + DRS[shuffle[dir]]) - SIZE/2;
                        const Position dc = (board.point.col + DCS[shuffle[dir]]) - SIZE/2;
                        const Priority priority = (dr * dr + dc * dc) * priority_sign;
                        dirs.emplace_back(priority, dir);
                    }
                    std::sort(dirs.begin(), dirs.end()); // 優先度の大きいものが後ろに来るように．

                    stack.emplace(node, false);

                    for(const auto &[_, dir] : dirs) {
                        const Score moved_score = board.moved_score(shuffle[dir]);

                        auto child_ptr = std::shared_ptr<Node>(new Node(Parent({ shuffle[dir], node }), moved_score));
                        stack.emplace(child_ptr, true);
                    }
                }
                else {  // 下り
                    if(node->parent.has_value()) board.remove(node->parent.value().first);
                }
            }
            std::clog << "Loops: " << cnt << "\n";
            std::clog << "Best internal score: " << best_score << "\n";
        }

        auto node = preliminary_answer; // ポインタを逆順に辿る
        while(node->parent.has_value()) {
            auto [dir, parent] = node->parent.value();
            answer->push_back(dir);
            node = parent;
        }

        reverse(answer->begin(), answer->end());

        return best_score;
    }
};

__attribute__((constructor)) inline void fast_io() { std::ios::sync_with_stdio(false), std::cin.tie(nullptr); }

signed main() {
    if constexpr (DEVELOPMEMT_MODE) std::clog << "Executed in development mode." << "\n";
    else std::clog << "Executed in non-development mode." << "\n";

    Position sr, sc; std::cin >> sr >> sc;
    Grid grid; grid.read();

    const Solver solver(sr, sc, &grid);

    std::vector<Direction> answer;
    const Score score = solver.solve(&answer);

    print_answer(&std::cout, answer, &std::clog, score);

    return 0;
}
