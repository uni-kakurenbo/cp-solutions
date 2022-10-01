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
    #define DEBUG(...) do { Debug::DEBUG(nullptr, "\033[3;35m#" + to_string(__LINE__) + "\033[m  "); Debug::DEBUG(__VA_ARGS__); Debug::DEBUG(nullptr, "\033[m\n"); } while(0);
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
#include <array>
#include <vector>
#include <deque>
#include <utility>
#include <tuple>
#include <set>
#include <algorithm>
#include <random>

using namespace std;

#define INF32 2147483647

constexpr int MAX_N = 61;
constexpr int MIN_N = 31;

constexpr int DX[8] = { 1, 1, 1, 0, -1, -1, -1, 0  };
constexpr int DY[8] = { 1, 0, -1, -1, -1, 0, 1, 1  };

struct RandomEngine {
    static constexpr double MAX = mt19937::max();
    // static constexpr double MAX = UINT32_MAX;

    RandomEngine(uint32_t seed = 3141592653UL) : x(seed) {
        engine.seed(seed);
    };

    uint32_t generate() {
        // x ^= x << 13; x ^= x >> 17; x ^= x << 15;
        // return x;
        return engine();
    }

    uint32_t range(uint32_t max) {
        if(max == 0) return 0;
        return this->generate() % max;
    }

    uint32_t range(uint32_t min, uint32_t max) {
        dev_assert(min <= max);
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
        return pair{x, y} < pair{other.x, other.y};
    }
    inline bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    pair<int,int> _debug() const {
        return { x, y };
    }
};

struct Line {
    int x0, y0, x1, y1;

    Line(const int x0, const int y0, const int x1, const int y1)
        : x0(x0), y0(y0), x1(x1), y1(y1) {}

    inline tuple<int,int,int,int> to_tuple() const {
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
            (min(x0,x1) <= px && px <= max(x0,x1)) &&
            (min(y0,y1) <= py && py <= max(y0,y1)) &&
            (this->y0 - this->y1) * (px - this->x0) == (this->x0 - this->x1) * (py - this->y0)
        );
    }

    bool overlapping(const Line &other) const {
        if((this->y1 - this->y0) * (other.x1 - other.x0) != (other.y1 - other.y0) * (this->x1 - this->x0)) {
            return false;
        }

        if(
            !this->lying_on(other.x0, other.y0) && !this->lying_on(other.x1, other.y1) &&
            !other.lying_on(this->x0, this->y0) && !other.lying_on(this->x1, this->y1)
        ) {
            return false;
        }

        if(
            (this->lying_on(other.x0, other.y0) && this->lying_on(other.x1, other.y1)) ||
            (other.lying_on(this->x0, this->y0) && other.lying_on(this->x1, this->y1))
        ) {
            return true;
        }

        if(
            (this->x0 == other.x0 && this->y0 == other.y0) || (this->x0 == other.x1 && this->y0 == other.y1) ||
            (this->x1 == other.x0 && this->y1 == other.y0) || (this->x1 == other.x1 && this->y1 == other.y1)
        ) {
            return false;
        }

        return true;
    }

    pair<Point,Point> _debug() const {
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

    inline void add(Line &line) {
        this->buffer.push_back(line);
    }
    inline void emplace(const int x0, const int y0, const int x1, const int y1) {
        this->buffer.emplace_back(x0, y0, x1, y1);
    }

    inline void pop(const int times) {
        for(int i=0; i<times; ++i) this->buffer.pop_back();
    }

    inline int size() const {
        return this->buffer.size();
    }

    auto _debug() {
        return this->buffer;
    }
};

struct Rectangle {
  public:
    int x0, y0, x1, y1, x2, y2, x3, y3;

    Rectangle(const int x0, const int y0, const int x1, const int y1, const int x2, const int y2, const int x3, const int y3)
        : x0(x0), y0(y0), x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3) {}

    tuple<Point,Point,Point,Point> _debug() const {
        return { { x0, y0 }, { x1, y1 }, { x2, y2 }, { x3, y3 } };
    }

    inline tuple<int,int,int,int,int,int,int,int> to_tuple() const {
        return make_tuple(x0, y0, x1, y1, x2, y2, x3, y3);
    }
    inline bool operator<(const Rectangle& other) const {
        return this->to_tuple() < other.to_tuple();
    }
};

using History = vector<Rectangle>;

template<> struct std::hash<Point> {
    size_t operator()(Point key) const {
        return key.x * MAX_N + key.y;
    }
};

struct Grid {
  private:
    int N;

  public:
    unordered_set<Point> buffer;

    Grid(const int N) : N(N) {};

    inline bool is_valid(const int x, const int y) const {
        return 0 <= x && x < N && 0 <= y && y < N;
    }

    inline bool get(const int x, const int y) const {
        dev_assert(this->is_valid(x, y));
        return this->buffer.count({x, y});
    }
    inline void put(const int x, const int y) {
        dev_assert(!this->get(x, y));
        this->buffer.emplace(x, y);
        return;
    }
    inline void drop(const int x, const int y) {
        dev_assert(this->get(x, y));
        this->buffer.erase({x, y});
        return;
    }

    string view() const {
        string res = "\n";
        for(int j=N-1; j>=0; --j) {
            for(int i=0; i<N; ++i) {
                res += this->get(i, j) ? '#' : '.';
            }
            res += "\n";
        }
        return res;
    }
};

struct Board {
  private:
    int N;

  public:
    Grid grid;
    LineCollector lines;
    History history;

    Board(const int N) : N(N), grid(N) {}

    inline void draw(const Rectangle &rectangle) {
        history.push_back(rectangle);
        grid.put(rectangle.x0, rectangle.y0);
        lines.emplace(rectangle.x0, rectangle.y0, rectangle.x1, rectangle.y1);
        lines.emplace(rectangle.x1, rectangle.y1, rectangle.x2, rectangle.y2);
        lines.emplace(rectangle.x2, rectangle.y2, rectangle.x3, rectangle.y3);
        lines.emplace(rectangle.x3, rectangle.y3, rectangle.x0, rectangle.y0);
    }

    bool find_can_put(const int px, const int py, vector<Rectangle> *found) const {
        dev_assert(this->grid.get(px, py));

        for(int d=0; d<8; ++d) {
            const int dx0 = DX[d], dy0 = DY[d];
            const int dx1 = DX[(d+2) % 8], dy1 = DY[(d+2) % 8];

            int x00, y00, x01, y01;
            x00 = x01 = px, y00 = y01 = py;

            do { x00 += dx0, y00 += dy0; } while(this->grid.is_valid(x00, y00) && !this->grid.get(x00, y00));
            do { x01 += dx1, y01 += dy1; } while(this->grid.is_valid(x01, y01) && !this->grid.get(x01, y01));

            if(!this->grid.is_valid(x00, y00) || !this->grid.is_valid(x01, y01)) continue;

            if(this->lines.overlapping_any(Line{px, py, x00, y00})) continue;
            if(this->lines.overlapping_any(Line{px, py, x01, y01})) continue;

            const int ex0 = x00 - px, ey0 = y00 - py;
            const int ex1 = x01 - px, ey1 = y01 - py;

            const int gx0 = x00 + ex1, gy0 = y00 + ey1;
            const int gx1 = x01 + ex0, gy1 = y01 + ey0;

            if(gx0 != gx1 || gy0 != gy1) continue;
            if(!this->grid.is_valid(gx0, gy0)) continue;
            if(this->grid.get(gx0, gy0)) continue;

            if(this->lines.overlapping_any(Line{x00, y00, gx0, gy0})) continue;
            if(this->lines.overlapping_any(Line{x01, y01, gx0, gy0})) continue;

            // debug(d, dx0, dy0, dx1,dy1);
            // debug(x00, y00, x01, y01);
            // debug(ex0, ey0, ex1, ey1);
            // debug(gx0, gy0, gx1, gy1);

            int x10 = x00, y10 = y00;
            int x11 = x01, y11 = y01;

            do { x10 += dx1, y10 += dy1; } while(!(x10 == gx0 && y10 == gy0) && !this->grid.get(x10, y10));
            do { x11 += dx0, y11 += dy0; } while(!(x11 == gx0 && y11 == gy0) && !this->grid.get(x11, y11));

            if(x10 != gx0 || y10 != gy0 || x11 != gx0 || y11 != gy0) continue;

            found->emplace_back(gx0, gy0, x00, y00, px, py, x01, y01);
        }
        return found->size() > 0;
    }

    void find_all_can_put(vector<Rectangle> *found) {
        for(auto [x, y] : this->grid.buffer) {
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
        : N(N), M(M), C((N-1)/2), score_rate_P(BASE_SCORE * 6), score_rate_Q(((N*N + 5) * M)) {};

    inline uint32_t weight(const int x, int y) {
        return (x - C) * (x - C) + (y - C) * (y - C) + 1;
    }

    Score evaluate(Board &board) {
        auto dots = &board.grid.buffer;
        int weight_sum = accumulate(dots->cbegin(), dots->cend(), 0,
            [this](int acc, const Point &e) { return acc + this->weight(e.x, e.y); }
        );
        int penalty = 0;
        penalty += board.history.size();
        return weight_sum;
    }

    int calc_score(Board &board) {
        return round(score_rate_P * this->evaluate(board) / score_rate_Q);
    }
};

struct State {
    Score score;
    Board board;
    State(const int score, const Board& board) : score(score), board(board) {}

    inline bool operator<(const State &other) const {
        return this->score < other.score;
    }

    int _debug() const {
        return score;
    }
};

struct Modifyer {
    int N;
    RandomEngine *random_engine;
    Evaluator *evaluator;
    State *initial_state;

    Modifyer(int N, RandomEngine *random_engine, Evaluator *evaluator, State *initial_state)
        : N(N), random_engine(random_engine), evaluator(evaluator), initial_state(initial_state) {}

    int modify(State *state) {
        int type = random_engine->range(3);

        if(type == 0 && state->board.history.size() > 3) {
            int times = random_engine->range(1, 3);
            for(int i=0; i<times; ++i) {
                Rectangle &last_drawn = state->board.history.back();
                state->board.grid.drop(last_drawn.x0, last_drawn.y0);
                state->score -= evaluator->weight(last_drawn.x0, last_drawn.y0);
                state->board.history.pop_back();
                state->board.lines.pop(4);
                // state->score += 1;
            }
        }

        if(type == 1) {
            vector<Rectangle> found;
            state->board.find_all_can_put(&found);

            if(found.empty()) return 1;

            sort(found.rbegin(), found.rend(), [this](Rectangle &a, Rectangle &b) {
                return this->evaluator->weight(a.x0, a.y0) < this->evaluator->weight(b.x0, b.y0);
            });
            Rectangle rectangle = found[random_engine->range(found.size())];
            state->board.draw(rectangle);
            state->score += evaluator->weight(rectangle.x0, rectangle.y0);
            // state->score -= 1;
        }

        if(type == 2 && state->board.history.size() > 3) {
            int times = random_engine->range(1, 3);
            for(int i=0; i<times; ++i) {
                Rectangle &last_drawn = state->board.history.back();
                state->board.grid.drop(last_drawn.x0, last_drawn.y0);
                state->score -= evaluator->weight(last_drawn.x0, last_drawn.y0);
                state->board.history.pop_back();
                state->board.lines.pop(4);
                // state->score += 1;
            }

            vector<Rectangle> found0;
            state->board.find_all_can_put(&found0);
            if(found0.empty()) return 1;

            sort(found0.rbegin(), found0.rend(), [this](Rectangle &a, Rectangle &b) {
                return this->evaluator->weight(a.x0, a.y0) < this->evaluator->weight(b.x0, b.y0);
            });

            for(int i=0; i<times; ++i) {
                const Rectangle &p = found0[random_engine->range(min((int)found0.size(), 10))];

                vector<Rectangle> found1;
                state->board.find_can_put(p.x2, p.y2, &found1);

                if(found1.empty()) continue;

                Rectangle &rectangle = found1[random_engine->range(found1.size())];

                state->board.draw(rectangle);
                state->score += evaluator->weight(rectangle.x0, rectangle.y0);
                // state->score -= 1;
            }
        }

        return 0;
    }
};

void print_answer(ostream *out, const State &state) {
    (*out) << state.board.history.size() << "\n";
    for(const Rectangle &rectangle : state.board.history) {
        (*out) << rectangle.x0 << " " << rectangle.y0 << " ";
        (*out) << rectangle.x1 << " " << rectangle.y1 << " ";
        (*out) << rectangle.x2 << " " << rectangle.y2 << " ";
        (*out) << rectangle.x3 << " " << rectangle.y3 << "\n";
    }
}
void print_answer(ostream *out, ostream *log, const State &state) {
    print_answer(out, state);
    (*log) << state.score << "\n";
}

constexpr int TIME_LIMIT_MS = 4900;
constexpr int TIME_LIMIT = TIME_LIMIT_MS * CLOCKS_PER_SEC / 1000;

constexpr double MT_MAX = mt19937::max();

signed main() {
    int N, M; cin >> N >> M;

    RandomEngine random_engine;
    Evaluator evaluator(N, M);

    Board initial_board(N);
    for(int i=0; i<M; ++i) {
        int x, y; cin >> x >> y;
        initial_board.grid.put(x, y);
    }

    Score initial_score = 0; //evaluator.evaluate(initial_board);
    debug(initial_score);

    double start_temperature, end_temperature, temperature_rate;

    {
        constexpr double S0 = 700, S1 = 200;
        constexpr double E0 = 30, E1 = 10;

        const double D = log((double)MAX_N / MIN_N);
        const double R = (double)MAX_N / N;

        const double KS = log(S0 / S1) / D;
        const double KE = log(E0 / E1) / D;

        start_temperature = pow(R, KS) * S1;
        end_temperature = pow(R, KE) * E1;
        temperature_rate = end_temperature / start_temperature;
        // cin >> start_temperature >> end_temperature;
    }

    debug(start_temperature, end_temperature);

    State initial_state(initial_score, initial_board);
    State answer = initial_state;

    Modifyer mdifyer(N, &random_engine, &evaluator, &initial_state);

    const int T = 3;

    constexpr double TIME_LIMIT = TIME_LIMIT_MS * CLOCKS_PER_SEC / 1000;
    constexpr double I_TIME_LIMIT = TIME_LIMIT / T;

    for(int t=0; t<T; ++t) {
        clock_t start = clock();
        int loops = 0;
        State state = initial_state;

        while((clock() - start) < I_TIME_LIMIT) { // SA
            double time_rate = (clock() - start) / I_TIME_LIMIT;

            State previous_state = state;

            if(mdifyer.modify(&state)) continue;

            Score diff = state.score - previous_state.score;

            if(diff >= 0) {
                // debug(state);
                answer = max(answer, state);
            } else {
                double temperature = start_temperature * pow(temperature_rate, time_rate);
                double probability = exp(diff / temperature);
                // debug(temperature, probability);
                if (probability * RandomEngine::MAX > random_engine.generate()) {
                    // debug(state);
                    // debug(temperature, state);
                    answer = max(answer, state);
                } else {
                    state = previous_state;
                }
            }
            ++loops;
        }

        { // Filling
            vector<Rectangle> found0;
            answer.board.find_all_can_put(&found0);

            sort(found0.rbegin(), found0.rend(), [&evaluator](Rectangle &a, Rectangle &b) {
                return evaluator.weight(a.x0, a.y0) < evaluator.weight(b.x0, b.y0);
            });

            for(Rectangle &p : found0) {
                vector<Rectangle> found1;
                answer.board.find_can_put(p.x2, p.y2, &found1);

                if(found1.empty()) continue;

                Rectangle &rectangle = found1[random_engine.range(found1.size())];

                answer.board.draw(rectangle);
            }
        }

        debug(loops, answer);
    }

    answer.score = evaluator.calc_score(answer.board);

    print_answer(&cout, &clog, answer);

    return 0;
}
