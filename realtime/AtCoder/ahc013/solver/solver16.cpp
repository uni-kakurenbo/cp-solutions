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

#include <iostream>
#include <algorithm>
#include <random>
#include <utility>
#include <vector>
#include <fstream>
#include <deque>

using namespace std;


struct UnionFind {
    using Group = vector<int>;
    using Groups = vector<Group>;

    int N;
    UnionFind(int N) : N(N), parent_or_size(N, -1) {}

    int unite(int a, int b) {
        dev_assert(0 <= a && a < N);
        dev_assert(0 <= b && b < N);
        int x = root(a), y = root(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    int root(int a) {
        dev_assert(0 <= a && a < N);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = root(parent_or_size[a]);
    }

    int size(int a) {
        dev_assert(0 <= a && a < N);
        return -parent_or_size[root(a)];
    }

    void build_groups(Groups *res) {
        vector<int> roots(N), group_size(N);
        for(int i=0; i<N; ++i) {
            roots[i] = root(i);
            ++group_size[roots[i]];
        }
        res->resize(N);
        for(int i=0; i<N; ++i) (*res)[i].reserve(group_size[i]);
        for(int i=0; i<N; ++i) (*res)[roots[i]].emplace_back(i);
        return;
    }

  private:
    vector<int> parent_or_size;
};


struct MoveAction {
    const int before_row, before_col, after_row, after_col;
    MoveAction(const int before_row, const int before_col, const int after_row, const int after_col)
        : before_row(before_row), before_col(before_col), after_row(after_row), after_col(after_col) {}
};

struct ConnectAction {
    const int c1_row, c1_col, c2_row, c2_col;
    ConnectAction(const int c1_row, const int c1_col, const int c2_row, const int c2_col)
        : c1_row(c1_row), c1_col(c1_col), c2_row(c2_row), c2_col(c2_col) {}
};

struct History {
    vector<MoveAction> move;
    vector<ConnectAction> connect;
    History(const vector<MoveAction> &move = {}, const vector<ConnectAction> &con = {}) : move(move), connect(con) {}
};


using Grid = vector<string>;

constexpr char USED = 'x';

struct Converter {
    const int N = 0;
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

struct Field {
    static constexpr int DR[4] = { 0, 1, 0, -1 };
    static constexpr int DC[4] = { 1, 0, -1, 0 };
    int N, K;
    int action_count_limit;
    Grid grid;
    History history;
    Converter *converter = nullptr;

    Field(const int N, const int K, const Grid &grid, Converter &converter)
        : N(N), K(K), action_count_limit(K * 100), grid(grid), converter(&converter) {}

    bool can_move(int row, int col, int dir) const {
        int nrow = row + DR[dir];
        int ncol = col + DC[dir];
        if(0 <= nrow && nrow < N && 0 <= ncol && ncol < N) {
            return grid[nrow][ncol] == '0';
        }
        return false;
    }

    void swap(int row, int col, int dir) {
        std::swap(grid[row][col], grid[row + DR[dir]][col + DC[dir]]);
        history.move.emplace_back(row, col, row + DR[dir], col + DC[dir]);
        --action_count_limit;
        return;
    }

    bool can_connect(int row, int col, int dir, int *res_pos = nullptr) const {
        int nrow = row + DR[dir];
        int ncol = col + DC[dir];
        while(0 <= nrow && nrow < N && 0 <= ncol && ncol < N) {
            if(grid[nrow][ncol] == grid[row][col]) {
                if(res_pos != nullptr) *res_pos = converter->pair_to_id(nrow, ncol);
                return true;
            } else if(grid[nrow][ncol] != '0') {
                return false;
            }
            nrow += DR[dir];
            ncol += DC[dir];
        }
        return false;
    }

    ConnectAction line_fill(int row, int col, int dir) {
        int nrow = row + DR[dir];
        int ncol = col + DC[dir];
        while(0 <= nrow && nrow < N && 0 <= ncol && ncol < N) {
            if(grid[nrow][ncol] == grid[row][col]) {
                return ConnectAction(row, col, nrow, ncol);
            }
            dev_assert(grid[nrow][ncol] == '0');
            grid[nrow][ncol] = USED;
            nrow += DR[dir];
            ncol += DC[dir];
        }
        assert(false);
    }

    void connect(int i, int j, int dir) {
        history.connect.push_back(line_fill(i, j, dir));
        action_count_limit--;
        return;
    }
};

struct Evaluator {
    const Converter *converter;

    Evaluator(const Converter &converter) : converter(&converter) {};

    int calc_score(const Field &field) {
        int N = field.N;

        UnionFind uf(N*N);

        for(auto r : field.history.connect) {
            uf.unite(converter->pair_to_id(r.c1_row, r.c1_col), converter->pair_to_id(r.c2_row, r.c2_col));
        }

        UnionFind::Groups groups;
        uf.build_groups(&groups);

        auto group_point = [](const int acc, const UnionFind::Group &group) {
            int n = group.size();
            return acc + n*(n-1)/2;
        };

        int score = accumulate(groups.cbegin(), groups.cend(), 0, group_point);

        return max(score, 0);
    }
};

struct Connector {
    static constexpr int CONNECT_DIRS[2] = { 0, 1 };

    const Converter *converter;

    Connector(const Converter &converter) : converter(&converter) {}

    void connect_all(Field *target) {
        const int N = target->N;

        UnionFind uf(N*N);

        for(int i=0; i<N; ++i) {
            for(int j=0; j<N; ++j) {
                if(target->grid[i][j] != '0') {
                    for(int dir : CONNECT_DIRS) {
                        int pos = -1;
                        if(!target->can_connect(i, j, dir, &pos)) continue;
                        uf.unite(converter->pair_to_id(i, j), pos);
                    }
                }
            }
        }
        UnionFind::Groups groups;
        uf.build_groups(&groups);

        auto last = remove_if(groups.begin(), groups.end(), [](vector<int> &group){ return group.size() <= 1; });
        // debug(*prev(last), *last, *next(last));

        sort(groups.begin(), last, [](vector<int> &a, vector<int> &b) { return a.size() > b.size(); });

        for(auto group=groups.begin(); group!=last; ++group) {
            for(auto v=group->begin(); v!=group->end(); v++) {
                int i = converter->id_to_first(*v), j = converter->id_to_second(*v);
                if(target->grid[i][j] != '0' && target->grid[i][j] != USED) {
                    for(int dir : CONNECT_DIRS) {
                        if(target->action_count_limit <= 0) return;
                        if(!target->can_connect(i, j, dir)) continue;
                        target->connect(i, j, dir);
                    }
                }
            }
        }

        return;
    }
};

struct Solver {
    Field field;
    mt19937 *engine = nullptr;

    Solver(const Field &field, mt19937 *engine) : field(field), engine(engine) {}

    bool move(Field *target) {
        // clog << (*engine) << "\n";
        int row = (*engine)() % target->N;
        int col = (*engine)() % target->N;
        int dir = (*engine)() % 4;

        if(target->grid[row][col] == '0' || !target->can_move(row, col, dir)) return false;
        target->swap(row, col, dir);
        return true;
    }

    Field solve(int move_limit = -1) {
        if(move_limit == -1) {
            move_limit = field.K * 50;
        }

        for(int i=0; i<move_limit; i++) move(&field);

        return field;
    }
};

template<class Stream> void print_answer(Stream *stream, const History &res) {
    *stream << res.move.size() << endl;
    for(auto &m : res.move) {
        *stream << m.before_row << " " << m.before_col << " " << m.after_row << " " << m.after_col << endl;
    }
    *stream << res.connect.size() << endl;
    for(auto &m : res.connect) {
        *stream << m.c1_row << " " << m.c1_col << " " << m.c2_row << " " << m.c2_col << endl;
    }
}

int constexpr TIME_LIMIT_MS = 2950;

constexpr int MOVE_LIMITS[10] = { 1, 1, 1, 1, 1, 1, 2, 3, 7, 10 };

struct State {
    int score, gen;
    Field field;
    State(int score, int gen, Field &field) : score(score), gen(gen), field(field) {};

    #ifdef LOCAL_JUDGE
        vector<int> _debug() {
            return { score, gen };
        }
    #endif

};

int main() {
    clock_t start = clock();

    int N, K; cin >> N >> K;
    Grid grid(N);

    for(int i = 0; i < N; i++) {
        cin >> grid[i];
    }

    Converter converter(N);
    Connector connector(converter);
    Evaluator evaluator(converter);


    Field initial_field(N, K, grid, converter);

    mt19937 engine;
    engine.seed(0);

    #ifdef LOCAL_JUDGE
        ofstream of_log(".log");
    #endif

    const int density = K * 1000 / (N*N);
    int frequency = MOVE_LIMITS[density];

    int Alpha = 5;
    int Beta = 30;

    if(N > 20) Alpha = 3, Beta = 25;
    if(N > 30) Alpha = 1, Beta = 20;
    if(N > 38) Beta = 10;
    if(N > 43) Beta = 8;
    if(N > 46) Beta = 7;

    if(density >= 8) Alpha = 5;

    deque<State> buffer;
    int score_max = 0, score_min = 0;

    {
        Field tmp = initial_field;

        connector.connect_all(&tmp);

        #ifdef LOCAL_JUDGE
            print_answer(&of_log, tmp.history);
        #else
            score_max += 0;
        #endif

        int score = evaluator.calc_score(tmp);
        score_max = score_min = score;
        debug(score);

        buffer.emplace_back(score, 0, initial_field);
    }
    // debug(buffer);

    int cnt = 0;
    // while(cnt < 10) {
    while((clock() - start) * 1000 < TIME_LIMIT_MS * CLOCKS_PER_SEC) {
        ++cnt;
        int l = buffer.size();
        for(int i=0; i<l; ++i) {
            const State *node = &buffer[i];
            int gen = node->gen;

            Solver solver(node->field, &engine);

            for(int j=0; j<Alpha; ++j) {
                Field res = solver.solve(frequency);

                Field tmp = res;
                connector.connect_all(&tmp);
                int score = evaluator.calc_score(tmp);

                if(score > score_min) {
                    buffer.emplace_back(score, gen + 1, res);
                }
            }
        }

        sort(buffer.begin(), buffer.end(), [](const State &a, const State &b) { return a.score == b.score ? a.gen < b.gen : a.score > b.score; });

        while((int)buffer.size() > Beta) buffer.pop_back();

        score_min = buffer.rbegin()->score;

        // debug(buffer, score_min);

        #ifdef LOCAL_JUDGE
            if(buffer.begin()->score > score_max) {
                score_max = buffer.begin()->score;
                Field tmp = buffer.begin()->field;
                connector.connect_all(&tmp);
                debug(score_max);
                print_answer(&of_log, tmp.history);
            }
        #endif

    }

    State *ans = &buffer.front();
    connector.connect_all(&ans->field);

    clog << "Density: " << density << "\n";
    clog << "Frequency: " << frequency << "\n";
    clog << "Alpha: " << Alpha << "\n";
    clog << "Beta: " << Beta << "\n";
    clog << "Loop: " << cnt << "\n";
    clog << "Final Generation: " << ans->gen << "\n";

    #ifdef LOCAL_JUDGE
        print_answer(&of_log, ans->field.history);
    #endif
    clog <<  ans->score << "\n";

    print_answer(&cout, ans->field.history);

    return 0;
}
