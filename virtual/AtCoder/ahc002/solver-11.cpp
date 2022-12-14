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
#include <fstream>

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

// 地点
struct Point {
    Position row, col;

    Point(const Position row, const Position col) : row(row), col(col) {}
    Point(const Position id = -1) : row(id/SIZE), col(id%SIZE) {}

    Position id() const { return this->row*SIZE + this->col; }

    inline bool operator==(const Point &other) const {
        return this->row == other.row and this->col == other.col;
    }
    inline bool operator!=(const Point &other) const {
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
                if(this->tile_direction(p) >= 0) continue;
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

    inline Point same_point(const Point &point) const {
        if(this->tile_direction(point) < 0) return point;
        Direction dir = this->tile_direction(point.id());
        return Point(point.row + DRS[dir], point.col + DCS[dir]);
    }

    inline Direction tile_direction(const Position pos) const {
        return this->_tiles[pos];
    }
    inline Direction tile_direction(const Point &point) const {
        return tile_direction(point.id());
    }

    inline Value value(const Position pos) const {
        return this->_values[pos];
    }
    inline Value value(const Point &point) const {
        return value(point.id());
    }
};

struct Input : private Uncopyable {
    const Grid &grid;
    const Point &start;

    Input(const Grid &grid, const Point &start) : grid(grid), start(start) {}
};

// 盤面を保持
struct Board {
    enum class Type : std::int8_t { Empty, Up, Right, Down, Left, Used };

  private:
    const Input *_input;
    Score _score = 0;

    std::array<Type,AREA> _data;

    Position _terminator0 = -1, _terminator1 = -1;

    inline Type set_direction(const Position point, const Direction dir) {
        if(dir == 0) return this->_data[point] = Type::Up;
        if(dir == 1) return this->_data[point] = Type::Right;
        if(dir == 2) return this->_data[point] = Type::Down;
        if(dir == 3) return this->_data[point] = Type::Left;
        assert(false);
    }

    inline const Grid& grid() const { return this->_input->grid; }
    inline const Point& start() const { return this->_input->start; }

  public:
    Board(const Input *const input) : _input(input) {
        this->_data.fill(Type::Empty);
        this->_score = this->grid().value(this->start());
    }

    inline bool operator<(const Board &other) const { return this->_score < other._score; }
    inline bool operator>(const Board &other) const { return this->_score > other._score; }

    inline bool terminated(const Position point) const { return point == this->_terminator0 or point == this->_terminator1; }
    inline bool terminated(const Point &point) const { return this->terminated(point.id()); }

    static constexpr bool empty(const Type type) { return type == Type::Empty; };
    inline bool empty(const Position pos) const { return Board::empty(this->_data[pos]); }
    inline bool empty(const Point &point) const { return this->empty(point.id()); }

    static constexpr bool used(const Type type) { return type == Type::Used; };
    inline bool used(const Position pos) const { return Board::used(this->_data[pos]); }
    inline bool used(const Point &point) const { return this->used(point.id()); }

    static constexpr bool directed(const Type type) { return type == Type::Up or type == Type::Right or type == Type::Down or type == Type::Left; }
    inline bool directed(const Position pos) const { return Board::directed(this->_data[pos]); }
    inline bool directed(const Point &point) const { return this->directed(point.id()); }


    inline Score score() const { return this->_score; }

    inline void set_terminator(const Point &point) {
        this->_terminator0 = point.id();
        this->_terminator1 = this->grid().same_point(point).id();
    }

    inline Point put(const Point &point, const Direction dir) {
        auto p = point.id(), q = this->grid().same_point(point).id();
        dev_assert(this->empty(p) and not this->terminated(point)); dev_assert(this->empty(q));

        this->_data[q] = Type::Used;
        this->set_direction(p, dir);

        auto next = Point(point.row + DRS[dir], point.col + DCS[dir]);

        this->_score += this->grid().value(next);

        return next;
    }

    inline Point advanced(const Point &point) const {
        auto dir = this->direction(point);
        return Point(point.row + DRS[dir], point.col + DCS[dir]);
    }

    inline void pop(const Point &point, const Point &score_source) {
        auto p = point.id(), q = this->grid().same_point(point).id();
        dev_assert(this->directed(p)); dev_assert(p == q or this->used(q));

        this->_score -= this->grid().value(score_source);

        this->_data[p] = this->_data[q] = Type::Empty;
    }

    inline Point pop_forward(const Point &point) {
        return this->pop_forward(point, this->advanced(point));
    }
    inline Point pop_forward(const Point &point, const Point &score_source) {
        this->pop(point, score_source);
        return score_source;
    }

    inline Point pop_backward(const Point &point) {
        return this->pop_backward(point, this->advanced(point));
    }
    inline Point pop_backward(const Point &point, const Point &score_source) {
        this->pop(point, score_source);
        return point;
    }

    inline bool can_set(const Point &point) const {
        if(point.row < 0 or point.row >= SIZE) return false;
        if(point.col < 0 or point.col >= SIZE) return false;
        return this->empty(point) and not this->terminated(point);
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

    inline std::string _debug() const {
        constexpr const char* CHIPS = ".A>V<-";
        std::string res = "\n";
        for(Position row=0; row<SIZE; ++row) {
            for(Position col=0; col<SIZE; ++col) {
                const Position p = Point{row, col}.id();
                res += this->terminated(p) ? '#' : CHIPS[static_cast<std::underlying_type_t<Type>>(this->_data[p])];
                res += " ";
            }
            res += "\n";
        }
        return res;
    }
};

struct Outputter : private Uncopyable {
  private:
    std::ostream *out = nullptr;

    const Input *input;

  public:
    Outputter(std::ostream *const out, const Input *const input) : out(out), input(input) {}
    Outputter(const Input *const input) : input(input) {}

    inline void set_sink(std::ostream *const out) { this->out = out; }

    inline std::string build_answer(const Board &source, Point *const last_point = nullptr) const {
        std::string res;
        Point point = this->input->start;
        Board validate(this->input);
        while(source.directed(point)) {
            dev_assert(validate.can_set(point));
            auto dir = source.direction(point);
            point = validate.put(point, dir);
            res.push_back(DIRECTIONS[dir]);
            if(last_point != nullptr) *last_point = point;
        }
        return res;
    }

    inline void print_answer(const Board &source) const {
        if(this->out != nullptr) *this->out << this->build_answer(source) << "\n";
    }

    inline void print_answer(const std::string answer) const {
        if(this->out != nullptr) *this->out << answer << "\n";
    }
};

RandomEngine random_engine;

struct Modifier {
    using Neighbor = std::int8_t;

  private:
    const Grid &grid;

  public:
    Modifier(const Grid & grid) : grid(grid) {}

    inline Neighbor choose(const Timer::Progress &progress) const {
        return 30 - 20 * progress;
    }

    inline bool apply(Board *const board, const Neighbor neighbor) const {
        static constexpr int shuffle[4] = { 0, 1, 2, 3 };

        Position start;
        do { start = random_engine(AREA); } while(not board->directed(start));

        Point goal = this->destroy(board, start, neighbor);

        Timer timer(10);

        return this->dfs(board, start, goal, shuffle, timer, 5*neighbor);
    }

    inline Point destroy(Board *const board, const Point &start, const Position length) const {
        dev_assert(board->directed(start));
        Point point = start;

        Position count = 0;
        while(count++ < length and board->directed(point)) {
            point = board->pop_forward(point);
        }
        return point;
    }

    inline bool dfs(
        Board *const board,
        const Point &start, const Point &goal,
        const int shuffle[4], const Timer &timer,
        const std::size_t stack_reservation_size,
        Board *const best_board = nullptr
    ) const {
        using Priority = std::make_signed_t<Position>;

        Stack<std::common_type_t<Direction,Position>> stack; stack.reserve(stack_reservation_size);

        Point point = start;
        stack.push(100);

        int count = 0;
        while(true) {  // DFS
            if(++count%100 == 0 and timer.expired()) return (debug("timed out")), false;
            if(stack.empty()) return (debug("stack empty")), false;

            auto motion = stack.top(); stack.pop();
            if(motion >= 0) {  // 上り
                Point prev_point = point;
                if(motion < 4) {
                    dev_assert(board->can_move(point, motion));
                    point = board->put(point, motion);
                }

                std::vector<std::pair<Priority, Direction>> dirs; dirs.reserve(4);
                for(Direction dir=0; dir<4; ++dir) {
                    if(this->grid.tile_direction(point) == shuffle[dir]) continue;

                    Point next = Point(point.row + DRS[shuffle[dir]], point.col + DCS[shuffle[dir]]);

                    if(next == goal) {
                        board->put(point, shuffle[dir]);
                        return true;
                    }

                    if(not board->can_set(next)) continue;

                    if(best_board == nullptr) {
                        dirs.emplace_back(random_engine(), dir);
                        continue;
                    }

                    constexpr Position MID = SIZE/2;
                    const Position dr = next.row - MID;
                    const Position dc = next.col - MID;

                    const Priority priority = (dr * dr + dc * dc);

                    dirs.emplace_back(priority, dir);
                }
                std::sort(dirs.begin(), dirs.end());  // 優先度の大きいものが後ろに来るように．

                if(motion < 4) stack.push(-prev_point.id()-1);
                for(const auto &[_, dir] : dirs) {
                    stack.push(shuffle[dir]);
                }
            }
            else {  // 下り
                if(best_board != nullptr and board->score() > best_board->score()) {
                    *best_board = *board;
                }
                point = board->pop_backward(-motion-1, point);
            }
        }
    }
};

struct Annealer : private Uncopyable {
  private:
    template<class Data> struct State {
      private:
        Data _current, _best, _saved;
        Outputter *logger = nullptr;

      public:
        State(const Data &init) : _current(init), _best(init), _saved(init) {}
        State(const Data &init, Outputter *const logger) : State(init) { this->logger = logger; }

        inline Data& current() { return this->_current; }
        inline const Data& best() const { return this->_best; }
        inline const Data& saved() const { return this->_saved; }

        inline void update_best() {
            if(this->_current > this->_best) this->_best = this->_current;
            if constexpr(DEVELOPMEMT_MODE) debug(this->_best.score());
        }
        inline void save() {  this->_saved = this->_current; }
        inline void rollback() { this->_current = std::move(this->_saved); }
        // inline void save() { logger->print_answer(this->_current), debug(this->_current); this->_saved = this->_current; }
    };

    const Modifier &modifier;

    double start_temp, end_temp, temp_change;

  public:
    Annealer(const Modifier &modifier, const double start_temp, const double end_temp)
        : modifier(modifier), start_temp(start_temp), end_temp(end_temp), temp_change(end_temp - start_temp)
    {}

    Board anneal(Board const &board, const Timer &timer, Outputter *const logger = nullptr) {
        State<Board> state(board, logger);

        int count = 0;
        while(true) {
            if(++count%1000 == 0 and timer.expired()) {
                std::cerr << "Annealing: Iterations: " << count << std::endl;
                break;
            }

            const auto progress = timer.progress();
            const double temp = this->start_temp + this->temp_change * progress;
            // debug(progress, temp);

            state.save();

            auto neighboor = this->modifier.choose(progress);
            const bool successful = this->modifier.apply(&state.current(), neighboor);

            if(not successful) {
                state.rollback();
                continue;
            }

            Score score_change = state.current().score() - state.saved().score();

            const double appling_probability = score_change > 0 ? 1 : std::exp(score_change / temp);
            if(appling_probability > random_engine.real()) state.update_best();
            else state.rollback();
        }

        return state.best();
    }
};

struct Solver : private Uncopyable {
  private:
    const Input *input;  // 入力

    const Modifier modifier;

    static constexpr Timer::Time TIME_LIMIT_MS = 1990;
    static constexpr Timer::Time INITIALIZATION_TIME_LIMIT_MS = 5;

    Board best_board;

  public:
    Solver(const Input *const input)
        : input(input), modifier(input->grid), best_board(input)
    {}

    inline Board solve() {
        Timer timer(this->TIME_LIMIT_MS);

        Outputter logger(this->input);

        if(DEVELOPMEMT_MODE) logger.set_sink(&std::cerr);

        this->initial_solution(logger);

        logger.print_answer(this->best_board);
        debug(this->best_board);

        Annealer annealer(modifier, 200, 10);
        this->best_board = annealer.anneal(this->best_board, timer, &logger);

        logger.print_answer(this->best_board);
        std::clog << "Currently best internal score: " << this->best_board.score() << "\n";\
        debug(this->best_board);

        return this->best_board;
    }

    inline void initial_solution(const Outputter &logger) {
        int shuffle[4] = { 0, 1, 2, 3 };  // 進行方向の優先順位 (4! 通り試す)
        Timer timer(this->INITIALIZATION_TIME_LIMIT_MS);
        do {
            timer.reset();

            Board board(this->input);

            this->modifier.dfs(&board, this->input->start, Point{-1, -1}, shuffle, timer, 5*AREA, &this->best_board);

            Point last_point(0, 0);
            logger.build_answer(this->best_board, &last_point);
            debug(last_point, this->input->grid.value(last_point));
            this->best_board.set_terminator(last_point);

            std::clog << "Currently best internal score: " << this->best_board.score() << "\n";
        } while(std::next_permutation(std::begin(shuffle), std::end(shuffle)));
    }
};

inline void fast_io() { std::ios::sync_with_stdio(false), std::cin.tie(nullptr); }

signed main() {
    fast_io();

    if constexpr (DEVELOPMEMT_MODE) std::clog << "Executed in development mode." << "\n";
    else std::clog << "Executed in non-development mode." << "\n";

    Point start; std::cin >> start.row >> start.col;
    Grid grid; grid.read();

    Input input(grid, start);

    Solver solver(&input);
    const Board best = solver.solve();

    Outputter outputter(&std::cout, &input);
    outputter.print_answer(best);

    return EXIT_SUCCESS;
}
