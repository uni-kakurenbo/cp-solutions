/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

#include "template/standard.hpp"

#pragma GCC diagnostic warning "-Wshadow=local"

constexpr int N = 5;

enum class OPERATION : char {
    PICK = 'P',
    DROP = 'Q',

    MOVE_UP = 'U',
    MOVE_DOWN = 'D',
    MOVE_LEFT = 'L',
    MOVE_RIGHT = 'R',

    PAUSE = '.',
    DESTROY = 'B',
};

inline auto to_id(const i32 i, const i32 j) { return i * N + j; }
inline auto to_row(const i32 id) { return id / N; }
inline auto to_col(const i32 id) { return id % N; }
inline auto to_pos(const i32 id) { return std::make_pair(to_row(id), to_col(id)); }

inline auto dist(const i32 p0, const i32 p1) {
    return std::abs(to_row(p0) - to_row(p1)) + std::abs(to_col(p0) - to_col(p1));
}

inline auto to_goal(const i32 id) { return to_id(id / N, N - 1); }

struct crane_type {
    std::vector<OPERATION> history;
    i32 pos = -1;
    i32 fold = -1;

    crane_type() = default;
    crane_type(const i32 id) : pos(to_id(id, 0)) {}

    void move_left() {
        history.push_back(OPERATION::MOVE_LEFT);
        --pos;
    }

    void move_right() {
        history.push_back(OPERATION::MOVE_RIGHT);
        ++pos;
    }

    void move_up() {
        history.push_back(OPERATION::MOVE_UP);
        pos -= N;
    }

    void move_down() {
        history.push_back(OPERATION::MOVE_DOWN);
        pos += N;
    }


    void pick(const i32 id) {
        assert(fold < 0);
        history.push_back(OPERATION::PICK);
        fold = id;
    }

    auto drop() {
        assert(fold >= 0);
        history.push_back(OPERATION::DROP);
        const auto res = fold;
        fold = -1;
        return res;
    }


    inline void destroy() {
        history.push_back(OPERATION::DESTROY);
    }
};


struct buffer_provider {
    std::unordered_set<i32> buffer;

    buffer_provider() = default;

    auto empty() { return buffer.empty(); }

    void push(const i32 pos) {
        buffer.insert(pos);
    }

    void pop(const i32 pos) {
        buffer.erase(pos);
    }

    auto get_middle(const i32 from, const i32 to) {
        i32 min = INF32, res = -1;
        ITR(pos, buffer) {
            if(chmin(min, dist(from, pos) + dist(pos, to))) {
                res = pos;
            };
        }
        assert(res >= 0);
        return res;
    }
};

struct board_type {
    std::array<std::deque<i32>, N> queue;
    std::array<i32, N * N> data, pos;
    std::array<crane_type, N> cranes;

    void update() {
        REP(i, N) {
            if(data[to_id(i, 0)] < 0 && !queue[i].empty()) {
                place(to_id(i, 0), queue[i].front());
                queue[i].pop_front();
            }
            if(data[to_id(i, N - 1)] >= 0) {
                this->place(-INF32, data[to_id(i, N - 1)]);
                this->place(to_id(i, N - 1), -1);
            }
        }
    }

    template<class T>
    board_type(const T& in) {
        REP(i, N) {
            cranes[i] = crane_type(i);
            ITR(v, in[i]) {
                queue[i].push_back(v);
                pos[v] = -(i + 1);
            }
        }
        data.fill(-1);
        update();
    }

    void place(const i32 pos, const i32 id) {
        if(pos >= 0) data[pos] = id;
        if(id >= 0) this->pos[id] = pos;
    }

    void pick(const i32 crane) {
        assert(data[cranes[crane].pos] >= 0);
        cranes[crane].pick(data[cranes[crane].pos]);
        place(cranes[crane].pos, -1);
    }

    auto drop(const i32 crane) {
        assert(data[cranes[crane].pos] < 0);
        return place(cranes[crane].pos, cranes[crane].drop());
    }

    void move(const i32 crane, const i32 to) {
        while(to_row(cranes[crane].pos) < to_row(to)) cranes[crane].move_down();
        while(to_row(cranes[crane].pos) > to_row(to)) cranes[crane].move_up();
        while(to_col(cranes[crane].pos) < to_col(to)) cranes[crane].move_right();
        while(to_col(cranes[crane].pos) > to_col(to)) cranes[crane].move_left();
    }

    void carry(const i32 crane, const i32 from, const i32 to) {
        assert(data[from] >= 0);
        assert(data[to] < 0);
        debug_("carry"); debug(to_pos(from), to_pos(to));
        move(crane, from);
        pick(crane);
        move(crane, to);
        drop(crane);
        update();
    }


    void output() {
        ITR(s, cranes) {
            ITR(v, s.history) print << static_cast<char>(v);
            print();
        }
    }
};

signed main() {
    { i32 _; input >> _; }
    uni::grid<i32> A(N, N); input >> A;

    board_type board(A);

    REP(i, 1, N) board.cranes[i].destroy();

    buffer_provider buffer;

    REP(i, N) {
        REP(j, 1, N - 1) buffer.push(to_id(i, j));
    }

    REP(target, N) {
        REP(next, N * target, N * (target + 1)) {
            debug(next, board.queue, board.data);
            debug(board.pos[next]);

            while(board.pos[next] < 0) {
                debug_("buffer");
                const auto from = to_id(-(board.pos[next] + 1), 0);
                const auto to = to_goal(board.data[from]);

                const auto buf = buffer.get_middle(from, to);

                board.carry(0, from, buf);
                buffer.pop(buf);
            }

            if(1 <= to_col(board.pos[next]) && to_col(board.pos[next]) < N - 1) {
                buffer.push(board.pos[next]);
            }

            debug_("export");
            board.carry(0, board.pos[next], to_id(target, N - 1));
        }
    }

    board.output();
}
