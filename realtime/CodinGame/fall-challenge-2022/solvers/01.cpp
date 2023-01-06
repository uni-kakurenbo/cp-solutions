/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
 /* #language C++ GCC */

#include <cassert>

#include <iostream>

#include <string>

#include <array>
#include <vector>
#include <queue>

#include <set>

#include <algorithm>
#include <limits>

using Amount = std::int16_t;
using Pos = std::int16_t;

struct Uncopyable {
    Uncopyable(){}
    Uncopyable(const Uncopyable&) = delete;
    Uncopyable& operator=(const Uncopyable&) = delete;
};

struct Point {
    Pos row, col;

    constexpr Point() : Point(-1, -1) {}
    constexpr Point(const Pos row, const Pos col) : row(row), col(col) {}

    inline bool operator==(const Point &other) const {
        return this->row == other.row and this->col == other.col;
    }
    inline bool operator!=(const Point &other) const {
        return not (*this == other);
    }

    inline bool operator<(const Point &other) const {
        return this->row == other.row ? this->col < other.col : this->row < other.row;
    }

    inline Point& operator+=(const Point &other) {
        this->row += other.row, this->col += other.col;
        return *this;
    }
    inline Point operator+(const Point &other) {
        Point res = *this;
        return res += other;
    }

    inline Pos dist(const Point &other) const {
        return std::max(std::abs(this->row - other.row), std::abs(this->col - other.col));
    }

    inline std::pair<Pos, Pos> _debug() const {
        return { this->row, this->col };
    }
};

struct Printer : private Uncopyable {
  private:
    std::ostream *_out;

    template<class Head, class... Tails>
    inline void _put(Head&& head, Tails&&... tails) {
        *this->_out << head << " ";
        this->_put(std::forward<Tails>(tails)...);
    }

    inline void _put() { *this->_out << ";"; }

  public:
    Printer(std::ostream *out) { this->set_sink(out); }

    inline void set_sink(std::ostream *out) { this->_out = out; }

    inline void new_line() { *this->_out << std::endl; }

    inline void move(const Amount amount, const Point &from, const Point &to) {
        this->_put("MOVE", amount, from.col, from.row, to.col, to.row);
    }

    inline void build(const Point point) {
        this->_put("BUILD", point.col, point.row);
    }

    inline void spawn(const Amount amount, const Point &point) {
        this->_put("SPAWN", amount, point.col, point.row);
    }

    inline void wait() { this->_put("WAIT"); }

    inline void message(const std::string& message) { this->_put("MESSAGE", message); }
};

constexpr Point DIRS4[] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

enum class Player : std::int8_t { Self, Opponent, None };

template<class T>
struct Grid : std::vector<std::vector<T>> {
    constexpr Grid(const size_t h = 0, const size_t w = 0, const T &&v = T{}) : std::vector<std::vector<T>>(h, std::vector<T>(w, v)) {}
};

struct Board : private Uncopyable {
    struct Tile {
        Amount scraps;
        Player owner;
        Amount units;
        bool recycler;

        bool can_build, can_spaen, recyclable;

        inline void read(std::istream *const in) {
            {
                std::int16_t owner;
                *in >> this->scraps >> owner >> this->units >> this->recycler;
                this->owner = owner == 1 ? Player::Self : (owner == 0 ? Player::Opponent : Player::None);
            }
            *in >> this->can_build >> this->can_spaen >> this->recyclable;
        }
    };

  private:
    Pos _height, _width;
    Grid<Tile> _tiles;

  public:
    Board() {}
    Board(const Pos height, const Pos width) : _height(height), _width(width), _tiles(height, width) {}

    inline void read(std::istream *const in) {
        for(Pos i=0; i<this->_height; ++i) {
            for(Pos j=0; j<this->_width; ++j) {
                _tiles[i][j].read(in);
            }
        }
    }

    inline Tile get(const Point &point) const {
        return this->_tiles[point.row][point.col];
    }

    inline Pos to_index(const Point &point) const {
        return point.row * this->_width + point.col;
    }

    inline Pos valid(const Point &point) const {
        return 0 <= point.row and 0 <= point.col and point.row < this->_height and point.col < this->_width;
    }

    template<class Query>
    inline std::multiset<Point> find(const Query query) const {
        std::multiset<Point> res;
        for(Pos i=0; i<this->_height; ++i) {
            for(Pos j=0; j<this->_width; ++j) {
                if(query(this->_tiles[i][j])) res.emplace(i, j);
            }
        }
        return res;
    }

    inline std::multiset<Point> find_units(const Player target = Player::Self) const {
        std::multiset<Point> res;
        for(Pos i=0; i<this->_height; ++i) {
            for(Pos j=0; j<this->_width; ++j) {
                if(this->_tiles[i][j].owner != target) continue;
                for(Amount cnt = this->_tiles[i][j].units; cnt > 0; --cnt) res.emplace(i, j);
            }
        }
        return res;
    }

    inline Grid<Pos> dists(const Point &start) const {
        std::queue<Point> que;
        Grid<Pos> dists(this->_height, this->_width, -1);

        que.push(start), dists[start.row][start.col] = 0;

        while(!que.empty()) {
            auto p = que.front(); que.pop();
            for(const Point &delta : DIRS4) {
                Point np = p + delta;
                if(not this->valid(np)) continue;
                if(this->get(np).scraps <= 0) continue;
                if(dists[np.row][np.col] >= 0) continue;
                dists[np.row][np.col]= dists[p.row][p.col] + 1;
                que.push(np);
            }
        }

        return dists;
    }
};

struct Game {
    Amount my_matter, opp_matter;
    Board board;

    Game(const Pos height, const Pos width) : board(height, width) {}

    inline void read(std::istream *const in) {
        *in >> this->my_matter >> this->opp_matter;
        this->board.read(in);
    }
};

Printer out(&std::cout);

signed main() {
    Pos height, width; std::cin >> width >> height;

    Game game(height, width);

    while(true) {
        game.read(&std::cin);

        Pos recyclers = 0;
        for(Pos i = 0; i < height; ++i) {
            for(Pos j = 0; j < width; ++j) {
                Board::Tile tile = game.board.get({ i, j });
                recyclers += tile.owner == Player::Self and tile.recycler;
            }
        }

        if(game.my_matter <= 20) recyclers = 0;

        std::clog << recyclers << std::endl;

        std::set<Point> color_queue;

        for(Pos i = 0; i < height; ++i) {
            for(Pos j = 0; j < width; ++j) {
                Point point = { i, j };
                Board::Tile tile = game.board.get(point);

                if(tile.owner == Player::Self) {
                    if(tile.can_build and recyclers == 0) {
                        out.build(point);
                        game.my_matter -= 10;
                        ++recyclers;
                    }

                    Pos border_count = 0;
                    Pos dead_count = 0;

                    for(const Point &delta : DIRS4) {
                        Point adj_point = point + delta;
                        if(not game.board.valid(adj_point)) continue;
                        Board::Tile adj_tile = game.board.get(adj_point);

                        if(adj_tile.owner != Player::Self) {
                            ++border_count;
                            color_queue.insert(adj_point);
                            std::clog << "(" << adj_point.col << "," << adj_point.row << ")" << std::endl;
                        }

                        dead_count += adj_tile.scraps == 0;
                    }

                    if(border_count and game.my_matter > 10) out.spawn(1, point), game.my_matter -= 10;
                }
            }
        }

        auto units = game.board.find_units();

        while(not color_queue.empty() and not units.empty()) {
            Point point = *color_queue.begin(); color_queue.erase(color_queue.begin());
            auto dists = game.board.dists(point);

            Pos min_dist = std::numeric_limits<Pos>::max();
            auto best_unit = std::begin(units);
            for(auto unit = std::begin(units); unit != std::end(units); ++unit) {
                if(dists[unit->row][unit->col] < 0) continue;
                if(dists[unit->row][unit->col] < min_dist) {
                    min_dist = dists[unit->row][unit->col];
                    best_unit = unit;
                }
            }
            out.move(1, *best_unit, point);
            units.erase(best_unit);
        }

        out.wait();
        out.new_line();
    }

    return EXIT_SUCCESS;
}
