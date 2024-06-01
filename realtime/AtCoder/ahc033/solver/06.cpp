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
    i32 hold = -1;

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
        assert(hold < 0);
        history.push_back(OPERATION::PICK);
        hold = id;
    }

    auto drop() {
        assert(hold >= 0);
        history.push_back(OPERATION::DROP);
        const auto res = hold;
        hold = -1;
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

    board_type() = default;

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
};

struct motion {
    i32 pos;
    OPERATION op;

    auto _debug() const { return std::make_pair(pos, (char)op); }
};

std::random_device rd;
std::mt19937 rng(rd());


uni::grid<i32> A(N, N);

struct scheduler {
    board_type board;
    std::array<crane_type, N> cranes;
    std::array<std::deque<motion>, N> schedule;
    std::unordered_set<i32> locked;
    std::array<i32, N> picked_from;

    scheduler() = default;

    template<class T>
    scheduler(const T& in) : board(in) {
        REP(i, N) {
            cranes[i] = crane_type(i);
        }
    }


    auto last_time(const i32 crane) {
        return (i32)std::ranges::ssize(schedule[crane]);
    }


    auto curr_pos(const i32 crane) {
        return cranes[crane].pos;
    }

    auto last_pos(const i32 crane) {
        if(schedule[crane].empty()) return curr_pos(crane);
        return schedule[crane].back().pos;
    }

    auto next_pos(const i32 crane) {
        if(schedule[crane].empty()) return curr_pos(crane);
        return schedule[crane].front().pos;
    }

    i32 get_pos(const i32 crane, const i32 time) {
        assert(time >= 0);
        if(time == 0) return curr_pos(crane);
        if(time > std::ranges::ssize(schedule[crane])) return last_pos(crane);
        return schedule[crane][time - 1].pos;
    }


    auto _pick(const i32 crane) {
        if(board.data[cranes[crane].pos] < 0) {
            if(locked.contains(cranes[crane].pos)) locked.erase(cranes[crane].pos);
            cranes[crane].pause();
            return false;
        }

        cranes[crane].pick(board.data[cranes[crane].pos]);
        picked_from[crane] = cranes[crane].pos;
        board.place(cranes[crane].pos, -1);

        return true;
    }

    auto _drop(const i32 crane) {
        if(board.data[cranes[crane].pos] >= 0) throw 0;
        const auto id = cranes[crane].drop();
        if(locked.contains(cranes[crane].pos)) locked.erase(cranes[crane].pos);
        if(locked.contains(picked_from[crane])) locked.erase(picked_from[crane]);
        board.place(cranes[crane].pos, id);
        return true;
    }


    auto _move_left(const i32 crane) {
        if(crane > 0 && cranes[crane].hold >= 0 && board.data[cranes[crane].pos - 1] >= 0) {
            if(to_col(cranes[crane].pos) < N - 1) _drop(crane);
            else throw 1;
            return false;
        }
        cranes[crane].move_left();
        return true;
    }

    auto _move_right(const i32 crane) {
        if(crane > 0 && cranes[crane].hold >= 0 && board.data[cranes[crane].pos + 1] >= 0) {
            if(to_col(cranes[crane].pos) < N - 1) _drop(crane);
            else throw 2;
            return false;
        }
        cranes[crane].move_right();
        return true;
    }

    auto _move_up(const i32 crane) {
        if(crane > 0 && cranes[crane].hold >= 0 && board.data[cranes[crane].pos - N] >= 0) {
            if(to_col(cranes[crane].pos) < N - 1) _drop(crane);
            else throw 3;
            return false;
        }
        cranes[crane].move_up();
        return true;
    }

    auto _move_down(const i32 crane) {
        if(crane > 0 && cranes[crane].hold >= 0 && board.data[cranes[crane].pos + N] >= 0) {
            if(to_col(cranes[crane].pos) < N - 1) _drop(crane);
            else throw 4;
            return false;
        }
        cranes[crane].move_down();
        return true;
    }


    auto _destroy(const i32 crane) {
        cranes[crane].destroy();
        return true;
    }

    auto can_move(const i32 crane, const i32 time, const i32 from, const i32 to, const bool picked = false) {
        assert(time >= 0);

        if(crane > 0 && picked && board.data[to] >= 0) return false;

        REP(i, N) {
            if(i == crane) continue;
            const auto p0 = get_pos(i, time);
            const auto p1 = get_pos(i, time + 1);
            if(p1 == to) return false;
            if(p1 == from && p0 == to) return false;
        }

        return true;
    }


    auto pick(const i32 crane) {
        if(!can_move(crane, last_time(crane), last_pos(crane), last_pos(crane))) return false;
        schedule[crane].emplace_back(last_pos(crane), OPERATION::PICK);
        return true;
    }

    auto drop(const i32 crane) {
        if(!can_move(crane, last_time(crane), last_pos(crane), last_pos(crane))) return false;
        schedule[crane].emplace_back(last_pos(crane), OPERATION::DROP);
        return true;
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

    std::optional<std::vector<i32>> root(const i32 crane, const i32 from, const i32 to, const i32 time, const bool picked = false) {
        std::queue<i32> que;
        vector<i32> dist(N * N, INF32), prev(N * N, -2);

        que.push(from), dist[from] = 0, prev[from] = -1;

        while(!que.empty()) {
            const auto p = que.front(); que.pop();
            if(p == to) break;

            ITR(di, dj, DIRS4) {
                const i32 ni = to_row(p) + di, nj = to_col(p) + dj;
                if(ni < 0 || nj < 0 || ni >= N || nj >= N) continue;
                if(crane > 0 && nj >= N - 1) continue;

                const i32 np = to_id(ni, nj);
                if(prev[np] >= -1) continue;

                if(!can_move(crane, time + dist[p], p, np, picked)) {
                    continue;
                }

                dist[np] = dist[p] + 1;
                prev[np] = p;

                que.push(np);
            }
        }

        auto pos = to;
        if(prev[pos] == -2) {
            return std::nullopt;
        }

        std::vector<i32> path;
        while(prev[pos] >= 0) {
            path.push_back(pos);
            pos = prev[pos];
        }
        path.push_back(from);
        std::ranges::reverse(path);

        return path;
    }

    std::vector<i32> root_vacancy(const i32 crane, const i32 from, const i32 time) {
        std::queue<i32> que;
        vector<i32> dist(N * N, INF32), prev(N * N, -2);

        que.push(from), dist[from] = 0, prev[from] = -1;

        auto to = -1;

        while(!que.empty()) {
            const auto p = que.front(); que.pop();
            if(p != from && to_col(p) < N - 1) BREAK(to = p);

            ITR(di, dj, DIRS4) {
                const i32 ni = to_row(p) + di, nj = to_col(p) + dj;
                if(ni < 0 || nj < 0 || ni >= N || nj >= N) continue;

                const i32 np = to_id(ni, nj);
                if(prev[np] >= -1) continue;

                if(!can_move(crane, time + dist[p], p, np)) {
                    continue;
                }

                dist[np] = dist[p] + 1;
                prev[np] = p;

                que.push(np);
            }
        }

        debug(crane, from);

        auto pos = to;

        if(pos < 0) throw 5;
        assert(prev[pos] >= -1);

        std::vector<i32> path;
        while(prev[pos] >= 0) {
            path.push_back(pos);
            pos = prev[pos];
        }
        path.push_back(from);
        std::ranges::reverse(path);

        return path;
    }

    auto get_motion(const i32 from, const i32 to) {
        if(to_col(from) - 1 == to_col(to)) return OPERATION::MOVE_LEFT;
        if(to_col(from) + 1 == to_col(to)) return OPERATION::MOVE_RIGHT;
        if(to_row(from) - 1 == to_row(to)) return OPERATION::MOVE_UP;
        if(to_row(from) + 1 == to_row(to)) return OPERATION::MOVE_DOWN;
        assert(false);
    }

    auto move(const i32 crane, const i32 to, const bool picked = false) {
        const auto pos = last_pos(crane);
        auto res = root(crane, pos, to, last_time(crane), picked);

        if(!res.has_value()) return false;

        auto path = *res;

        REP(i, 1, path.size()) {
            schedule[crane].emplace_back(path[i], get_motion(path[i - 1], path[i]));
        }

        return true;
    }

    void escape(const i32 crane) {
        const auto pos = last_pos(crane);
        auto path = root_vacancy(crane, pos, last_time(crane));

        debug_("excape"); debug(crane, path);

        REP(i, 1, path.size()) {
            schedule[crane].emplace_back(path[i], get_motion(path[i - 1], path[i]));
        }
    }

    auto carry(const i32 crane, const i32 from, const i32 to) {
        if(board.data[from] < 0) return false;
        if(board.data[to] >= 0) return false;
        // debug_("carry"); debug(to_pos(from), to_pos(to));

        const auto time = last_time(crane);

        if(
            !move(crane, from) ||
            !pick(crane) ||
            !move(crane, to, true) ||
            !drop(crane)
        ) {
            schedule[crane].erase(std::ranges::begin(schedule[crane]) + time, std::ranges::end(schedule[crane]));
            return false;
        }

        locked.insert(from);
        locked.insert(to);

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

        REP(i, N) if(i != crane && cranes[crane].hold >= 0 && cranes[i].hold >= 0 && cranes[i].pos == cranes[crane].pos) throw 6;

        if(!ok) {
            debug_("cancel");
            schedule[crane].clear();
        }
        else {
            schedule[crane].pop_front();
        }
    }

    void advance() {
        if(empty()) return;
        REP(i, N) _advance(i);
        board.update();
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


auto solve(const i32 crane_num) {
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

    REP(i, crane_num, N) state.destroy(i);

    buffer_provider buffer;

    REP(i, N) {
        REP(j, 1, N - 1) {
            if(board.data[to_id(i, j)] >= 0) continue;
            buffer.push(to_id(i, j));
        }
    }

    std::vector<i32> queue;
    REP(i, N) queue.push_back(i * N);


    bool skip_0 = false;
    i32 next = -1;
    std::array<bool, N> move_request{};

    while(true) {
        if(!skip_0 && state.empty(0)) {
            const auto pos = state.cranes[0].pos;

            if(
                std::ranges::any_of(std::views::iota(1, crane_num), [&](const i32 crane) { return state.next_pos(crane) == pos; }) ||
                move_request[0]
            ) {
                move_request[0] = false;
                state.escape(0);
            }

            if(next == -1) {
                auto cost = [&](i32 id) -> i32 {
                    if(state.locked.contains(board.pos[id])) return INF32;
                    i32 dist = distance(board.pos[id], pos);
                    if(board.pos[id] >= 0) return dist;
                    const auto& que = board.queue[-(board.pos[id] + 1)];
                    return N * N * (std::ranges::find(que, id) - que.begin() + 1) + dist;
                };

                std::ranges::sort(queue, [&](i32 i, i32 j) { return cost(i) > cost(j); });

                if(queue.empty()) break;

                next = queue.back(); queue.pop_back();
                if(state.locked.contains(board.pos[next])) {
                    debug("retry");
                    queue.push_back(next);
                    next = -1;
                    skip_0 = true;
                    continue;
                }
                // debug(next, board.queue, board.data);
                // debug(board.pos[next]);
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

                REP(crane, 1, crane_num) {
                    if(board.data[state.cranes[crane].pos] == next) {
                        move_request[crane] = true;
                    }
                }

                if(state.carry(0, board.pos[next], to_goal(next))) {
                    if(1 <= to_col(board.pos[next]) && to_col(board.pos[next]) < N - 1) {
                        buffer.push(board.pos[next]);
                    }

                    if(next % N + 1 < N) queue.push_back(next + 1);
                }
                else {
                    queue.push_back(next);
                }

                next = -1;
            }
        }
        if(skip_0) skip_0 = false;

        REP(crane, 1, crane_num) {
            if(state.empty(crane)) {
                const auto pos = state.cranes[crane].pos;
                if(
                    std::ranges::any_of(std::views::iota(0, crane_num), [&](const i32 c) {
                        if(crane == 2 && crane != c) debug(c, state.next_pos(c));
                        return crane != c && state.next_pos(c) == pos;
                    })
                    || move_request[crane]
                ) {
                    move_request[crane] = false;
                    state.escape(crane);
                }
                else {
                    std::vector<spair<i32>> cands;

                    REP(i, N) REP(j, N - 1) {
                        if(state.locked.contains(to_id(i, j))) continue;
                        if(board.data[to_id(i, j)] < 0) continue;

                        REP(ni, N) REP(nj, N - 1) {
                            if(ni == i && nj == j) continue;
                            // if(ni != i && nj != j) continue;
                            const auto add = [&](const i32 p) {
                                if(state.locked.contains(p)) return;
                                if(board.data[p] >= 0) return;
                                cands.emplace_back(to_id(i, j), p);
                            };
                            add(to_id(ni, nj));
                            // if(0 <= i + k && i + k < N) add(to_id(i + k, j));
                            // if(0 <= j + k && j + k < N - 1) add(to_id(i, j + k));
                        }
                    }

                    std::ranges::sort(cands, [&](auto p, auto q) {
                        const auto diff = [&](auto t) {
                            auto g = to_goal(board.data[t.first]);
                            return distance(g, t.second) - distance(g, t.first);
                        };
                        return diff(p) < diff(q);
                    });


                    ITR(p, q, cands) {
                        const auto goal = to_goal(board.data[p]);
                        if(distance(p, goal) <= distance(q, goal)) continue;
                        if(!state.carry(crane, p, q)) continue;
                        break;
                    }

                    debug_("organize"); debug(crane);
                }
            }
        }


        debug(board.data, board.pos, state.locked, queue, move_request, state.schedule);
        state.advance();
        // state.output();
    }

    return state;
}

signed main() {
    { i32 _; input >> _; }
    input >> A;

    i32 min = INF32;
    scheduler state;

    FORD(cranes, 1, 3) {
        try {
            const auto res = solve(cranes);
            if(chmin(min, std::ranges::max(res.cranes | std::views::transform([&](auto& c) { return (i32)c.history.size(); })))) {
                debug(min);
                state = std::move(res);
            }
        }
        catch (i32 code) {
            debug_("exception");
            debug(cranes, code);
        }
    }

    state.output();
}
