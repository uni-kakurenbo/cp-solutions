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
using SropeType = std::size_t;

using Integer = std::int32_t;
using UnsignedInteger = std::uint32_t;

using Time = std::int32_t;
using Score = std::int32_t;
using Hash = std::uint32_t;

using Value = std::int16_t;
using Tile = std::int16_t;

constexpr Hash HASH_PRIME = 2654435761UL;
constexpr Hash HASH_MAX = std::numeric_limits<Hash>::max();

constexpr Position SIZE = 50;

constexpr Position DRS[] = { -1, 0, 1, 0 }, DCS[] = { 0, 1, 0, -1 };
constexpr const char * DIRECTIONS = "URDL";

class Timer {
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

template<class Engine = std::mt19937> struct RandomEngine {
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

template<class T> struct Expander {
  private:
    T N;

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

struct Grid {
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

    Tile tile_number(const Position pos) const {
        return this->_tiles[pos];
    }
    Tile tile_number(const Position row, const Position col) const {
        return tile_number(this->converter.pair_to_id(row, col));
    }
    Tile tile_number(const Point point) const {
        return tile_number(this->converter.pair_to_id(point.row, point.col));
    }

    Value value(const Position pos) const {
        return this->_value[pos];
    }
    Value value(const Position row, const Position col) const {
        return value(this->converter.pair_to_id(row, col));
    }
    Value value(const Point point) const {
        return value(this->converter.pair_to_id(point.row, point.col));
    }
};

struct State {
  public:
    const Grid *grid;
    Point point;
    Score score;
    std::array<bool, SIZE*SIZE> visited;

    State(const Grid *grid, Point point) : grid(grid), point(point), score(this->grid->value(this->point)) {
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
        return this->score + this->grid->value(moved_point);
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

inline void print_answer(std::ostream *out, const std::vector<Direction> answer) {
    for(const Direction& dir : answer) (*out) << DIRECTIONS[dir];
}

inline void print_answer(std::ostream *out, const std::vector<Direction> answer, std::ostream *log, const Score score) {
    (*log) << score << "\n";
    print_answer(out, answer);
}

struct Node;

struct Candidate {
    Direction dir;
    std::shared_ptr<Node> parent;
    Integer priority = 0;
    Score score = 0;
    Integer noise = 0;

    Candidate(const Direction& dir, const std::shared_ptr<Node>& parent, const Integer priority, const Score score, const Integer noise = 0)
        : dir(dir), parent(parent), priority(priority), score(score), noise(noise) {}

    Candidate() {}

    inline bool operator<(const Candidate& other) const {
        auto v0 = this->score + this->noise, v1 = other.score + other.noise;
        return v0 == v1 ? this->priority < other.priority : v0 < v1;
    }
    inline bool operator>(const Candidate& other) const {
        auto v0 = this->score + this->noise, v1 = other.score + other.noise;
        return v0 == v1 ? this->priority > other.priority : v0 > v1;
    }
};

using Parent = std::optional<std::pair<Direction, std::shared_ptr<Node>>>;
using Children = std::vector<std::pair<Direction, std::weak_ptr<Node>>>;

struct Node {
    Parent parent;
    Children children;
    Score score;
    // Hash hash;

    Node(const Parent parent, const Children children, const Score score) : parent(parent), children(children), score(score) {}
};

RandomEngine random_engine;

struct Tree {
    State state;
    std::shared_ptr<Node> node;
    std::vector<Candidate>* end_states;
    Integer rank;

    Tree(const State &state, const std::shared_ptr<Node> &node, std::vector<Candidate> *end_states, const Integer rank = 0)
        : state(state), node(node), end_states(end_states), rank(rank) {};

    template<class Noise>
    void dfs(std::vector<Candidate> *next_states, const bool one, Integer *priority, const Integer dpath, const Noise noise) {
        if (dpath == 0) {
            Score score = this->node->score;
            // debug(state.point);
            // Hash hash = this->node->hash;

            // debug(score, state.score);
            dev_assert(score == state.score);
            // dev_assert(hash == state.hash);

            bool can_move[4] = { 0, 0, 0, 0 };
            state.find_all_can_move(can_move);

            // debug(can_move[0], can_move[1], can_move[2], can_move[3]);

            if(not can_move[0] and not can_move[1] and not can_move[2] and not can_move[3]) {
                end_states->emplace_back(Direction{}, this->node, *priority, score);
            }

            for(Direction dir=0; dir<4; ++dir) {
                if(not can_move[dir]) continue;
                // debug(dir);
                const Score next_score = state.moved_score(dir);
                next_states->emplace_back(dir, this->node, *priority, next_score, (*noise)());
            }
        }
        else {
            auto node_backup = this->node;
            auto *children = &node_backup->children;

            children->erase(
                remove_if(children->begin(), children->end(), [](auto& x) { return x.second.expired(); }),
                children->end()
            );

            bool next_one = one && children->size() == 1;

            ++this->rank;

            for (const auto &[dir, ptr] : *children) {
                this->node = ptr.lock();

                state.move(dir);

                dfs(next_states, next_one, priority, dpath - 1, noise);

                if (!next_one) {
                    state.remove(dir);
                }
            }

            if (!next_one) {
                this->node = node_backup;
                --this->rank;
            }
        }
    }
};

struct BeamSearch {
    const Timer *timer;
    const State state;

    BeamSearch(const Timer *timer, const State &state) : timer(timer), state(state) {}

    Score run(std::vector<Direction> *answer, size_t width) const {
        std::vector<Candidate> next_states, end_states;

        next_states.reserve(10000), end_states.reserve(300);

        Tree tree = {
            state,
            std::shared_ptr<Node>(new Node(Parent{}, Children{}, state.score)),
            &end_states
        };

        std::vector<std::shared_ptr<Node>> current = { tree.node };
        current.reserve(width);

        Integer loop_count = 0;
        Time loop_duration = 0;
        for (; ; ++loop_count) {
            const Integer noise_range = std::max(0, 100 - loop_count);
            auto noise = [&noise_range]() {
                return 0;
                // return random_engine(-noise_range, noise_range);
            };

            Time loop_start_time = this->timer->elapsed();

            // if(loop_duration < appropriate_race_duration) ++width;
            // else width = max(width - 1, 1UL);
            // debug(width);

            next_states.clear();

            Integer tmp = 0;
            tree.dfs(&next_states, true, &tmp, loop_count - tree.rank, &noise);

            if(next_states.empty()) {
                std::clog << "*broken" << "\n";
                break;
            }

            if(this->timer->expired()) break;

            if (next_states.size() > width) {
                nth_element(next_states.begin(), next_states.begin() + width, next_states.end(),
                    [](Candidate& a, Candidate& b) { return a > b; }
                );
                next_states.erase(next_states.begin() + width, next_states.end());
            }

            current.clear();
            // visited.clear();
            for (const auto& [dir, parent, _priority, score, _noise] : next_states) {
                auto child_ptr = std::shared_ptr<Node>(new Node(Parent({ dir, parent }), Children{}, score));
                parent->children.emplace_back(dir, std::weak_ptr<Node>(child_ptr));
                current.emplace_back(child_ptr);
            }

            // loop_duration = timer->elapsed() - loop_start_time;

            // debug(width, loop_duration);
        }

        Candidate best_state;

        {
            if(!next_states.empty()) {
                auto itr = max_element(next_states.begin(), next_states.end());
                if(best_state.score < itr->score) best_state = *itr;
            }
            if(!end_states.empty()) {
                auto itr = max_element(end_states.begin(), end_states.end());
                if(best_state.score < itr->score) best_state = *itr;
            }
        }

        auto [dir, node, _priority, score, _hash] = best_state;


        while(node->parent.has_value()) {
            auto [dir, parent] = node->parent.value();
            answer->push_back(dir);
            node = parent;
        }

        std::clog << "Depth: " << loop_count << "\n";
        std::clog << "Last width: " << width << "\n";
        std::clog << "Internal score: " << score << "\n";
        std::clog << "Answer length: " << answer->size() << "\n";

        return score;
    }
};

struct Solver {
    const Position sr, sc;
    const Grid *grid;

    static constexpr Time TIME_LIMIT_MS = 1850;

    static inline size_t SHAKED_WIDTH(const size_t base) { return random_engine(8, 15) * base / 10; }

    Solver(const Position sr, const Position sc, const Grid *grid) : sr(sr), sc(sc), grid(grid) {}

    Score solve(std::vector<Direction> *answer) const {
        Timer timer(TIME_LIMIT_MS);

        const State state(grid, Point{sr, sc});

        Score best_score = -1;
        std::vector<Direction> preliminary_answer;
        preliminary_answer.reserve(10000);

        // const auto appropriate_race_duration = APPROPRIATE_RACING_DURATION(N);
        const auto appropriate_race_duration = 100;

        // const auto basic_width = BASIC_WIDTH(N);
        // const Position basic_search_range = BASIC_SEARCH_RANGE;

        const auto basic_width = 500;

        auto width = basic_width;

        while(!timer.expired()) { // Beam Search
            std::clog << "---" << "\n";
            const BeamSearch beam_search(&timer, state);

            std::clog << "Beam width: " << width << "\n";

            preliminary_answer.clear();
            Score score = beam_search.run(&preliminary_answer, width);
            debug(timer.elapsed());

            if(score > best_score) {
                best_score = score;
                *answer = preliminary_answer;
            }

            width = SHAKED_WIDTH(basic_width);
        }

        std::clog << "Best internal score: " << best_score << "\n";

        reverse(answer->begin(), answer->end());

        return best_score;
    }
};

signed main() {
    if constexpr (DEVELOPMEMT_MODE) std::clog << "Executed in development mode." << "\n";
    else std::clog << "Executed in non-development mode." << "\n";

    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    Position sr, sc; std::cin >> sr >> sc;

    Grid grid; grid.read();

    const Solver solver(sr, sc, &grid);

    std::vector<Direction> answer;
    const Score score = solver.solve(&answer);

    print_answer(&std::cout, answer, &std::clog, score);

    return 0;
}
