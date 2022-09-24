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
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include <fstream>

#include <atcoder/dsu>

using namespace std;
using namespace atcoder;

struct MoveAction {
    int before_row, before_col, after_row, after_col;
    MoveAction(int before_row, int before_col, int after_row, int after_col)
        : before_row(before_row), before_col(before_col), after_row(after_row),
          after_col(after_col) {}
};

struct ConnectAction {
    int c1_row, c1_col, c2_row, c2_col;
    ConnectAction(int c1_row, int c1_col, int c2_row, int c2_col)
        : c1_row(c1_row), c1_col(c1_col), c2_row(c2_row), c2_col(c2_col) {}
};

struct History {
    vector<MoveAction> move;
    vector<ConnectAction> connect;
    History(const vector<MoveAction> &move = {}, const vector<ConnectAction> &con = {})
        : move(move), connect(con) {}
};

using Grid = vector<string>;

struct Field {
    static constexpr int DR[4] = {0, 1, 0, -1};
    static constexpr int DC[4] = {1, 0, -1, 0};

    static constexpr char USED = 'x';

    int N, K;
    int action_count_limit;
    Grid grid;
    History history;

    Field(int N, int K, const Grid &grid) : N(N), K(K), action_count_limit(K * 100), grid(grid) {}

    bool can_move(int row, int col, int dir) const {
        int nrow = row + DR[dir];
        int ncol = col + DC[dir];
        if(0 <= nrow && nrow < N && 0 <= ncol && ncol < N) {
            return grid[nrow][ncol] == '0';
        }
        return false;
    }

    bool swap(int row, int col, int dir) {
        if(grid[row][col] == '0' || !can_move(row, col, dir)) return false;

        std::swap(grid[row][col], grid[row + DR[dir]][col + DC[dir]]);
        history.move.emplace_back(row, col, row + DR[dir], col + DC[dir]);
        --action_count_limit;

        return true;
    }

    bool can_connect(int row, int col, int dir) const {
        int nrow = row + DR[dir];
        int ncol = col + DC[dir];
        while(0 <= nrow && nrow < N && 0 <= ncol && ncol < N) {
            if(grid[nrow][ncol] == grid[row][col]) {
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
            assert(grid[nrow][ncol] == '0');
            grid[nrow][ncol] = USED;
            nrow += DR[dir];
            ncol += DC[dir];
        }
        assert(false);
    }

    bool connect(int i, int j) {
        if(grid[i][j] != '0' && grid[i][j] != 'x') {
            for(int dir = 0; dir < 2; dir++) {
                if(action_count_limit <= 0) return false;
                if(!can_connect(i, j, dir)) continue;
                history.connect.push_back(line_fill(i, j, dir));
                action_count_limit--;
                if(action_count_limit <= 0) {
                    return false;
                }
            }
        }
        return true;
    }
};

struct Solver {
    Field field;
    mt19937 *engine;

    Solver(const Field &field, mt19937 *engine) : field(field), engine(engine) {
    }

    bool move(Field *target) {
        int row = (*engine)() % target->N;
        int col = (*engine)() % target->N;
        int dir = (*engine)() % 4;

        return target->swap(row, col, dir);
    }


    static void connect_all(Field *target) {
        for(int i = 0; i < target->N; i++) {
            for(int j = 0; j < target->N; j++) {
                if(!target->connect(i, j)) return;
            }
        }
        return;
    }

    Field solve(int move_limit = -1) {
        if(move_limit == -1) {
            move_limit = field.K * 50;
        }

        for(int i=0; i<move_limit; i++) move(&field);

        return field;
    }
};

struct Converter {
    int N = 0;
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


int calc_score(Field field) {
    int N = field.N;

    Solver::connect_all(&field);

    Converter converter(N);
    dsu uf(N*N);

    for(auto r : field.history.connect) {
        uf.merge(converter.pair_to_id(r.c1_row, r.c1_col), converter.pair_to_id(r.c2_row, r.c2_col));
    }

    vector groups = uf.groups();

    auto group_point = [](int acc, vector<int> &group) {
        int n = group.size();
        return acc + n*(n-1)/2;
    };

    int score = accumulate(groups.begin(), groups.end(), 0, group_point);

    return max(score, 0);
}

template<class Stream> void print_answer(Stream *stream, const History &res) {
    *stream << res.move.size() << endl;
    for(auto m : res.move) {
        *stream << m.before_row << " " << m.before_col << " " << m.after_row << " " << m.after_col << endl;
    }
    *stream << res.connect.size() << endl;
    for(auto m : res.connect) {
        *stream << m.c1_row << " " << m.c1_col << " " << m.c2_row << " " << m.c2_col << endl;
    }
}

int constexpr TIME_LIMIT_MS = 2950;

int main() {
    clock_t start = clock();

    int N, K;
    cin >> N >> K;
    Grid grid(N);
    for(int i = 0; i < N; i++) {
        cin >> grid[i];
    }

    Field initial_field(N, K, grid);

    mt19937 enginge;
    enginge.seed(0);

    Solver solver(initial_field, &enginge);
    Field ans = solver.solve(0);
    int score_max = calc_score(ans);

    // ofstream of_log(".log");

    while((clock() - start) * 1000 < TIME_LIMIT_MS * CLOCKS_PER_SEC) {
        Solver solver(ans, &enginge);
        int motin_limit = 1;
        Field ret = solver.solve(motin_limit);
        int score = calc_score(ret);
        if(score_max < score) {
            debug(score);
            score_max = score;

            // {
            //     auto temp = ans;
            //     Solver::connect_all(&temp);
            //     print_answer(&of_log, temp.history);
            // }

            ans = ret;
        }
    }

    Solver::connect_all(&ans);
    clog << score_max << "\n";
    // print_answer(&of_log, ans.history);
    print_answer(&cout, ans.history);

    return 0;
}
