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
#include <list>

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

using Score = std::int32_t;

constexpr Position SIZE = 50;
constexpr Position AREA = SIZE*SIZE;

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
    using Time = std::int32_t;

  private:
    const Time time_limit;
    std::chrono::system_clock::time_point clock_start;

  public:
    using Progress = double;

    Timer(const Time time_limit = 0) : time_limit(time_limit), clock_start(std::chrono::system_clock::now()) {}

    inline Time limit() {
        return this->time_limit;
    }

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
    using result_type = typename Engine::result_type;
    using signed_result_type = typename std::make_signed_t<result_type>;

  private:
    mutable Engine engine;

  public:
    static constexpr result_type MIN = Engine::min();
    static constexpr result_type MAX = Engine::max();

    static constexpr result_type min() { return MIN; }
    static constexpr result_type max() { return MAX; }

    RandomEngine(unsigned long seed = 3141592653UL) { this->engine.seed(seed); };

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
        return static_cast<T>(this->engine()) / this->max();
    }
};

// 地点
struct Point {
    Position row, col;

    Point(const Position row, const Position col) : row(row), col(col) {}
    Point(const Position id) : row(id/SIZE), col(id%SIZE) {}

    Position id() const { return this->row*SIZE + this->col; }

    inline bool operator==(const Point& other) const {
        return this->id() == other.id();
    }
    inline bool operator!=(const Point& other) const {
        return not (*this == other);
    }

    inline std::pair<Position, Position> _debug() const {
        return { this->row, this->col };
    }
};

// 入力された盤面の情報．コピーされない．
struct Grid : private Uncopyable {
    using Value = std::int16_t;

  private:
    std::array<Direction,AREA> _tiles;
    std::array<Value,AREA> _values;

    inline bool same(Point p, Point q) const {
        return this->tile_dirc(p) == this->tile_dirc(q);
    }

    inline constexpr Direction inversed(const Direction dir) { return (dir+2)%4; }

  public:
    Grid() : _tiles(), _values() {}

    void read() {
        this->_tiles.fill(-1);

        std::array<Direction,AREA> tile_numbers;

        for(Position pos=0; pos<AREA; ++pos) std::cin >> tile_numbers[pos];
        for(Position pos=0; pos<AREA; ++pos) std::cin >> this->_values[pos];

        for(Position row=0; row<SIZE; ++row) {
            for(Position col=0; col<SIZE; ++col) {
                Position p = Point{row, col}.id();
                if(this->tile_dirc(p) >= 0) continue;
                for(Direction dir=0; dir<2; ++dir) {
                    Point adj = Point(row + DRS[dir], col + DCS[dir]);
                    if(adj.row < 0 or adj.row >= SIZE) continue;
                    if(adj.col < 0 or adj.col >= SIZE) continue;
                    Position q = adj.id();
                    if(tile_numbers[p] == tile_numbers[q]) {
                        this->_tiles[p] = dir;
                        this->_tiles[q] = inversed(dir);
                    }
                }
            }
        }
    }

    inline Direction tile_dirc(const Position pos) const {
        return this->_tiles[pos];
    }
    inline Direction tile_dirc(const Point &point) const {
        return tile_dirc(point.id());
    }

    inline Point same_point(const Point &point) const {
        if(this->tile_dirc(point) < 0) return point;
        Direction dir = this->tile_dirc(point.id());
        return Point(point.row + DRS[dir], point.col + DCS[dir]);
    }

    inline Value value(const Position pos) const {
        return this->_values[pos];
    }
    inline Value value(const Point &point) const {
        return value(point.id());
    }
};

// 盤面を保持
struct Board {
    enum class Type : std::int8_t { Empty, Up, Down, Left, Right, Passed };

  private:
    const Grid *_grid = nullptr;
    Score _score = 0;

    std::array<Type,AREA> _data;

    inline Type set_direction(const Position point, const Direction dir) {
        if(dir == 0) return this->_data[point] = Type::Up;
        if(dir == 1) return this->_data[point] = Type::Right;
        if(dir == 2) return this->_data[point] = Type::Down;
        if(dir == 3) return this->_data[point] = Type::Left;
        assert(false);
    }

  public:
    Board() : _data() {}
    Board(const Grid *grid, const Point start) : _grid(grid) {
        this->_data.fill(Type::Empty);
        this->_score = this->_grid->value(start);
    }

    static constexpr bool empty(const Type type) { return type == Type::Empty; };
    inline bool empty(const Position pos) const { return Board::empty(this->_data[pos]); }
    inline bool empty(const Point point) const { return this->empty(point.id()); }

    static constexpr bool scorable(const Type type) { return type != Type::Empty and type != Type::Passed; };
    inline bool scorable(const Position pos) const { return Board::scorable(this->_data[pos]); }
    inline bool scorable(const Point point) const { return this->scorable(point.id()); }


    inline Score score() const { return this->_score; }

    inline Point put(const Point &point, const Direction dir) {
        auto p = point.id(), q = this->_grid->same_point(point).id();
        dev_assert(this->empty(p)); dev_assert(this->empty(q));

        this->set_direction(p, dir), this->set_direction(q, dir);

        auto next = Point(point.row + DRS[dir], point.col + DCS[dir]);
        this->_score += this->_grid->value(next);

        return next;
    }

    inline Point pop(const Point &point) {
        auto dir = this->direction(point);
        return this->pop(point, Point(point.row + DRS[dir], point.col + DCS[dir]));
    }
    inline Point pop(const Point &point, const Point &score_source) {
        auto p = point.id(), q = this->_grid->same_point(point).id();
        dev_assert(this->scorable(p)); dev_assert(not this->empty(q));

        this->_score -= this->_grid->value(score_source);

        this->_data[p] = this->_data[q] = Type::Empty;

        return point;
    }

    inline bool can_set(const Point &point) const {
        if(point.row < 0 or point.row >= SIZE) return false;
        if(point.col < 0 or point.col >= SIZE) return false;
        return this->empty(point);
    }
    inline bool can_move(const Point &point, const Direction dir) const {
        Point next = Point(point.row + DRS[dir], point.col + DCS[dir]);
        return this->can_set(next);
    }

    inline Direction direction(const Point &point) const {
        auto type = this->_data[point.id()];
        if(type == Type::Up) return 0;
        if(type == Type::Right) return 1;
        if(type == Type::Down) return 2;
        if(type == Type::Left) return 3;
        assert(false);
    }
};

inline void print_answer(std::ostream *out, const std::string answer) {
    *out << answer << "\n";
}

inline void print_answer(std::ostream *out, const std::string answer, std::ostream *log, const Score score) {
    *log << score << "\n";
    print_answer(out, answer);
}

struct State {
    Board board, best_board;

    State(const Board &board) : board(board), best_board(board) {}

    void update_best(const State &state) {
        this->best_board = state.board;
    }

    bool operator<(const State &others) const {
        return this->board.score() < others.board.score();
    }
};

RandomEngine random_engine;

// struct Modifier {
//     using Neighbor = int;

//     Neighbor choose(const State &state) {
//         return 0;
//     }

//     void apply(State *state, const Neighbor neighbor) {
//         if(neighbor == 0) {
//             // int start = random_engine(state->board.root.size());
//             // auto board = destroyed(&state->board, start, 30);

//             // Timer timer(1000);
//             // UnsignedInteger shuffle[] = { 0, 1, 2, 3 };

//             // this->dfs(&board, state->board.root[std::min(start+30UL, state->board.root.size())], shuffle, timer);

//             // {
//             //     auto history_start_itr = next(state->board.history.begin(), start);
//             //     auto root_start_itr = next(state->board.root.begin(), start);

//             //     state->board.history.erase(history_start_itr, next(history_start_itr, 30));
//             //     state->board.root.erase(root_start_itr, next(root_start_itr, 30));

//             //     state->board.history.insert(next(state->board.history.begin(), start), board.history.begin(), board.history.end());
//             //     state->board.history.insert(next(state->board.history.begin(), start), board.history.begin(), board.history.end());
//             // }
//         }
//     }
//     void restore(State *state, const Neighbor neighbor) {
//     }

//     Board destroyed(Board *source, const int start, const int count) {
//         // Board board(source->grid, source->root[start]);

//         // dev_assert(board.root.size() == 1);
//         // dev_assert(board.history.size() == 0);

//         // auto last = start + count;
//         // if(last > source->root.size()) last = source->root.size();
//         // debug(start, last);
//         // debug(source->root[start], source->root[last]);

//         // for(auto p=source->root.begin(), end = p+start+1; p != end; ++p) {
//         //     board.visited[board.grid->tile_dirc(*p)] = true;
//         // }
//         // for(auto p=source->root.begin()+last+1; p != source->root.end(); ++p) {
//         //     board.visited[board.grid->tile_dirc(*p)] = true;
//         // }

//         // return board;
//     }

//     // inline void dfs(
//     //     Board *board, const Point goal,
//     //     const UnsignedInteger shuffle[4], const Timer &timer,
//     //     Board *best_board = nullptr
//     // ) {
//     //     using Priority = std::make_signed_t<Position>;

//     //     Stack<Direction> stack; stack.reserve(5*AREA);
//     //     stack.push(100);

//     //     dev_assert(not stack.empty());

//     //     int cnt = 0;

//     //     while(board->point != goal and not timer.expired()) {  // DFS
//     //         ++cnt;
//     //         auto motion = stack.top(); stack.pop();
//     //         if(motion >= 0) {  // 上り
//     //             if(motion < 4) board->move(motion);
//     //             // if(best_board == nullptr) debug(motion);

//     //             std::vector<std::pair<Priority, Direction>> dirs; dirs.reserve(4);
//     //             for(Direction dir = 0; dir < 4; dir++) {
//     //                 if(not board->can_move(shuffle[dir])) continue;
//     //                 const Position dr = (board->point.row + DRS[shuffle[dir]]) - SIZE/2;
//     //                 const Position dc = (board->point.col + DCS[shuffle[dir]]) - SIZE/2;
//     //                 const Priority priority = best_board == nullptr ? random_engine() : (dr * dr + dc * dc);
//     //                 dirs.emplace_back(priority, dir);
//     //             }
//     //             std::sort(dirs.begin(), dirs.end());  // 優先度の大きいものが後ろに来るように．

//     //             stack.push(-1);
//     //             for(const auto &[_, dir] : dirs) stack.push(shuffle[dir]);
//     //         }
//     //         else {  // 下り
//     //             if(best_board != nullptr and best_board->score < board->score) *best_board = *board;
//     //             board->remove();
//     //         }
//     //     }
//     //     std::clog << "Loops: " << cnt << "\n";
//     // }
// };

// template<class RandomEngine>
// struct Annealer {
//     RandomEngine *random_engine;
//     Modifier modifier;

//     double start_temp, end_temp, temp_duration;

//     Annealer(const double start_temp, const double end_temp, const RandomEngine *random_engine)
//         : random_engine(random_engine), start_temp(start_temp), end_temp(end_temp), temp_duration(start_temp - end_temp)
//     {}

//     void anneal(State *state, const Timer timer) {
//         State best_state;
//         while(not timer.expired()) {
//             const auto progress = timer.progress();
//             const double temp = this->start_temp + () * progress;

//             Score score_change;
//             auto neighboor = this->modifier.choose(*state, &score_change);
//             this->modifier.apply(state, neighboor);

//             const double appling_probability = score_change > 0 ? 1 : std::exp(score_change / temp);

//             if(appling_probability > random_engine.real()) {
//                 if(best_state < state) {
//                     best_state.update_best(*state);
//                 }
//             }
//             else {
//                 this->modifier.restore(state, neighboor);
//             }
//         }
//     }
// };

struct Solver : private Uncopyable {
  private:
    const Point initial_point;  // 初期位置
    const Grid *grid = nullptr;  // 盤面

    static constexpr Timer::Time TIME_LIMIT_MS = 50;

    Board best_board;

  public:
    Solver(const Position sr, const Position sc, const Grid *grid) : initial_point(sr, sc), grid(grid) {}

    Score solve(std::string *answer) {
        constexpr int shuffles[][4] = { { 0, 1, 2, 3 }, { 1, 2, 3, 0 } };  // 進行方向の優先順位 (いくつか試す)

        Timer timer(this->TIME_LIMIT_MS / std::size(shuffles));
        for(const auto &shuffle : shuffles) {
            timer.reset();

            Board board(this->grid, this->initial_point);

            this->dfs(&board, this->initial_point, Point{-1, -1}, shuffle, timer, &this->best_board);

            std::clog << "Best internal score: " << this->best_board.score() << "\n";
        }

        this->build_answer(answer);
        // print_answer(&std::cout, *answer);

        // State state(this->best_board);
        // modifier.apply(&state, 0);

        // this->build_answer(answer, state.board.history);

        return this->best_board.score();
    }

    inline void dfs(
        Board *board,
        const Point start, const Point goal,
        const int shuffle[4], const Timer &timer,
        Board *best_board = nullptr
    ) const {
        using Priority = std::make_signed_t<Position>;

        Stack<std::common_type_t<Direction,Position>> stack; stack.reserve(5*SIZE*SIZE);
        stack.push(100);

        dev_assert(not stack.empty());

        int cnt = 0;
        Point point = start;
        while(point != goal) {  // DFS
            if(++cnt%100000 == 0 and timer.expired()) break;
            auto motion = stack.top(); stack.pop();
            if(motion >= 0) {  // 上り
                Point prev_point = point;
                if(motion < 4) {
                    point = board->put(point, motion);
                }

                std::vector<std::pair<Priority, Direction>> dirs; dirs.reserve(4);
                for(Direction dir=0; dir<4; ++dir) {
                    if(this->grid->tile_dirc(point) == shuffle[dir]) continue;

                    Point next = Point(point.row + DRS[shuffle[dir]], point.col + DCS[shuffle[dir]]);
                    if(not board->can_set(next)) continue;

                    constexpr Position MID = SIZE/2;
                    const Position dr = next.row - MID;
                    const Position dc = next.col - MID;

                    const Priority priority = (dr * dr + dc * dc);
                    dirs.emplace_back(priority, dir);
                }
                std::sort(dirs.begin(), dirs.end());  // 優先度の大きいものが後ろに来るように．

                stack.push(-prev_point.id()-1);
                for(const auto &[_, dir] : dirs) {
                    stack.push(shuffle[dir]);
                }
            }
            else {  // 下り
                if(board->score() > best_board->score()) {
                    *best_board = *board;
                }
                // auto _history = board.history;
                // std::string _answer; this->build_answer(&_answer, &_history); print_answer(&std::cout, _answer);
                point = board->pop(-motion-1, point);
            }
        }
        std::clog << "Loops: " << cnt << "\n";
    }

    inline void build_answer(std::string *answer) const {
        this->build_answer(answer, this->best_board);
    }
    inline void build_answer(std::string *answer, const Board &source) const {
        answer->clear();
        Point point = this->initial_point;
        while(source.scorable(point)) {
            auto dir = source.direction(point);
            *answer += DIRECTIONS[dir];
            point.row += DRS[dir], point.col += DCS[dir];
        }
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
