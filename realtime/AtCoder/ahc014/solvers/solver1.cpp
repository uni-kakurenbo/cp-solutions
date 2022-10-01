/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */

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

#ifdef LOCAL_JUDGE
    #include <fstream>
#endif

#include <iostream>
#include <bitset>
#include <array>
#include <vector>
#include <utility>
#include <tuple>
#include <set>
#include <algorithm>

using namespace std;

#define INF32 2147483647

constexpr int MAX_N = 61;

constexpr int DX[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
constexpr int DY[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

using Point = pair<int,int>;

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
    vector<Line> buffer;

  public:
    inline bool overlapping_any(const Line &target) const {
        static set<Line> determined;

        if (determined.count(target)) return true;

        bool res = any_of(buffer.cbegin(), buffer.cend(),
            [&target](const Line &line) { return target.overlapping(line); }
        );

        if(res) determined.insert(target);

        return res;
    }

    inline void add(Line &line) {
        this->buffer.push_back(line);
    }
    inline void emplace(const int x0, const int y0, const int x1, const int y1) {
        this->buffer.emplace_back(x0, y0, x1, y1);
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
};

using History = vector<Rectangle>;

struct Converter {
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
  private:
    int N = 0;
};

struct Grid {
  private:
    int N;
    const Converter *converter;
    bitset<MAX_N*MAX_N> data;

  public:
    Grid(const int N, const Converter &converter) : N(N), converter(&converter) {};

    inline bool is_valid(const int id) const {
        return 0 <= id && id < N*N;
    }
    inline bool is_valid(const int x, const int y) const {
        return 0 <= x && x < N && 0 <= y && y < N;
    }

    inline bool get(const int id) const {
        dev_assert(is_valid(id));
        return data.test(id);
    }
    inline void put(const int id) {
        dev_assert(!this->get(id));
        data.set(id);
        return;
    }

    inline bool get(const int x, const int y) const {
        return this->get(converter->pair_to_id(x,y));
    }
    inline void put(const int x, const int y) {
        this->put(converter->pair_to_id(x,y));
        return;
    }

    string view() const {
        string res = "\n";
        for (int j=N-1; j>=0; --j) {
            for (int i=0; i<N; ++i) {
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

    Board(const int N, const Converter &converter) : N(N), grid(N, converter) {}

    inline void draw(const Rectangle &rectangle) {
        history.push_back(rectangle);
        grid.put(rectangle.x0, rectangle.y0);
        lines.emplace(rectangle.x0, rectangle.y0, rectangle.x1, rectangle.y1);
        lines.emplace(rectangle.x1, rectangle.y1, rectangle.x2, rectangle.y2);
        lines.emplace(rectangle.x2, rectangle.y2, rectangle.x3, rectangle.y3);
        lines.emplace(rectangle.x3, rectangle.y3, rectangle.x0, rectangle.y0);
    }

    bool find_rectangles(const int px, const int py, vector<Rectangle> *found) const {
        if (grid.get(px, py)) return false;
        set<Point> already;

        for (int d=0; d<8; ++d) {
            const int dx0 = DX[d], dy0 = DY[d];
            int tx0 = px, ty0 = py;

            do { tx0 += dx0, ty0 += dy0; } while(grid.is_valid(tx0, ty0) && !grid.get(tx0, ty0));
            if (!grid.is_valid(tx0, ty0) || already.count({tx0, ty0})) continue;
            if (this->lines.overlapping_any(Line(px, py, tx0, ty0))) continue;

            int dx10 = 0, dy10 = 0, dx11 = 0, dy11 = 0;
            if (dx0 == 0) dy10 = dy11 = 0, dx10 = 1, dx11 = -1;
            else if (dy0 == 0) dx10 = dx11 = 0, dy10 = 1, dy11 = -1;
            else dx10 = -dx0, dy10 = dy0, dx11 = dx0, dy11 = -dy0;

            int tx10 = tx0, ty10 = ty0;
            do { tx10 += dx10, ty10 += dy10; } while(grid.is_valid(tx10, ty10) && !grid.get(tx10, ty10));

            int tx11 = tx0, ty11 = ty0;
            do { tx11 += dx11, ty11 += dy11; } while(grid.is_valid(tx11, ty11) && !grid.get(tx11, ty11));


            const int dx2 = -dx0, dy2 = -dy0;

            const int dx30 = -dx10, dy30 = -dy10;
            const int dx31 = -dx11, dy31 = -dy11;

            const int ex0 = px - tx0, ey0 = py - ty0;
            const int gx0 = ex0 + tx10, gy0 = ey0 + ty10;
            const int gx1 = ex0 + tx11, gy1 = ey0 + ty11;

            // debug(tx0, ty0, tx10, ty10, tx11, ty11, gx0, gy0, gx1, gy1);
            // debug(grid.get(gx0, gy0), grid.get(gx1, gy1));

            if (
                !this->lines.overlapping_any(Line(tx0, ty0, tx10, ty10)) &&
                !this->lines.overlapping_any(Line(tx10, ty10, gx0, gy0)) &&
                !this->lines.overlapping_any(Line(gx0, gy0, px, py)) &&
                grid.is_valid(tx10, ty10) && grid.is_valid(gx0, gy0) && grid.get(gx0, gy0)
            ) {
                int tx2 = tx10, ty2 = ty10;
                do { tx2 += dx2, ty2 += dy2; } while((tx2 != gx0 || ty2 != gy0) && !grid.get(tx2, ty2));
                if (tx2 == gx0 && ty2 == gy0) {
                    int tx3 = tx2, ty3 = ty2;
                    do { tx3 += dx30, ty3 += dy30; } while((tx3 != px || ty3 != py) && !grid.get(tx3, ty3));
                    if (tx3 == px && ty3 == py ) {
                        already.emplace(tx2, ty2);
                        found->emplace_back(px, py, tx0, ty0, tx10, ty10, tx2, ty2);
                    }
                }
            }

            if (
                !this->lines.overlapping_any(Line(tx0, ty0, tx11, ty11)) &&
                !this->lines.overlapping_any(Line(tx11, ty11, gx1, gy1)) &&
                !this->lines.overlapping_any(Line(gx1, gy1, px, py)) &&
                grid.is_valid(tx11, ty11) && grid.is_valid(gx1, gy1) && grid.get(gx1, gy1)
            ) {
                int tx2 = tx11, ty2 = ty11;
                do { tx2 += dx2, ty2 += dy2; } while((tx2 != gx1 || ty2 != gy1) && !grid.get(tx2, ty2));
                if (tx2 == gx1 && ty2 == gy1) {
                    int tx3 = tx2, ty3 = ty2;
                    do { tx3 += dx31, ty3 += dy31; } while((tx3 != px || ty3 != py) && !grid.get(tx3, ty3));
                    if (tx3 == px && ty3 == py ) {
                        already.emplace(tx2, ty2);
                        found->emplace_back(px, py, tx0, ty0, tx11, ty11, tx2, ty2);
                    }
                }
            }
        }

        return found->size() > 0;
    }
};

void print_answer(ostream *out, const Board board) {
    (*out) << board.history.size() << "\n";
    for(const Rectangle &rectangle : board.history) {
        (*out) << rectangle.x0 << " " << rectangle.y0 << " ";
        (*out) << rectangle.x1 << " " << rectangle.y1 << " ";
        (*out) << rectangle.x2 << " " << rectangle.y2 << " ";
        (*out) << rectangle.x3 << " " << rectangle.y3 << "\n";
    }
}

constexpr int TIME_LIMIT_MS = 4900;

signed main() {
    clock_t start = clock();

    int N, M; cin >> N >> M;

    Converter converter(N);

    Board initial_board(N, converter);
    for (int i=0; i<M; ++i) {
        int x, y; cin >> x >> y;
        initial_board.grid.put(x, y);
    }

    debug(initial_board.grid.view());

    Board board = initial_board;

    constexpr int TIME_LIMIT = TIME_LIMIT_MS * CLOCKS_PER_SEC / 1000;
    while((clock() - start) < TIME_LIMIT) {
        bool flag = true;
        for (int x=0; x<N; ++x) {
            for (int y=0; y<N; ++y) {
                vector<Rectangle> found;
                if(!board.find_rectangles(x, y, &found)) continue;
                flag = false;
                // debug(found);
                board.draw(found[0]);
                // debug(board.lines);
            }
        }
        if(flag) break;
    }

    print_answer(&cout, board);

    return 0;
}
