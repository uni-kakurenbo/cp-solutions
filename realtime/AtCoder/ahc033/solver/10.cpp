/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

#include "template/standard.hpp"
#include "utility/timer.hpp"

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


std::mt19937 rng(42);


uni::grid<i32> A(N, N);

struct scheduler {
    board_type board;
    std::array<crane_type, N> cranes;

    std::array<std::deque<motion>, N> schedule;
    std::deque<board_type> future_boards;

    std::array<i32, N> picked_from;
    std::array<i32, N> holding;

    i32 remaing = N * N;

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

    const auto& get_board_const(const i32 time) {
        assert(time >= 0);
        if(time == 0) return board;
        while(time > std::ranges::ssize(future_boards)) {
            if(future_boards.empty()) future_boards.push_back(board);
            else future_boards.push_back(future_boards.back());
        }
        return future_boards[time - 1];
    }

    auto& get_board(const i32 time) {
        assert(time > 0);
        while(time > std::ranges::ssize(future_boards)) {
            if(future_boards.empty()) future_boards.push_back(board);
            else future_boards.push_back(future_boards.back());
        }
        return future_boards[time - 1];
    }


    auto _pick(const i32 crane) {
        assert(board.data[cranes[crane].pos] >= 0);

        cranes[crane].pick(board.data[cranes[crane].pos]);
        picked_from[crane] = cranes[crane].pos;

        return true;
    }

    auto _drop(const i32 crane) {
        assert(board.data[cranes[crane].pos] < 0);
        cranes[crane].drop();
        if(to_col(cranes[crane].pos) == N - 1) --remaing;
        return true;
    }


    auto _move_left(const i32 crane) {
        if(crane > 0 && cranes[crane].hold >= 0 && board.data[cranes[crane].pos - 1] >= 0) {
            throw 0;
            assert(false);
        }
        cranes[crane].move_left();
        return true;
    }

    auto _move_right(const i32 crane) {
        if(crane > 0 && cranes[crane].hold >= 0 && board.data[cranes[crane].pos + 1] >= 0) {
            throw 1;
            assert(false);
        }
        cranes[crane].move_right();
        return true;
    }

    auto _move_up(const i32 crane) {
        if(crane > 0 && cranes[crane].hold >= 0 && board.data[cranes[crane].pos - N] >= 0) {
            throw 2;
            assert(false);
        }
        cranes[crane].move_up();
        return true;
    }

    auto _move_down(const i32 crane) {
        if(crane > 0 && cranes[crane].hold >= 0 && board.data[cranes[crane].pos + N] >= 0) {
            throw 3;
            assert(false);
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

        if(crane > 0 && picked && get_board_const(time).data[to] >= 0) return false;

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

        holding[crane] = get_board_const(last_time(crane)).data[last_pos(crane)];
        if(holding[crane] < 0) return false;

        FOR(t, last_time(crane), uni::max(last_time(crane), std::ranges::ssize(future_boards) - 1)) {
            get_board(t + 1).place(last_pos(crane), -1);
            get_board(t + 1).update();
        }

        schedule[crane].emplace_back(last_pos(crane), OPERATION::PICK);

        return true;
    }

    auto drop(const i32 crane) {
        if(!can_move(crane, last_time(crane), last_pos(crane), last_pos(crane))) return false;

        if(get_board_const(last_time(crane) + 1).data[last_pos(crane)] >= 0) return false;

        FOR(t, last_time(crane), uni::max(last_time(crane), std::ranges::ssize(future_boards) - 1)) {
            get_board(t + 1).place(last_pos(crane), holding[crane]);
            get_board(t + 1).update();
        }

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
        std::priority_queue<spair<i32>, std::vector<spair<i32>>, std::greater<spair<i32>>> que;

        constexpr i32 M = N * N;
        constexpr i32 K = 1;

        vector<i32> dist(M * K, INF32), prev(M * K, -2);

        const auto h = [&](const i32 p) { return distance(p, to); };

        que.emplace(h(from), from), prev[from] = -1, dist[from] = 0;

        i32 pos = -1;

        while(!que.empty()) {
            const auto [ f, id ] = que.top(); que.pop();
            const auto p = id % M, t = id / M;
            const auto d = f - h(p);

            if(p == to) BREAK(pos = id);
            if(d > dist[id]) continue;

            spair<i32> dirs[5]; std::ranges::copy(DIRS4P, dirs);
            std::ranges::shuffle(dirs, rng);

            ITR(di, dj, dirs) {
                const i32 ni = to_row(p) + di, nj = to_col(p) + dj;
                if(ni < 0 || nj < 0 || ni >= N || nj >= N) continue;
                // if(crane > 0 && nj >= N - 1) continue;

                const i32 np = to_id(ni, nj);
                const i32 nt = t + (p == np);
                const i32 nd = d + 1;
                if(nt >= K) continue;

                const i32 nid = np + M * nt;
                if(nd >= dist[nid]) continue;


                if(!can_move(crane, time + d, p, np, picked)) continue;

                prev[nid] = id;
                dist[nid] = nd;

                que.emplace(nd + h(np), nid);
            }
        }

        if(pos < 0 || prev[pos] == -2) {
            return std::nullopt;
        }

        std::vector<i32> path;
        while(prev[pos] >= 0) {
            path.push_back(pos % M);
            pos = prev[pos];
        }
        path.push_back(from);
        std::ranges::reverse(path);

        return path;
    }

    // std::optional<std::vector<i32>> root(const i32 crane, const i32 from, const i32 to, const i32 time, const bool picked = false) {
    //     std::queue<i32> que;
    //     vector<i32> dist(N * N, INF32), prev(N * N, -2);

    //     que.push(from), dist[from] = 0, prev[from] = -1;

    //     while(!que.empty()) {
    //         const auto p = que.front(); que.pop();
    //         if(p == to) break;

    //         spair<i32> dirs[4]; std::ranges::copy(DIRS4, dirs);
    //         std::ranges::shuffle(dirs, rng);

    //         ITR(di, dj, dirs) {
    //             const i32 ni = to_row(p) + di, nj = to_col(p) + dj;
    //             if(ni < 0 || nj < 0 || ni >= N || nj >= N) continue;
    //             // if(crane > 0 && nj >= N - 1) continue;

    //             const i32 np = to_id(ni, nj);
    //             if(prev[np] >= -1) continue;

    //             if(!can_move(crane, time + dist[p], p, np, picked)) {
    //                 continue;
    //             }

    //             dist[np] = dist[p] + 1;
    //             prev[np] = p;

    //             que.push(np);
    //         }
    //     }

    //     auto pos = to;
    //     if(prev[pos] == -2) {
    //         return std::nullopt;
    //     }

    //     std::vector<i32> path;
    //     while(prev[pos] >= 0) {
    //         path.push_back(pos);
    //         pos = prev[pos];
    //     }
    //     path.push_back(from);
    //     std::ranges::reverse(path);

    //     return path;
    // }


    std::vector<i32> root_vacancy(const i32 crane, const i32 from, const i32 time) {
        std::queue<i32> que;
        vector<i32> dist(N * N, INF32), prev(N * N, -2);

        que.push(from), dist[from] = 0, prev[from] = -1;

        auto to = -1;

        while(!que.empty()) {
            const auto p = que.front(); que.pop();
            if(p != from && to_col(p) < N - 1) BREAK(to = p);

            spair<i32> dirs[4]; std::ranges::copy(DIRS4, dirs);
            std::ranges::shuffle(dirs, rng);

            ITR(di, dj, dirs) {
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
        // if(from == to) return OPERATION::PAUSE;
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

    auto exist_from(const i32 time, const i32 to) {
        FOR(t, time, uni::max(time, std::ranges::ssize(future_boards))) {
            if(get_board_const(t).data[to] < 0) return false;
        }
        return true;
    }

    auto vacant_from(const i32 time, const i32 to) {
        FOR(t, time, uni::max(time, std::ranges::ssize(future_boards))) {
            if(get_board_const(t).data[to] >= 0) return false;
        }
        return true;
    }

    auto can_carry(const i32 crane, const i32 from, const i32 to) {
        auto time = last_time(crane);

        {
            auto path = root(crane, last_pos(crane), from, time);
            if(!path) return false;
            time += std::ranges::ssize(*path);
        }

        if(!exist_from(time, from)) return false;
        if(!can_move(crane, time, from, from)) return false;

        {
            auto path = root(crane, from, to, time, true);
            if(!path) return false;
            time += std::ranges::ssize(*path);
        }

        if(!can_move(crane, time, to, to)) return false;
        if(!vacant_from(time, to)) return false;

        return true;
    }

    auto carry(const i32 crane, const i32 to) {
        const i32 from = last_pos(crane);
        debug(crane, board.data[from], to_pos(from), to_pos(to));

        const auto time = last_time(crane);

        auto rev = future_boards;

        if(
            !exist_from(crane, from) ||
            !pick(crane) ||
            !move(crane, to, true) ||
            !vacant_from(last_time(crane), to) ||
            !drop(crane)
        ) {
            schedule[crane].erase(std::ranges::begin(schedule[crane]) + time, std::ranges::end(schedule[crane]));
            future_boards = rev;
            return false;
        }

        return true;
    }


    void _advance(const i32 crane) {
        if(schedule[crane].empty()) {
            cranes[crane].pause();
            return;
        }

        bool ok = true;

        switch(schedule[crane].front().op) {
            case OPERATION::PAUSE: cranes[crane].pause(); break;
            case OPERATION::MOVE_LEFT: ok = _move_left(crane); break;
            case OPERATION::MOVE_RIGHT: ok = _move_right(crane); break;
            case OPERATION::MOVE_UP: ok = _move_up(crane); break;
            case OPERATION::MOVE_DOWN: ok = _move_down(crane); break;
            case OPERATION::DESTROY: ok = _destroy(crane); break;
            case OPERATION::PICK: ok = _pick(crane); break;
            case OPERATION::DROP: ok = _drop(crane); break;
            default: break;
        }

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

        // debug(future_boards | std::views::transform([&](auto& v) { return v.data; }));
        // assert(!future_boards.empty());
        if(!future_boards.empty()) {
            board = std::move(future_boards.front());
            future_boards.pop_front();
        }
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
        i32 left = rng() % (N - 2) + 1;
        if(std::ranges::all_of(A, [&](const auto& a) { return a[N - 1] % 5 == 0; })) {
            chmax(left, 2);
        }

        REP(i, N) {
            REPD(j, left, N - 1) {
                state.move(i, to_id(i, 0));
                state.carry(i, to_id(i, j));
            }
        }
    }

    state.update();

    // return state;

    REP(i, crane_num, N) state.destroy(i);

    std::array<spair<i32>, N> next; next.fill({ -1, -1 });

    auto can_export = [&](const i32 i, const i32 j, const i32 ni) {
        const auto id = board.data[to_id(i, j)];
        assert(id >= 0);
        if(id % N == 0) return id / N == ni;
        assert(id % N > 0);
        if(board.pos[id - 1] == -INF32) return id / N == ni;
        return false;
    };

#  ifdef DEBUGGER_ENABLED
    uni::timer timer(10000);
#  else
    uni::timer timer(100);
#  endif

    while(true) {
        if(timer.expired()) throw 7;
        debug(next);

        REP(crane, crane_num) {
            if(!state.empty(crane)) continue;

            if(next[crane].first < 0) {
                state.escape(crane);

                std::vector<spair<i32>> cands;
                {
                    const auto cost = [&](auto t) {
                        const auto g = to_goal(board.data[t.first]);
                        if(crane == 0 && distance(g, t.second) == 0) return -INF32;

                        if(to_col(t.first) == 0 && !board.queue[to_col(t.first)].empty()) return -INF32 / 2 ;

                        if(distance(g, t.second) >= distance(g, t.first)) return 0;

                        return N * N * distance(g, t.second) + distance(t.first, state.cranes[crane].pos) - INF32 / 4;
                    };

                    REP(i, N) REP(j, N - 1) {
                        const auto from = to_id(i, j);

                        if(board.data[from] < 0) continue;
                        if(
                            std::ranges::any_of(
                                next,
                                [&](const auto& p) { return p.first == from; }
                            )
                        ) continue;

                        REP(ni, N) REP(nj, N) {
                            if(ni == i && nj == j) continue;
                            if(nj == N - 1 && !can_export(i, j, ni)) continue;

                            const auto to = to_id(ni, nj);

                            if(board.data[to] >= 0) continue;
                            if(cost(std::make_pair(from, to)) >= 0) continue;
                            if(!state.can_carry(crane, from, to)) continue;

                            cands.emplace_back(from, to);
                        }
                    }

                    if(cands.empty()) continue;

                    next[crane] = std::ranges::min(cands, [&](auto p, auto q) {
                        return cost(p) < cost(q);
                    });
                }

                continue;
            }

            const auto [ from, to ] = next[crane];

            if(state.curr_pos(crane) != from) {
                if(state.can_carry(crane, from, to)) {
                    state.move(crane, from);
                }
                else {
                    state.escape(crane);
                    next[crane] = { -1, -1 };
                }
            }
            else {
                if(!state.carry(crane, to)) state.escape(crane);
                next[crane] = { -1, -1 };
            }
        }

        debug(board.data, board.pos, state.schedule, state.remaing);
        state.advance();
        // state.output();

        REP(i, N) REP(j, i + 1, N) if(state.cranes[i].pos >= 0 && state.cranes[i].pos == state.cranes[j].pos) throw 6;

        if(state.remaing == 0) break;
    }

    return state;
}

signed main() {
    { i32 _; input >> _; }
    input >> A;

    i32 min = INF32;
    scheduler state;

    // try {
    //     solve(4).output();
    // } catch(const i32 code) {
    //     debug(code);
    // }

    // return 0;

    constexpr i32 START = 3;

    FORD(cranes, START, N) {
        uni::timer timer(2800 / (N - START + 1));
        std::cerr << "start: " << cranes << "\n";
        i32 cnt = 0;

        while(!timer.expired()) {
            try {
                const auto res = solve(cranes);
                if(chmin(min, std::ranges::max(res.cranes | std::views::transform([&](auto& c) { return (i32)c.history.size(); })))) {
                    std::cerr << min << "\n";
                    state = std::move(res);
                }
                ++cnt;
            }
            catch (i32 code) {
                // std::cerr << "exception: " << code << "\n";
            }
        }

        std::cerr << "valid: " << cnt << "\n";
    }

    state.output();
}
