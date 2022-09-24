#include <cassert>
#include <iostream>
#include <map>
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

        for(int i = 0; i < move_limit; i++) {
            int row = engine() % N;
            int col = engine() % N;
            int dir = engine() % 4;
            if(field[row][col] != '0' && can_move(row, col, dir)) {
                swap(field[row][col], field[row + DR[dir]][col + DC[dir]]);
                ret.emplace_back(row, col, row + DR[dir], col + DC[dir]);
                action_count_limit--;
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

    Result solve() {
        // create random moves
        auto moves = move();
        // from each computer, connect to right and/or bottom if it will reach
        // the same type
        auto connects = connect();
        return Result(moves, connects);
    }
};

struct Converter {
    int N = 0;
    Converter(int N) : N(N) {}
    inline int pair_to_id(pair<int,int> p) {
        return p.first*N + p.second;
    }
    inline int id_to_first(int id) {
        return id / N;
    }
    inline int id_to_second(int id) {
        return id % N;
    }
};


int calc_score(int N, vector<string> field, const Result &res) {
    Converter converter(N);
    dsu uf(N*N);

    for(auto r : res.move) {
        assert(field[r.before_row][r.before_col] != '0');
        assert(field[r.after_row][r.after_col] == '0');
        swap(field[r.before_row][r.before_col],
             field[r.after_row][r.after_col]);
    }

    for(auto r : res.connect) {
        pair<int, int> p1(r.c1_row, r.c1_col), p2(r.c2_row, r.c2_col);
        uf.merge(converter.pair_to_id(p1), converter.pair_to_id(p2));
    }

    vector<int> computers;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(field[i][j] != '0') {
                computers.emplace_back(converter.pair_to_id({ i, j }));
            }
        }
    }

    int score = 0;
    for(int i = 0; i < (int)computers.size(); i++) {
        for(int j = i + 1; j < (int)computers.size(); j++) {
            auto c1 = computers[i];
            auto c2 = computers[j];
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

int main() {
    int N, K;
    cin >> N >> K;
    vector<string> field(N);
    for(int i = 0; i < N; i++) {
        cin >> field[i];
    }

    int score_max = 0;
    Result ans{{}, {}};

    mt19937 seed_generator;
    seed_generator.seed(0);

    for(int i = 0; i < 3000; ++i) {
        Solver s(N, K, field, seed_generator());
        auto ret = s.solve();
        int score = calc_score(N, field, ret);
        // int score = 0;
        if(score_max < score) {
            score_max = score;
            cerr << score << endl;
            ans = ret;
        }
    }

    print_answer(ans);

    return 0;
}
