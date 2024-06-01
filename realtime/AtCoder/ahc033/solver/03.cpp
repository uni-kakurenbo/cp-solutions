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

inline auto distance(const i32 p0, const i32 p1) {
    return std::abs(to_row(p0) - to_row(p1)) + std::abs(to_col(p0) - to_col(p1));
}

inline auto to_goal(const i32 id) { return to_id(id / N, N - 1); }

struct crane_type {
    std::vector<OPERATION> history;
    std::deque<OPERATION> schedule;

    i32 pos = -1;
    i32 fold = -1;

    crane_type() = default;
    crane_type(const i32 id) : pos(to_id(id, 0)) {}


    void pause() {
        history.push_back(OPERATION::PAUSE);
    }


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
        pos = -INF32;
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
            if(chmin(min, distance(from, pos) + distance(pos, to))) {
                res = pos;
            }
        }
        assert(res >= 0);
        return res;
    }
};

struct board_type {
    std::array<std::deque<i32>, N> queue;
    std::array<i32, N * N> data, pos;

    void update() {
        REP(i, N) {
            if(data[to_id(i, 0)] < 0 && !queue[i].empty()) {
                place(to_id(i, 0), queue[i].front());
                queue[i].pop_front();
            }
            if(data[to_id(i, N - 1)] >= 0) {
                place(-INF32, data[to_id(i, N - 1)]);
                place(to_id(i, N - 1), -1);
            }
        }
    }

    template<class T>
    board_type(const T& in) {
        REP(i, N) {
            ITR(v, in[i]) {
                pos[v] = -(i + 1);
                queue[i].push_back(v);
            }
        }
        data.fill(-1);
        update();
    }

    void place(const i32 pos, const i32 id) {
        if(pos >= 0) data[pos] = id;
        if(id >= 0) this->pos[id] = pos;
    }


    auto root(const i32 from, const i32 to) {
        std::queue<i32> que;
        vector<i32> prev(N * N, -2);

        que.push(from), prev[from] = -1;

        while(!que.empty()) {
            auto p = que.front(); que.pop();
            if(p == to) break;

            ITR(di, dj, DIRS4) {
                i32 ni = to_row(p) + di, nj = to_col(p) + dj;
                if(ni < 0 || nj < 0 || ni >= N || nj >= N) continue;

                i32 np = to_id(ni, nj);
                if(prev[np] >= -1) continue;

                prev[np] = p;
                que.push(np);
            }
        }

        auto pos = to;

        std::vector<i32> path;
        while(prev[pos] >= 0) {
            path.push_back(pos);
            pos = prev[pos];
        }
        std::ranges::reverse(path);

        return path;
    }
};

struct motion {
    i32 pos;
    OPERATION op;
};

struct scheduler {
    board_type board;
    std::array<crane_type, N> cranes;
    std::array<std::deque<motion>, N> schedule;
    std::unordered_set<i32> locked;


    template<class T>
    scheduler(const T& in) : board(in) {
        REP(i, N) {
            cranes[i] = crane_type(i);
        }
    }


    auto _move_left(const i32 crane) {
        if(0 < to_col(cranes[crane].pos)) {
            // REP(i, N) if(i != N && )
        }
        cranes[crane].move_left();
        return true;
    }

    auto _move_right(const i32 crane) {
        cranes[crane].move_right();
        return true;
    }

    auto _move_up(const i32 crane) {
        cranes[crane].move_up();
        return true;
    }

    auto _move_down(const i32 crane) {
        cranes[crane].move_down();
        return true;
    }


    auto _destroy(const i32 crane) {
        cranes[crane].destroy();
        return true;
    }


    auto _pick(const i32 crane) {
        if(board.data[cranes[crane].pos] < 0) return false;
        cranes[crane].pick(board.data[cranes[crane].pos]);
        board.place(cranes[crane].pos, -1);
        return true;
    }

    auto _drop(const i32 crane) {
        assert(board.data[cranes[crane].pos] < 0);
        const auto id = cranes[crane].drop();
        if(locked.contains(id)) locked.erase(id);
        board.place(cranes[crane].pos, id);
        return true;
    }


    auto last_pos(const i32 crane) {
        if(schedule[crane].empty()) return cranes[crane].pos;
        return schedule[crane].back().pos;
    }

    auto next_pos(const i32 crane) {
        if(schedule[crane].empty()) return cranes[crane].pos;
        return schedule[crane].front().pos;
    }


    void pick(const i32 crane) {
        schedule[crane].emplace_back(last_pos(crane), OPERATION::PICK);
    }

    void drop(const i32 crane) {
        schedule[crane].emplace_back(last_pos(crane), OPERATION::DROP);
    }


    void destroy(const i32 crane) {
        schedule[crane].emplace_back(last_pos(crane), OPERATION::DESTROY);
    }


    void move_left(const i32 crane) {
        schedule[crane].emplace_back(last_pos(crane) - 1, OPERATION::MOVE_LEFT);
    }

    void move_right(const i32 crane) {
        schedule[crane].emplace_back(last_pos(crane) + 1, OPERATION::MOVE_RIGHT);
    }

    void move_up(const i32 crane) {
        schedule[crane].emplace_back(last_pos(crane) - N, OPERATION::MOVE_UP);
    }

    void move_down(const i32 crane) {
        schedule[crane].emplace_back(last_pos(crane) + N, OPERATION::MOVE_DOWN);
    }


    void move(const i32 crane, const i32 to) {
        const auto pos = last_pos(crane);
        if(to_col(pos) < to_col(to)) {
            REP(to_col(to) - to_col(pos)) move_right(crane);
            REP(std::max(0, to_row(to) - to_row(pos))) move_down(crane);
            REP(std::max(0, to_row(pos) - to_row(to))) move_up(crane);
        }
        else {
            REP(std::max(0, to_row(to) - to_row(pos))) move_down(crane);
            REP(std::max(0, to_row(pos) - to_row(to))) move_up(crane);
            REP(to_col(pos) - to_col(to)) move_left(crane);
        }
    }

    auto carry(const i32 crane, const i32 from, const i32 to) {
        if(board.data[from] < 0) return false;
        if(board.data[to] >= 0) return false;
        debug_("carry"); debug(to_pos(from), to_pos(to));

        locked.insert(board.data[from]);

        move(crane, from);
        pick(crane);
        move(crane, to);
        drop(crane);

        return true;
    }

    void _advance(const i32 crane) {
        if(schedule[crane].empty()) {
            cranes[crane].pause();
            return;
        }

        bool ok = true;

        switch(schedule[crane].front().op) {
            case OPERATION::MOVE_LEFT: ok = _move_left(crane); break;
            case OPERATION::MOVE_RIGHT: ok = _move_right(crane); break;
            case OPERATION::MOVE_UP: ok = _move_up(crane); break;
            case OPERATION::MOVE_DOWN: ok = _move_down(crane); break;
            case OPERATION::DESTROY: ok = _destroy(crane); break;
            case OPERATION::PICK: ok = _pick(crane); break;
            case OPERATION::DROP: ok = _drop(crane); break;
            default: break;
        }

        if(ok) schedule[crane].pop_front();
        else schedule[crane].clear();
    }

    void advance() {
        if(empty()) return;
        REP(i, N) _advance(i);
        board.update();
        output();
    }


    inline bool empty(const i32 crane) {
        return schedule[crane].empty();
    }

    inline bool empty() {
        return std::ranges::all_of(schedule, [&](const auto& v) { return v.empty(); });
    }


    inline void update() {
        while(!empty()) advance();
    }

    void output() {
        ITR(s, cranes) {
            ITR(v, s.history) print << static_cast<char>(v);
            print();
        }
        std::cout << std::flush;
    }
};

signed main() {
    { i32 _; input >> _; }
    uni::grid<i32> A(N, N); input >> A;

    scheduler state(A);
    auto& board = state.board;

    {
        i32 left = 1;
        if(std::ranges::all_of(A, [&](const auto& a) { return a[N - 1] % 5 == 0; })) {
            left = 2;
        }

        REP(i, N) {
            REPD(j, left, N - 1) {
                state.carry(i, to_id(i, 0), to_id(i, j));
            }
        }
    }

    state.update();


    REP(i, 2, N) state.destroy(i);

    buffer_provider buffer;

    REP(i, N) {
        REP(j, 1, N - 1) {
            if(board.data[to_id(i, j)] >= 0) continue;
            buffer.push(to_id(i, j));
        }
    }

    vector<i32> queue;
    REP(i, N) queue.push_back(i * N);


    i32 next = -1;

    while(true) {
        if(state.empty(0)) {
            if(next == -1) {
                auto cost = [&](i32 id) -> i32 {
                    i32 dist = distance(board.pos[id], state.cranes[0].pos);;
                    if(board.pos[id] >= 0) return dist;
                    const auto& que = board.queue[-(board.pos[id] + 1)];
                    return N * N * (std::ranges::find(que, id) - que.begin() + 1) + dist;
                };

                queue.sort([&](i32 i, i32 j) { return cost(i) > cost(j); });

                if(queue.empty()) break;

                next = queue.back(); queue.pop_back();
                debug(next, board.queue, board.data);
                debug(board.pos[next]);
            }

            if(board.pos[next] < 0) {
                debug_("buffer");
                // debug(next, board.pos[next]);
                const auto from = to_id(-(board.pos[next] + 1), 0);
                const auto to = to_goal(board.data[from]);

                const auto buf = buffer.get_middle(from, to);

                state.carry(0, from, buf);
                buffer.pop(buf);
            }
            else {
                debug_("export");
                debug(next);
                // if(state.locked.contains(next)) continue;
                state.carry(0, board.pos[next], to_goal(next));

                if(1 <= to_col(board.pos[next]) && to_col(board.pos[next]) < N - 1) {
                    buffer.push(board.pos[next]);
                }

                if(next % N + 1 < N) queue.push_back(next + 1);

                next = -1;
            }
        }

        if(state.empty(1)) {
            std::unordered_set<i32> ignored_rows;
            ITR(v, state.locked) ignored_rows.insert(to_row(board.pos[v]));

            const auto pos = state.cranes[1].pos;
            if(state.next_pos(0) == pos) {
                if(to_row(pos) >= N / 2) state.move_up(1);
                else state.move_down(1);
            }
            else {
                bool found = false;

                REP(i, N) REP(j, 1, N - 1) {
                    if(ignored_rows.contains(i)) continue; // temp
                    if(state.cranes[0].pos == to_id(i, j)) continue;

                    if(board.data[to_id(i, j)] == -1) {
                        constexpr spair<i32> dirs[] = { { 0, -1 } };
                        ITR(di, dj, dirs) {
                            const i32 ni = i + di, nj = j + dj;
                            if(ni < 0 || nj < 0 || ni >= N - 1 || nj >= N - 1) continue;
                            if(board.data[to_id(ni, nj)] < 0) continue;
                            if(state.locked.contains(board.data[to_id(ni, nj)])) continue;
                            state.carry(1, to_id(ni, nj), to_id(i, j));
                            BREAK(found = true);
                        }
                    }

                    if(found) break;
                }
            }
        }

        state.advance();

        debug(board.data, state.locked);
    }

    state.output();
}
