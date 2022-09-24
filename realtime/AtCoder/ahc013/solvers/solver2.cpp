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

struct Result {
    vector<MoveAction> move;
    vector<ConnectAction> connect;
    Result(const vector<MoveAction> &move, const vector<ConnectAction> &con)
        : move(move), connect(con) {}
};

struct Solver {
    static constexpr char USED = 'x';
    static constexpr int DR[4] = {0, 1, 0, -1};
    static constexpr int DC[4] = {1, 0, -1, 0};

    int N, K;
    int action_count_limit;
    mt19937 engine;
    vector<string> field;

    Solver(int N, int K, const vector<string> &field, int seed = 0)
        : N(N), K(K), action_count_limit(K * 100), field(field) {
        engine.seed(seed);
    }

    bool can_move(int row, int col, int dir) const {
        int nrow = row + DR[dir];
        int ncol = col + DC[dir];
        if(0 <= nrow && nrow < N && 0 <= ncol && ncol < N) {
            return field[nrow][ncol] == '0';
        }
        return false;
    }

    vector<MoveAction> move(int move_limit = -1) {
        vector<MoveAction> ret;
        if(move_limit == -1) {
            move_limit = K * 50;
        }

        for(int i=0, j=0; i<move_limit*2 && j<move_limit; i++) {
            int row = engine() % N;
            int col = engine() % N;
            int dir = engine() % 4;
            if(field[row][col] != '0' && can_move(row, col, dir)) {
                swap(field[row][col], field[row + DR[dir]][col + DC[dir]]);
                ret.emplace_back(row, col, row + DR[dir], col + DC[dir]);
                action_count_limit--;
                ++j;
            }
        }

        return ret;
    }

    bool can_connect(int row, int col, int dir) const {
        int nrow = row + DR[dir];
        int ncol = col + DC[dir];
        while(0 <= nrow && nrow < N && 0 <= ncol && ncol < N) {
            if(field[nrow][ncol] == field[row][col]) {
                return true;
            } else if(field[nrow][ncol] != '0') {
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
            if(field[nrow][ncol] == field[row][col]) {
                return ConnectAction(row, col, nrow, ncol);
            }
            assert(field[nrow][ncol] == '0');
            field[nrow][ncol] = USED;
            nrow += DR[dir];
            ncol += DC[dir];
        }
        assert(false);
    }

    vector<ConnectAction> connect() {
        vector<ConnectAction> ret;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(field[i][j] != '0' && field[i][j] != 'x') {
                    for(int dir = 0; dir < 2; dir++) {
                        if(can_connect(i, j, dir)) {
                            ret.push_back(line_fill(i, j, dir));
                            action_count_limit--;
                            if(action_count_limit <= 0) {
                                return ret;
                            }
                        }
                    }
                }
            }
        }
        return ret;
    }

    Result solve(int motion_limit = -1) {
        auto moves = move(motion_limit);
        auto connects = connect();
        return Result(moves, connects);
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


int calc_score(int N, vector<string> field, const Result &res) {
    Converter converter(N);
    dsu uf(N*N);

    for(auto r : res.move) {
        assert(field[r.before_row][r.before_col] != '0');
        assert(field[r.after_row][r.after_col] == '0');
        swap(field[r.before_row][r.before_col], field[r.after_row][r.after_col]);
    }

    for(auto r : res.connect) {
        uf.merge(converter.pair_to_id(r.c1_row, r.c1_col), converter.pair_to_id(r.c2_row, r.c2_col));
    }

    vector<int> computers;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(field[i][j] != '0') {
                computers.emplace_back(converter.pair_to_id(i, j));
            }
        }
    }

    int score = 0;
    int L = computers.size();
    for(int i = 0; i < L; i++) {
        for(int j = i + 1; j < L; j++) {
            int c1 = computers[i], c2 = computers[j];
            if(uf.same(c1, c2)) {
                score +=
                    (field[converter.id_to_first(c1)][converter.id_to_second(c1)] == field[converter.id_to_first(c2)][converter.id_to_second(c2)])
                        ? 1
                        : -1;
            }
        }
    }

    return max(score, 0);
}

void print_answer(const Result &res) {
    cout << res.move.size() << endl;
    for(auto m : res.move) {
        cout << m.before_row << " " << m.before_col << " " << m.after_row << " "
             << m.after_col << endl;
    }
    cout << res.connect.size() << endl;
    for(auto m : res.connect) {
        cout << m.c1_row << " " << m.c1_col << " " << m.c2_row << " "
             << m.c2_col << endl;
    }
}

int constexpr TIME_LIMIT_MS = 2950;

int main() {
    clock_t start = clock();

    int N, K;
    cin >> N >> K;
    vector<string> field(N);
    for(int i = 0; i < N; i++) {
        cin >> field[i];
    }

    mt19937 seed_generaotr;
    seed_generaotr.seed(0);

    int score_max = 0;
    Result ans({},{});

    while((clock() - start) * 1000 < TIME_LIMIT_MS * CLOCKS_PER_SEC) {
        Solver s(N, K, field, seed_generaotr());
        int motin_limit = K*80;//K * (const int[]){ 40, 50, 60 }[seed_generaotr()%3];
        Result ret = s.solve(motin_limit);
        int score = calc_score(N, field, ret);
        if(score_max < score) {
            score_max = score;
            cerr << score << endl;
            ans = ret;
        }
    }

    print_answer(ans);

    return 0;
}
