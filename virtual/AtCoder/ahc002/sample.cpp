#include <bits/stdc++.h>
using namespace std;

// (https://qiita.com/thun-c/items/058743a25c37c87b8aa4)
// を参考にしています。thunderさんに多大なる感謝を…

// Copyright [2021] <Copyright Eita Aoki (Thunder) >
std::random_device rnd;
std::mt19937 mt(rnd());

// 型の定義
using Action = int;
using Actions = std::vector<int>;
using ScoreType = int64_t;
using Output = std::string;

// 定数
constexpr const ScoreType INF = 1000000000LL;
const int TILE_SIZE = 50;
const int DIJ[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
const std::string DIR = "LRUD";

// 好みで変更する
const int64_t TIME_LIMIT = 1900;
const int SEED = 20210325;

// 入力
struct Input
{
    pair<int, int> s;
    vector<vector<int>> tiles;
    vector<vector<int>> ps;

    Input(pair<int, int> s, vector<vector<int>> tiles, vector<vector<int>> ps) : s(s), tiles(tiles), ps(ps) {}
};

// 時間を管理するクラス
struct TimeKeeper
{
private:
    std::chrono::high_resolution_clock::time_point start_time_;
    int64_t time_threshold_;

public:
    // 時間制限をミリ秒単位で指定してインスタンスをつくる。
    TimeKeeper(const int64_t &time_threshold)
        : start_time_(std::chrono::high_resolution_clock::now()), time_threshold_(time_threshold) {}

    // インスタンス生成した時から指定した時間制限を超過したか判断する。
    bool isTimeOver() const
    {
        auto diff = std::chrono::high_resolution_clock::now() - this->start_time_;
        return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() >= time_threshold_;
    }

    // 経過時間をミリ秒単位で返す
    int64_t Time() const
    {
        auto diff = std::chrono::high_resolution_clock::now() - this->start_time_;
        return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
    }
};

// 位置を表す構造体
struct Position
{
    int i_;
    int j_;
    Position(const int i = 0, const int j = 0) : i_(i), j_(j) {}
};

// END_TURN_: 探索を終了するターン<br>
// turn_: 現在のターン<br>
// seen_: タイルを踏んだかどうか<br>
// pos_: 現在位置<br>
// output_: 経路の出力<br>
// steps_: 移動経路の座標<br>
// game_score_: 得点(実際の得点)<br>
// evaluated_score_: 探索上で評価したスコア<br>
// first_action_: 探索木のノートルードで最初に選択した行動<br>
struct TileState
{
private:
    int END_TURN_;
    int turn_;
    std::vector<bool> seen_;
    Position pos_;

public:
    Output output_;
    std::vector<Position> steps_;
    int game_score_;
    ScoreType evaluated_score_;
    Action first_action_;

    TileState(Input &input, int end_turn, pair<int, int> pos)
    {
        int size = 0;
        for (auto &i : input.tiles)
        {
            size = max(size, *max_element(i.begin(), i.end()));
        }
        size++;
        this->END_TURN_ = end_turn;
        this->turn_ = 0;
        this->pos_ = Position(pos.first, pos.second);
        this->seen_ = std::vector<bool>(size, false);
        this->seen_[input.tiles[pos_.i_][pos_.j_]] = true;
        this->output_ = "";
        this->steps_ = std::vector<Position>();
        this->steps_.push_back(this->pos_);
        this->game_score_ = input.ps[pos_.i_][pos_.j_];
        this->evaluated_score_ = game_score_;
        this->first_action_ = -1;
    }

    // [どのゲームでも実装する] : 探索用の盤面評価をする
    void evaluateScore()
    {
        // 探索ではゲーム本来のスコアに別の評価値をプラスするといい探索ができるので、ここに工夫の余地がある。
        this->evaluated_score_ = this->game_score_;
    }

    // [どのゲームでも実装する] : ゲームの終了判定
    bool isDone() const { return this->turn_ == END_TURN_; }

    // [どのゲームでも実装する] : 指定したactionでゲームを1ターン進める
    void advance(Input &input, Action action)
    {
        this->pos_.i_ += DIJ[action][0];
        this->pos_.j_ += DIJ[action][1];
        this->steps_.push_back(Position(this->pos_.i_, this->pos_.j_)); // thunder'sヒィィィント！！ここはもっと簡潔かつ実行速度も高速化できる実装があるよ！
        // advanceは探索中何度も呼ばれるからけっこう改善の効果がでかいかも？
        this->game_score_ += input.ps[this->pos_.i_][this->pos_.j_];
        this->seen_[input.tiles[this->pos_.i_][this->pos_.j_]] = true;
        this->turn_++;
        this->output_.push_back(DIR[action]);
    }

    // [どのゲームでも実装する] : 現在の状況でプレイヤーが可能な行動を全て取得する
    Actions legalActions(Input &input) const
    {
        Actions actions;
        for (int action = 0; action < 4; action++)
        {
            int ni = this->pos_.i_ + DIJ[action][0];
            int nj = this->pos_.j_ + DIJ[action][1];
            if (ni < 0 || ni >= TILE_SIZE || nj < 0 || nj >= TILE_SIZE)
                continue;
            if (this->seen_[input.tiles[ni][nj]])
                continue;
            actions.push_back(action);
        }
        return actions;
    }

    // TODO: まだバグってる...
    // [実装しなくてもよいが実装すると便利] : 現在のゲーム状況を文字列にする
    void toString(Input &input) const
    {
        vector<vector<string>> current_path(TILE_SIZE, vector<string>(TILE_SIZE, "  "));
        // 移動経路に罫線を引く
        auto [i, j] = input.s;
        current_path[i][j] = "@@";
        for (int i = 1; i < this->turn_; i++)
        {
            int h = this->steps_[i].i_;
            int w = this->steps_[i].j_;
            string dir = "";
            dir += this->output_[i - 1];
            dir += this->output_[i];
            // 直前の移動方向 + 今回の移動方向によって引く罫線を決定
            current_path[h][w] = dir == "LL"   ? "━━"
                                 : dir == "LU" ? "┗━"
                                 : dir == "LD" ? "┏━"
                                 : dir == "RR" ? "━━"
                                 : dir == "RU" ? "┛ "
                                 : dir == "RD" ? "┓ "
                                 : dir == "UL" ? "┓ "
                                 : dir == "UR" ? "┏━"
                                 : dir == "UU" ? "┃ "
                                 : dir == "DL" ? "┛ "
                                 : dir == "DR" ? "┗━"
                                 : dir == "DD" ? "┃ "
                                               : "??";
        }
        // 出力パート
        auto isConnectHorizontal = [&](int h, int w)
        {
            return w + 1 < TILE_SIZE && input.tiles[h][w] == input.tiles[h][w + 1];
        };
        auto isConnectVertical = [&](int h, int w)
        {
            return h + 1 < TILE_SIZE && input.tiles[h][w] == input.tiles[h + 1][w];
        };
        for (int h = 0; h < TILE_SIZE; h++)
        {
            for (int w = 0; w < TILE_SIZE; w++)
            {
                if (!isConnectVertical(h, w))
                {
                    // 下のタイルとつながっていなかったら下線を引く
                    fprintf(stderr, "\x1b[4m");
                }
                if (this->seen_[input.tiles[h][w]])
                {
                    // 踏んだタイルなら色を塗る
                    fprintf(stderr, "\x1b[46m");
                }

                fprintf(stderr, "%s", current_path[h][w].c_str());

                if (isConnectHorizontal(h, w))
                {
                    // 右のタイルと繋がっていたら文字修飾を引き継いで空白を出力
                    fprintf(stderr, " ");
                }
                else
                {
                    // 右のタイルと繋がっていなかったら修飾をリセットして|を出力
                    fprintf(stderr, "\x1b[0m");
                    fprintf(stderr, "|");
                }
            }
            fprintf(stderr, "\n");
        }
        fprintf(stderr, "turn : %d\n", this->turn_);
        fprintf(stderr, "score: %d\n", this->game_score_);
    }
};

// [どのゲームでも実装する] : 探索時のソート用に評価を比較する
bool operator<(const TileState &maze_1, const TileState &maze_2)
{
    return maze_1.evaluated_score_ < maze_2.evaluated_score_;
}
bool operator>(const TileState &maze_1, const TileState &maze_2)
{
    return maze_1.evaluated_score_ > maze_2.evaluated_score_;
}
bool operator==(const TileState &maze_1, const TileState &maze_2)
{
    return maze_1.evaluated_score_ == maze_2.evaluated_score_;
}

using State = TileState;

// ランダムに行動を決定する
Action randomAction(Input &input, const State &state)
{
    auto legal_actions = state.legalActions(input);
    if (legal_actions.empty())
    {
        return -1;
    }
    return legal_actions[mt() % (legal_actions.size())];
}

// 貪欲法で行動を決定する
Action greedyAction(Input &input, const State &state)
{
    ScoreType best_score = -INF;
    Action best_action = -1;
    auto legal_actions = state.legalActions(input);
    if (legal_actions.empty())
    {
        return best_action;
    }
    for (auto action : legal_actions)
    {
        State now_state = state;
        now_state.advance(input, action);
        now_state.evaluateScore();
        if (now_state.evaluated_score_ > best_score)
        {
            best_score = now_state.evaluated_score_;
            best_action = action;
        }
    }
    return best_action;
}

// ビーム幅と深さを指定してビームサーチで行動を決定する
Action beamSearchAction(Input &input, const State &state, const int beam_width, const int beam_depth)
{
    auto legal_actions = state.legalActions(input);
    State best_state = state;
    std::priority_queue<State> now_beam;
    now_beam.push(state);

    for (int t = 0; t < beam_depth; t++)
    {
        std::priority_queue<State> next_beam;

        for (int i = 0; i < beam_width; i++)
        {
            if (now_beam.empty())
                break;
            State now_state = now_beam.top();
            now_beam.pop();
            auto legal_actions = now_state.legalActions(input);

            for (const auto &action : legal_actions)
            {
                State next_state = now_state;
                next_state.advance(input, action);
                next_state.evaluateScore();
                if (t == 0)
                    next_state.first_action_ = action;
                next_beam.push(next_state);
            }
        }

        now_beam = next_beam;
        best_state = now_beam.top();

        if (best_state.isDone())
        {
            break;
        }
    }
    return best_state.first_action_;
}

// ビーム幅と制限時間(ms)を指定してビームサーチで行動を決定する
Action beamSearchActionWithTimeThreshold(Input &input, const State &state, const int beam_width,
                                         const int64_t time_threshold)
{
    auto time_keeper = TimeKeeper(time_threshold);
    auto legal_actions = state.legalActions(input);
    State best_state = state;
    std::priority_queue<State> now_beam;
    now_beam.push(state);

    for (int t = 0;; t++)
    {
        std::priority_queue<State> next_beam;
        for (int i = 0; i < beam_width; i++)
        {
            if (time_keeper.isTimeOver())
            {
                return best_state.first_action_;
            }
            if (now_beam.empty())
                break;
            State now_state = now_beam.top();
            now_beam.pop();
            auto legal_actions = now_state.legalActions(input);
            for (const auto &action : legal_actions)
            {
                State next_state = now_state;
                next_state.advance(input, action);
                next_state.evaluateScore();
                if (t == 0)
                    next_state.first_action_ = action;
                next_beam.push(next_state);
            }
        }

        now_beam = next_beam;
        best_state = now_beam.top();

        if (best_state.isDone())
        {
            break;
        }
    }
    return best_state.first_action_;
}

// ビーム1本あたりのビーム幅とビームの本数を指定してchokudaiサーチで行動を決定する
Action chokudaiSearchAction(Input input, const State &state, const int beam_width, const int beam_depth,
                            const int beam_number)
{
    auto beam = std::vector<std::priority_queue<State>>(beam_depth + 1);
    for (int t = 0; t < beam_depth + 1; t++)
    {
        beam[t] = std::priority_queue<State>();
    }
    beam[0].push(state);

    for (int cnt = 0; cnt < beam_number; cnt++)
    {
        for (int t = 0; t < beam_depth; t++)
        {
            auto &now_beam = beam[t];
            auto &next_beam = beam[t + 1];

            for (int i = 0; i < beam_width; i++)
            {
                if (now_beam.empty())
                    break;
                State now_state = now_beam.top();
                if (now_state.isDone())
                    break;
                now_beam.pop();
                auto legal_actions = now_state.legalActions(input);

                for (const auto &action : legal_actions)
                {
                    State next_state = now_state;
                    next_state.advance(input, action);
                    next_state.evaluateScore();
                    if (t == 0)
                        next_state.first_action_ = action;
                    next_beam.push(next_state);
                }
            }
        }
    }

    for (int t = beam_depth; t >= 0; t--)
    {
        const auto &now_beam = beam[t];
        if (!now_beam.empty())
        {
            return now_beam.top().first_action_;
        }
    }

    return -1;
}

// ビーム1本あたりのビーム幅と制限時間(ms)を指定してchokudaiサーチで行動を決定する
Action chokudaiSearchActionWithTimeThreshold(Input &input, const State &state, const int beam_width,
                                             const int beam_depth, const int64_t time_threshold)
{
    auto time_keeper = TimeKeeper(time_threshold);
    auto beam = std::vector<std::priority_queue<State>>(beam_depth + 1);
    for (int t = 0; t < beam_depth + 1; t++)
    {
        beam[t] = std::priority_queue<State>();
    }
    beam[0].push(state);

    for (;;)
    {
        for (int t = 0; t < beam_depth; t++)
        {
            auto &now_beam = beam[t];
            auto &next_beam = beam[t + 1];

            for (int i = 0; i < beam_width; i++)
            {
                if (now_beam.empty())
                    break;
                State now_state = now_beam.top();
                if (now_state.isDone())
                    break;
                now_beam.pop();
                auto legal_actions = now_state.legalActions(input);

                for (const auto &action : legal_actions)
                {
                    State next_state = now_state;
                    next_state.advance(input, action);
                    next_state.evaluateScore();
                    if (t == 0)
                        next_state.first_action_ = action;
                    next_beam.push(next_state);
                }
            }
        }
        if (time_keeper.isTimeOver())
            break;
    }

    for (int t = beam_depth; t >= 0; t--)
    {
        const auto &now_beam = beam[t];
        if (!now_beam.empty())
        {
            return now_beam.top().first_action_;
        }
    }

    return -1;
}

// 入力の受け取り
Input read_input()
{
    pair<int, int> s;
    vector<vector<int>> tiles(TILE_SIZE, vector<int>(TILE_SIZE));
    vector<vector<int>> ps(TILE_SIZE, vector<int>(TILE_SIZE));

    cin >> s.first >> s.second;
    for (int i = 0; i < TILE_SIZE; i++)
    {
        for (int j = 0; j < TILE_SIZE; j++)
        {
            cin >> tiles[i][j];
        }
    }
    for (int i = 0; i < TILE_SIZE; i++)
    {
        for (int j = 0; j < TILE_SIZE; j++)
        {
            cin >> ps[i][j];
        }
    }

    return Input(s, tiles, ps);
}

int main()
{
    auto time_keeper = TimeKeeper(TIME_LIMIT);
    Input input = read_input();
    auto state = TileState(input, -1, input.s);
    state.evaluateScore();

    int loop_cnt = 0;
    while (!time_keeper.isTimeOver())
    {
        loop_cnt++;

        // 好きな実装を選択しよう！
        // ハイパーパラメータ(ビーム幅など)は適当です。
        // auto action = randomAction(input, state);
        // auto action = greedyAction(input, state);
        auto action = beamSearchAction(input, state, 50, 100);
        // auto action = beamSearchActionWithTimeThreshold(input, state, 70, 10);
        // auto action = chokudaiSearchAction(input, state, 100, 100, 50);
        // auto action = chokudaiSearchActionWithTimeThreshold(input, state, 3, 3, 20);

        if (action == -1)
            break;
        state.advance(input, action);
        state.evaluateScore();
    }

    cout << state.output_ << endl;

    // debug用
    cerr << loop_cnt << " loops" << endl;
    cerr << time_keeper.Time() << " ms" << endl;
    state.toString(input);
}
