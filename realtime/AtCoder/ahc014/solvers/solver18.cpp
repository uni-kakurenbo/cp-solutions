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

#ifdef LOCAL_JUDGE
#include<debug>
#define debug(...) Debug::debug(Debug::split(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#define DEBUG(...) do { Debug::DEBUG(nintptr, "\033[3;35m#" + to_string(__LINE__) + "\033[m  "); Debug::DEBUG(__VA_ARGS__); Debug::DEBUG(nintptr, "\033[m\n"); } while(0);
#else
#define debug(...) { ; }
#define DEBUG(...) { ; }
#endif

#include <cassert>

#ifdef LOCAL_JUDGE
#define dev_assert(...) assert(__VA_ARGS__)
#else
#define dev_assert(...) { ; }
#endif

#include <cstdint>
#include <chrono>
#include <iostream>
#include <cmath>
#include <unordered_set>
#include <set>
#include <bitset>
#include <array>
#include <vector>
#include <deque>
#include <utility>
#include <tuple>
#include <algorithm>
#include <random>
#include <numeric>
#include <memory>
#include <optional>

using namespace std;

#define INF32 2147483647

using Integer = int32_t;
using UnsignedInteger = uint32_t;

using Time = int32_t;
using Score = int32_t;
using Hash = uint32_t;

constexpr Hash HASH_MAX = numeric_limits<Hash>::max();

constexpr Integer MAX_N = 61;
constexpr Integer MIN_N = 31;

constexpr Integer DX[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
constexpr Integer DY[8] = { 1, 0, -1, -1, -1, 0, 1, 1 };

class Timer {
  private:
    const Time time_limit;
    chrono::system_clock::time_point clock_start;

  public:
    Timer(const Time time_limit = 0) : time_limit(time_limit), clock_start(chrono::system_clock::now()) {}

    inline Timer* reset() {
        clock_start = chrono::system_clock::now();
        return this;
    }

    inline Time elapsed() const {
        return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - this->clock_start).count();
    }

    inline bool expired() const { return this->elapsed() > time_limit; }
};

template<class Engine = mt19937> struct RandomEngine {
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
        return (*this)() % max;
    }
    inline Integer operator()(Integer min, Integer max) const {
        dev_assert(min <= max);
        if(min == max) return min;
        return min + (*this)(max - min);
    };
};

struct Point {
    Integer x, y;
    Point(const Integer x = 0, const Integer y = 0) : x(x), y(y) {}

    inline bool operator<(const Point& other) const {
        return pair{ x, y } < pair{ other.x, other.y };
    }
    inline bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    inline pair<Integer, Integer> _debug() const {
        return { x, y };
    }
};

struct Line {
    Integer x0, y0, x1, y1;

    Line(const Integer x0, const Integer y0, const Integer x1, const Integer y1) : Line(Point(x0,y0), Point(x1,y1)) {}
    Line(const Point p0, const Point p1) : x0(min(p0,p1).x), y0(min(p0,p1).y), x1(max(p0,p1).x), y1(max(p0,p1).y) {};

    inline Hash hash() const {
        Hash id = ((x0 * MAX_N + y0) * MAX_N + x1) * MAX_N + y1;
        return id * 2654435761UL % HASH_MAX;
    }

    inline tuple<Integer, Integer, Integer, Integer> to_tuple() const {
        return make_tuple(x0, y0, x1, y1);
    }

    inline bool operator<(const Line& other) const {
        return this->to_tuple() < other.to_tuple();
    }
    inline bool operator==(const Line& other) const {
        return (
            min(x0, x1) == min(other.x0, other.x1) && max(x0, x1) == max(other.x0, other.x1) &&
            min(y0, y1) == min(other.y0, other.y1) && max(y0, y1) == max(other.y0, other.y1)
            );
    }

    inline bool lying_on(const Integer px, const Integer py) const {
        return (
            (min(x0, x1) <= px && px <= max(x0, x1)) &&
            (min(y0, y1) <= py && py <= max(y0, y1)) &&
            (this->y0 - this->y1) * (px - this->x0) == (this->x0 - this->x1) * (py - this->y0)
            );
    }

    inline bool overlapping(const Line& other) const {
        if ((this->y1 - this->y0) * (other.x1 - other.x0) != (other.y1 - other.y0) * (this->x1 - this->x0)) {
            return false;
        }

        if (
            !this->lying_on(other.x0, other.y0) && !this->lying_on(other.x1, other.y1) &&
            !other.lying_on(this->x0, this->y0) && !other.lying_on(this->x1, this->y1)
            ) {
            return false;
        }

        if (
            (this->lying_on(other.x0, other.y0) && this->lying_on(other.x1, other.y1)) ||
            (other.lying_on(this->x0, this->y0) && other.lying_on(this->x1, this->y1))
            ) {
            return true;
        }

        if (
            (this->x0 == other.x0 && this->y0 == other.y0) || (this->x0 == other.x1 && this->y0 == other.y1) ||
            (this->x1 == other.x0 && this->y1 == other.y0) || (this->x1 == other.x1 && this->y1 == other.y1)
            ) {
            return false;
        }

        return true;
    }

    inline pair<Point, Point> _debug() const {
        return { { x0, y0 }, { x1, y1 } };
    }
};

struct LineCollector {
    deque<Line> buffer;

  public:
    inline bool overlapping_any(const Line &target) const {

        bool res = any_of(buffer.cbegin(), buffer.cend(),
            [&target](const Line &line) { return target.overlapping(line); }
        );

        return res;
    }

    inline void add(Line& line) {
        this->buffer.push_back(line);
    }
    inline void emplace(const Integer x0, const Integer y0, const Integer x1, const Integer y1) {
        this->buffer.emplace_back(x0, y0, x1, y1);
    }

    inline void pop(const Integer times) {
        for (Integer i = 0; i < times; ++i) this->buffer.pop_back();
    }

    inline Integer size() const {
        return this->buffer.size();
    }

    inline Hash hash() const {
        return accumulate(
            this->buffer.cbegin(), this->buffer.cend(), Hash{},
            [](const Hash &acc, const Line &e) { return acc ^ e.hash(); }
        );
    }

    inline auto _debug() {
        return this->buffer;
    }
};

struct Rectangle {
  public:
    Integer x0, y0, x1, y1, x2, y2, x3, y3;

    Rectangle(const Integer x0, const Integer y0, const Integer x1, const Integer y1, const Integer x2, const Integer y2, const Integer x3, const Integer y3)
        : x0(x0), y0(y0), x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3) {}

    Rectangle()
        : x0(0), y0(0), x1(0), y1(0), x2(0), y2(0), x3(0), y3(0) {}

    inline tuple<Point, Point, Point, Point> _debug() const {
        return { { x0, y0 }, { x1, y1 }, { x2, y2 }, { x3, y3 } };
    }

    inline auto to_tuple() const {
        return make_tuple(x0, y0, x1, y1, x2, y2, x3, y3);
    }
    inline bool operator<(const Rectangle& other) const {
        return this->to_tuple() < other.to_tuple();
    }
};

template<> struct std::hash<Point> {
    inline size_t operator()(Point key) const {
        return key.x * MAX_N + key.y;
    }
};
template<> struct std::hash<Line> {
    inline size_t operator()(Line key) const {
        return key.hash();
    }
};

struct Converter {
  private:
    Integer N;

  public:
    Converter(const Integer N) : N(N) {}
    inline Integer pair_to_id(const Integer a, const Integer b) const {
        return a * N + b;
    }
    inline Integer id_to_first(const Integer id) const {
        return id / N;
    }
    inline Integer id_to_second(const Integer id) const {
        return id % N;
    }
};

struct Grid {
  private:
    Integer N;
    Converter converter;

  public:
    unordered_set<Point> buffer;

    Grid(const Integer N) : N(N), converter(N) {};

    inline bool is_valid(const Integer x, const Integer y) const {
        return 0 <= x && x < N && 0 <= y && y < N;
    }

    inline bool get(const Integer x, const Integer y) const {
        dev_assert(this->is_valid(x, y));
        return this->buffer.count({x,y});
    }

    inline void put(const Integer x, const Integer y) {
        dev_assert(!this->get(x, y));
        this->buffer.emplace(x, y);
    }

    inline void drop(const Integer x, const Integer y) {
        dev_assert(this->get(x, y));
        this->buffer.erase({ x, y });
        return;
    }

    inline string view() const {
        string res = "\n";
        for (Integer j = N - 1; j >= 0; --j) {
            for (Integer i = 0; i < N; ++i) {
                res += this->get(i, j) ? '#' : '.';
            }
            res += "\n";
        }
        return res;
    }
};

struct Board {
  public:
    Grid grid;
    LineCollector lines;

    Board(Grid grid) : grid(grid) {}

    inline void draw(const Rectangle& rectangle) {
        grid.put(rectangle.x0, rectangle.y0);
        lines.emplace(rectangle.x0, rectangle.y0, rectangle.x1, rectangle.y1);
        lines.emplace(rectangle.x1, rectangle.y1, rectangle.x2, rectangle.y2);
        lines.emplace(rectangle.x2, rectangle.y2, rectangle.x3, rectangle.y3);
        lines.emplace(rectangle.x3, rectangle.y3, rectangle.x0, rectangle.y0);
    }

    bool find_can_put(const Integer px, const Integer py, vector<Rectangle>* found) const {
        dev_assert(this->grid.get(px, py));

        for (Integer d = 0; d < 8; ++d) {
            const Integer dx0 = DX[d], dy0 = DY[d];
            const Integer dx1 = DX[(d + 2) % 8], dy1 = DY[(d + 2) % 8];

            Integer x00, y00, x01, y01;
            x00 = x01 = px, y00 = y01 = py;

            do { x00 += dx0, y00 += dy0; } while (this->grid.is_valid(x00, y00) && !this->grid.get(x00, y00));
            do { x01 += dx1, y01 += dy1; } while (this->grid.is_valid(x01, y01) && !this->grid.get(x01, y01));

            if (!this->grid.is_valid(x00, y00) || !this->grid.is_valid(x01, y01)) continue;

            if (this->lines.overlapping_any(Line{ px, py, x00, y00 })) continue;
            if (this->lines.overlapping_any(Line{ px, py, x01, y01 })) continue;

            const Integer ex0 = x00 - px, ey0 = y00 - py;
            const Integer ex1 = x01 - px, ey1 = y01 - py;

            const Integer gx0 = x00 + ex1, gy0 = y00 + ey1;
            const Integer gx1 = x01 + ex0, gy1 = y01 + ey0;

            if (gx0 != gx1 || gy0 != gy1) continue;
            if (!this->grid.is_valid(gx0, gy0)) continue;
            if (this->grid.get(gx0, gy0)) continue;

            if (this->lines.overlapping_any(Line{ x00, y00, gx0, gy0 })) continue;
            if (this->lines.overlapping_any(Line{ x01, y01, gx0, gy0 })) continue;

            Integer x10 = x00, y10 = y00;
            Integer x11 = x01, y11 = y01;

            do { x10 += dx1, y10 += dy1; } while (!(x10 == gx0 && y10 == gy0) && !this->grid.get(x10, y10));
            do { x11 += dx0, y11 += dy0; } while (!(x11 == gx0 && y11 == gy0) && !this->grid.get(x11, y11));

            if (x10 != gx0 || y10 != gy0 || x11 != gx0 || y11 != gy0) continue;

            found->emplace_back(gx0, gy0, x00, y00, px, py, x01, y01);
        }
        return found->size() > 0;
    }

    inline void find_all_can_put(vector<Rectangle>* found) {
        for (auto [x, y] : this->grid.buffer) {
            this->find_can_put(x, y, found);
        }
    }
};

inline void print_answer(ostream *out, const vector<Rectangle> answer) {
    (*out) << answer.size() << "\n";
    for (const Rectangle& rectangle : answer) {
        (*out) << rectangle.x0 << " " << rectangle.y0 << " ";
        (*out) << rectangle.x1 << " " << rectangle.y1 << " ";
        (*out) << rectangle.x2 << " " << rectangle.y2 << " ";
        (*out) << rectangle.x3 << " " << rectangle.y3 << "\n";
    }
}

inline void print_answer(ostream *out, const vector<Rectangle> answer, ostream *log, const Score score) {
    (*log) << score << "\n";
    print_answer(out, answer);
}

struct State {
    Score score;
    Hash hash;
    Board board;

    State(const Score score, const Hash hash, const Board& board) : score(score), hash(hash), board(board) {}

    Integer _debug() const {
        return score;
    }
};

struct Node;

struct Candidate {
    Rectangle rectangle;
    shared_ptr<Node> parent;
    Integer priority = 0;
    Score score = 0;
    Hash hash = 0;

    Candidate(const Rectangle& rectangle, const shared_ptr<Node>& parent, const Integer priority, const Score score, const Hash hash)
        : rectangle(rectangle), parent(parent), priority(priority), score(score), hash(hash) {}

    Candidate() {}

    inline bool operator<(const Candidate& other) const {
        Integer v0 = this->score, v1 = other.score;
        return v0 == v1 ? this->priority < other.priority : v0 < v1;
    }
    inline bool operator>(const Candidate& other) const {
        Integer v0 = this->score, v1 = other.score;
        return v0 == v1 ? this->priority > other.priority : v0 > v1;
    }
};

using Parent = optional<pair<Rectangle, shared_ptr<Node>>>;
using Children = vector<pair<Rectangle, weak_ptr<Node>>>;

struct Node {
    Parent parent;
    Children children;
    Integer score;
    Hash hash;

    Node(const Parent parent, const Children children, const Score score, const Hash hash) : parent(parent), children(children), score(score), hash(hash) {}
};


struct Evaluator {
    static constexpr Integer BASE_SCORE = 1000000;
    Integer N, M, C;
    float_t score_rate_P, score_rate_Q;

    Evaluator(const Integer N, const Integer M)
        : N(N), M(M), C((N - 1) / 2), score_rate_P(BASE_SCORE * 6), score_rate_Q(((N* N + 5)* M)) {};

    inline UnsignedInteger weight(const Integer x, const Integer y) const {
        return (x - C) * (x - C) + (y - C) * (y - C) + 1;
    }

    inline Score evaluate(const Board& board) const {
        auto dots = &board.grid.buffer;
        Integer weight_sum = accumulate(dots->cbegin(), dots->cend(), 0,
            [this](Integer acc, const Point& e) { return acc + this->weight(e.x, e.y); }
        );
        return weight_sum;
    }

    inline Integer calc_score(const Board& board) const {
        return round(score_rate_P * this->evaluate(board) / score_rate_Q);
    }
};

struct Modifier {
    const Converter converter;
    const Evaluator evaluator;

    Modifier(const Integer N, const Integer M) : converter(N), evaluator(N, M) {}

    inline Hash calc_modified_hash(const Hash hash, const Rectangle& rectangle) const {
        Hash res_hash = hash;
        res_hash ^= Line{rectangle.x0, rectangle.y0, rectangle.x1, rectangle.y1}.hash();
        res_hash ^= Line{rectangle.x1, rectangle.y1, rectangle.x2, rectangle.y2}.hash();
        res_hash ^= Line{rectangle.x2, rectangle.y2, rectangle.x3, rectangle.y3}.hash();
        res_hash ^= Line{rectangle.x3, rectangle.y3, rectangle.x0, rectangle.y0}.hash();
        return res_hash;
    }

    inline pair<Score,Hash> calc_modified_state(const Score score, const Hash hash, const Rectangle rectangle) const {
        Score res_score = score + evaluator.weight(rectangle.x0, rectangle.y0);
        return { res_score, this->calc_modified_hash(hash, rectangle) };
    }

    inline void apply(State *state, const Rectangle &rectangle) const {
        state->score += evaluator.weight(rectangle.x0, rectangle.y0);
        state->hash = this->calc_modified_hash(state->hash, rectangle);
        state->board.draw(rectangle);
    }

    inline void restore(State *state, const Rectangle &rectangle) const {
        state->score -= evaluator.weight(rectangle.x0, rectangle.y0);
        state->hash = this->calc_modified_hash(state->hash, rectangle);
        state->board.grid.drop(rectangle.x0, rectangle.y0);
        state->board.lines.pop(4);
    }
};

struct Tree {
    const Modifier &modifier;

    State state;
    shared_ptr<Node> node;
    vector<Candidate>* end_states;
    Integer rank;

    Tree(const Modifier &modifier, const State &state, const shared_ptr<Node> &node, vector<Candidate> *end_states, const Integer rank = 0)
        : modifier(modifier), state(state), node(node), end_states(end_states), rank(rank) {};

    void dfs(vector<Candidate>* next_states, const bool one, Integer* priority, const Integer dpath) {
        if (dpath == 0) {
            Score score = this->node->score;
            Hash hash = this->node->hash;

            dev_assert(score == state.score);
            dev_assert(hash == state.hash);

            vector<Rectangle> found;
            state.board.find_all_can_put(&found);

            if (found.empty()) {
                end_states->emplace_back(Rectangle{}, this->node, *priority, score, hash);
            }

            for (Rectangle& rectangle : found) {
                auto [next_score, next_hash] = modifier.calc_modified_state(score, hash, rectangle);
                next_states->emplace_back(rectangle, this->node, *priority, next_score, next_hash);
                // *priority += 1;
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

            for (const auto& [rectangle, ptr] : *children) {
                this->node = ptr.lock();

                modifier.apply(&state, rectangle);

                dfs(next_states, next_one, priority, dpath - 1);

                if (!next_one) {
                    modifier.restore(&state, rectangle);
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
    const Modifier modifier;

    BeamSearch(const Timer *timer, const State &state, const Modifier modifier) : timer(timer), state(state), modifier(modifier) {}

    void run(vector<Rectangle> *answer, Integer width) const {
        vector<Candidate> next_states, end_states;

        next_states.reserve(100000), end_states.reserve(100);

        Tree tree = {
            modifier, state,
            shared_ptr<Node>(new Node(Parent{}, Children{}, state.score, state.hash)),
            &end_states
        };

        vector<shared_ptr<Node>> current = { tree.node };
        current.reserve(width);

        unordered_set<Hash> visited;

        Integer loop_count = 0;
        Time loop_duration = 0;
        for (; ; ++loop_count) {
            Time loop_start_time = this->timer->elapsed();

            if(loop_duration < 30) ++width;
            else width = max(width - 1, 1);
            // debug(width);

            next_states.clear();

            Integer tmp = 0;
            tree.dfs(&next_states, true, &tmp, loop_count - tree.rank);

            if(next_states.empty()) {
                debug("broken");
                break;
            }

            if(this->timer->expired()) break;

            if ((Integer)next_states.size() > width) {
                nth_element(next_states.begin(), next_states.begin() + width, next_states.end(),
                    [](Candidate& a, Candidate& b) { return a > b; }
                );
                next_states.erase(next_states.begin() + width, next_states.end());
            }

            current.clear();
            visited.clear();
            for (const auto& [rectangle, parent, _priority, score, hash] : next_states) {
                if(visited.count(hash)) continue;
                visited.insert(hash);
                auto child_ptr = shared_ptr<Node>(new Node(Parent({ rectangle, parent }), Children{}, score, hash));
                parent->children.emplace_back(rectangle, weak_ptr<Node>(child_ptr));
                current.emplace_back(child_ptr);
            }

            loop_duration = timer->elapsed() - loop_start_time;

            // debug(loop_duration);
        }

        {
            Candidate best_state;
            if(!next_states.empty()) {
                auto itr = max_element(next_states.begin(), next_states.end());
                if(best_state.score < itr->score) best_state = *itr;
            }
            if(!end_states.empty()) {
                auto itr = max_element(end_states.begin(), end_states.end());
                if(best_state.score < itr->score) best_state = *itr;
            }

            auto [rectangle, node, _priority, score, _hash] = best_state;

            answer->reserve(500);

            while(node->parent.has_value()) {
                auto [rectangle, parent] = node->parent.value();
                answer->push_back(rectangle);
                node = parent;
            }

            reverse(answer->begin(), answer->end());

            clog << "Depth: " << loop_count << "\n";
            clog << "Last width: " << width << "\n";
            clog << "Score: " << score << "\n";
            clog << "Answer length: " << answer->size() << "\n";
        }

        return;
    }
};

struct Solver {
    const Integer N, M;
    const Grid grid;

    static constexpr Integer TIME_LIMIT_MS = 4800;

    Solver(const Integer N, const Integer M, const Grid &grid) : N(N), M(M), grid(grid) {}

    Score solve(vector<Rectangle> *answer) const {
        Timer timer(TIME_LIMIT_MS);

        Board board(grid);

        const Evaluator evaluator(N, M);
        const Modifier modifier(N, M);

        const Score score = evaluator.evaluate(board);
        const Hash hash = board.lines.hash();

        const State state(score, hash, board);

        { // Beam Search
            const BeamSearch beam_search(timer.reset(), state, modifier);
            const Integer width = 1 * pow(61.0 / N, 9.18116498453);
            debug(width);

            beam_search.run(answer, width);
        }

        for(Rectangle &rectangle : *answer) board.draw(rectangle);

        return evaluator.calc_score(board);
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    Integer N, M; cin >> N >> M;

    Grid grid(N);
    for (Integer i = 0; i < M; ++i) {
        Integer x, y; cin >> x >> y; grid.put(x, y);
    }

    const Solver solver(N, M, grid);

    vector<Rectangle> answer;
    const Score score = solver.solve(&answer);

    print_answer(&cout, answer, &clog, score);

    return 0;
}
