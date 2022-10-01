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

constexpr int MAX_N = 61;
constexpr int MIN_N = 31;

constexpr int DX[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
constexpr int DY[8] = { 1, 0, -1, -1, -1, 0, 1, 1 };

using Hash = uint64_t;

struct RandomEngine {
    static constexpr uint32_t MAX = mt19937::max();

    RandomEngine(uint32_t seed = 3141592653UL) : x(seed) {
        engine.seed(seed);
    };

    uint32_t generate() {
        // x ^= x << 13; x ^= x >> 17; x ^= x << 15;
        // return x;
        return engine();
    }

    uint32_t range(uint32_t max) {
        return this->generate() % max;
    }

    uint32_t range(uint32_t min, uint32_t max) {
        dev_assert(min < max);
        return min + this->range(max - min);
    };

  private:
    uint32_t x;
    mt19937 engine;
};

struct Point {
    int x, y;
    Point(const int x = 0, const int y = 0) : x(x), y(y) {}

    inline bool operator<(const Point& other) const {
        return pair{ x, y } < pair{ other.x, other.y };
    }
    inline bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    pair<int, int> _debug() const {
        return { x, y };
    }
};

struct Line {
    int x0, y0, x1, y1;

    Line(const int x0, const int y0, const int x1, const int y1)
        : x0(x0), y0(y0), x1(x1), y1(y1) {}

    inline Hash hash() const {
        pair<Hash,Hash> p0 = {x0, y0}, p1 = {x1, y1};
        auto [a, b] = min(p0, p1);
        auto [c, d] = max(p0, p1);
        return ((a * MAX_N + b) * MAX_N + c) * MAX_N + d;
    }

    inline tuple<int, int, int, int> to_tuple() const {
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

    inline bool lying_on(const int px, const int py) const {
        return (
            (min(x0, x1) <= px && px <= max(x0, x1)) &&
            (min(y0, y1) <= py && py <= max(y0, y1)) &&
            (this->y0 - this->y1) * (px - this->x0) == (this->x0 - this->x1) * (py - this->y0)
            );
    }

    bool overlapping(const Line& other) const {
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

    pair<Point, Point> _debug() const {
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
    inline void emplace(const int x0, const int y0, const int x1, const int y1) {
        this->buffer.emplace_back(x0, y0, x1, y1);
    }

    inline void pop(const int times) {
        for (int i = 0; i < times; ++i) this->buffer.pop_back();
    }

    inline int size() const {
        return this->buffer.size();
    }

    inline Hash hash() const {
        return accumulate(
            this->buffer.cbegin(), this->buffer.cend(), Hash{},
            [](const Hash &acc, const Line &e) { return acc ^ e.hash(); }
        );
        // assert(this->buffer.size() % 4 == 0);
        // Hash res = 0;
        // for(auto itr=this->buffer.begin(); itr != this->buffer.end(); ) {
        //     res ^= itr++->hash();
        //     res ^= itr++->hash();
        //     res ^= itr++->hash();
        //     res ^= itr++->hash();
        // }
        // return res;
    }

    auto _debug() {
        return this->buffer;
    }
};

struct Rectangle {
  public:
    int x0, y0, x1, y1, x2, y2, x3, y3;

    Rectangle(const int x0 = -1, const int y0 = -1, const int x1 = -1, const int y1 = -1, const int x2 = -1, const int y2 = -1, const int x3 = -1, const int y3 = -1)
        : x0(x0), y0(y0), x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3) {}

    tuple<Point, Point, Point, Point> _debug() const {
        return { { x0, y0 }, { x1, y1 }, { x2, y2 }, { x3, y3 } };
    }

    inline tuple<int, int, int, int, int, int, int, int> to_tuple() const {
        return make_tuple(x0, y0, x1, y1, x2, y2, x3, y3);
    }
    inline bool operator<(const Rectangle& other) const {
        return this->to_tuple() < other.to_tuple();
    }
};

template<> struct std::hash<Point> {
    size_t operator()(Point key) const {
        return key.x * MAX_N + key.y;
    }
};
template<> struct std::hash<Line> {
    size_t operator()(Line key) const {
        return key.hash();
    }
};

struct Converter {
  private:
    int N;

  public:
    Converter(const int N) : N(N) {}
    inline int pair_to_id(const int a, const int b) const {
        return a * N + b;
    }
    inline int id_to_first(const int id) const {
        return id / N;
    }
    inline int id_to_second(const int id) const {
        return id % N;
    }
};

struct Grid {
  private:
    int N;
    Converter converter;

  public:
    unordered_set<Point> buffer;

    Grid(const int N) : N(N), converter(N) {};

    inline bool is_valid(const int x, const int y) const {
        return 0 <= x && x < N && 0 <= y && y < N;
    }

    inline bool get(const int x, const int y) const {
        dev_assert(this->is_valid(x, y));
        return this->buffer.count({x,y});
    }

    inline void put(const int x, const int y) {
        dev_assert(!this->get(x, y));
        this->buffer.emplace(x, y);
    }

    inline void drop(const int x, const int y) {
        dev_assert(this->get(x, y));
        this->buffer.erase({ x, y });
        return;
    }

    string view() const {
        string res = "\n";
        for (int j = N - 1; j >= 0; --j) {
            for (int i = 0; i < N; ++i) {
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

    bool find_can_put(const int px, const int py, vector<Rectangle>* found) const {
        dev_assert(this->grid.get(px, py));

        for (int d = 0; d < 8; ++d) {
            const int dx0 = DX[d], dy0 = DY[d];
            const int dx1 = DX[(d + 2) % 8], dy1 = DY[(d + 2) % 8];

            int x00, y00, x01, y01;
            x00 = x01 = px, y00 = y01 = py;

            do { x00 += dx0, y00 += dy0; } while (this->grid.is_valid(x00, y00) && !this->grid.get(x00, y00));
            do { x01 += dx1, y01 += dy1; } while (this->grid.is_valid(x01, y01) && !this->grid.get(x01, y01));

            if (!this->grid.is_valid(x00, y00) || !this->grid.is_valid(x01, y01)) continue;

            if (this->lines.overlapping_any(Line{ px, py, x00, y00 })) continue;
            if (this->lines.overlapping_any(Line{ px, py, x01, y01 })) continue;

            const int ex0 = x00 - px, ey0 = y00 - py;
            const int ex1 = x01 - px, ey1 = y01 - py;

            const int gx0 = x00 + ex1, gy0 = y00 + ey1;
            const int gx1 = x01 + ex0, gy1 = y01 + ey0;

            if (gx0 != gx1 || gy0 != gy1) continue;
            if (!this->grid.is_valid(gx0, gy0)) continue;
            if (this->grid.get(gx0, gy0)) continue;

            if (this->lines.overlapping_any(Line{ x00, y00, gx0, gy0 })) continue;
            if (this->lines.overlapping_any(Line{ x01, y01, gx0, gy0 })) continue;

            int x10 = x00, y10 = y00;
            int x11 = x01, y11 = y01;

            do { x10 += dx1, y10 += dy1; } while (!(x10 == gx0 && y10 == gy0) && !this->grid.get(x10, y10));
            do { x11 += dx0, y11 += dy0; } while (!(x11 == gx0 && y11 == gy0) && !this->grid.get(x11, y11));

            if (x10 != gx0 || y10 != gy0 || x11 != gx0 || y11 != gy0) continue;

            found->emplace_back(gx0, gy0, x00, y00, px, py, x01, y01);
        }
        return found->size() > 0;
    }

    void find_all_can_put(vector<Rectangle>* found) {
        for (auto [x, y] : this->grid.buffer) {
            this->find_can_put(x, y, found);
        }
    }
};

constexpr int BASE_SCORE = 1000000;
using Score = int;

struct Evaluator {
    int N, M, C;
    double score_rate_P, score_rate_Q;

    Evaluator(const int N, const int M)
        : N(N), M(M), C((N - 1) / 2), score_rate_P(BASE_SCORE * 6), score_rate_Q(((N* N + 5)* M)) {};

    inline uint32_t weight(const int x, int y) const {
        return (x - C) * (x - C) + (y - C) * (y - C) + 1;
    }

    Score evaluate(Board& board) const {
        auto dots = &board.grid.buffer;
        int weight_sum = accumulate(dots->cbegin(), dots->cend(), 0,
            [this](int acc, const Point& e) { return acc + this->weight(e.x, e.y); }
        );
        return weight_sum;
    }

    int calc_score(Board& board) const {
        return round(score_rate_P * this->evaluate(board) / score_rate_Q);
    }
};

struct State {
    Score score;
    Hash hash;
    Board board;

    State(const Score score, const Hash hash, const Board& board) : score(score), hash(hash), board(board) {}

    int _debug() const {
        return score;
    }
};

struct Modifier {
    const Converter converter;
    const Evaluator evaluator;

    Modifier(const int N, const int M) : converter(N), evaluator(N, M) {}

    inline Hash calc_modified_hash(const Hash hash, const Rectangle& rectangle) const {
        Hash res_hash = hash;
        res_hash ^= Line{rectangle.x0, rectangle.y0, rectangle.x1, rectangle.y1}.hash();
        res_hash ^= Line{rectangle.x1, rectangle.y1, rectangle.x2, rectangle.y2}.hash();
        res_hash ^= Line{rectangle.x2, rectangle.y2, rectangle.x3, rectangle.y3}.hash();
        res_hash ^= Line{rectangle.x3, rectangle.y3, rectangle.x0, rectangle.y0}.hash();
        return res_hash;
    }

    pair<Score,Hash> calc_modified_state(const Score score, const Hash hash, const Rectangle rectangle) const {
        Score res_score = score + evaluator.weight(rectangle.x0, rectangle.y0);
        return { res_score, this->calc_modified_hash(hash, rectangle) };
    }

    void apply(State *state, const Rectangle &rectangle) const {
        state->score += evaluator.weight(rectangle.x0, rectangle.y0);
        state->hash = this->calc_modified_hash(state->hash, rectangle);
        state->board.draw(rectangle);
    }

    void restore(State *state, const Rectangle &rectangle) const {
        state->score -= evaluator.weight(rectangle.x0, rectangle.y0);
        state->hash = this->calc_modified_hash(state->hash, rectangle);
        state->board.grid.drop(rectangle.x0, rectangle.y0);
        state->board.lines.pop(4);
    }
};


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M; cin >> N >> M;

    Grid grid(N);
    for (int i = 0; i < M; ++i) {
        int x, y; cin >> x >> y; grid.put(x, y);
    }

    Board board0(grid), board1(grid);

    vector<Rectangle> found;

    {
        board0.find_can_put(15, 18, &found);
        board0.draw(found[0]);
        found.clear();

        board0.find_can_put(12, 14, &found);
        board0.draw(found[0]);
        found.clear();
    }

    {
        board1.find_can_put(12, 14, &found);
        board1.draw(found[0]);
        found.clear();

        board1.find_can_put(15, 18, &found);
        board1.draw(found[0]);
        found.clear();
    }

    debug(board0.lines.buffer, board1.lines.buffer);
    debug(set(board0.lines.buffer.begin(), board0.lines.buffer.end()), set(board1.lines.buffer.begin(), board1.lines.buffer.end()));
    debug(board0.lines.hash(), board1.lines.hash());


    debug(board0.lines.buffer == board1.lines.buffer);
    debug(set(board0.lines.buffer.begin(), board0.lines.buffer.end()) == set(board1.lines.buffer.begin(), board1.lines.buffer.end()));
    debug(board0.lines.hash() == board1.lines.hash());

    return 0;
}
