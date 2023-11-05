/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
/* #region template */
#include <bits/stdc++.h>
#include "template.hpp"
/* #endregion */

constexpr int N = 200, M = 10, K = N / M;

inline void move(const int id, const int to = -1) {
    print(id + 1, to + 1);
    return;
}

struct storage {
    std::array<std::vector<i64>, M> data;
    std::array<spair<int>, N> address;
    int removed = 0;
    int energy = 0;

    void read() {
        ITRR(stk, this->data) stk.resize(K), stk.reserve(3 * K);
        input >> this->data;
        REP(i, M) REP(j, K) this->address[--this->data[i][j]] = { i, j };
    }

    inline int stack(int id = 0) const { return address[id].first; }
    inline int pos(int id = 0) const { return address[id].second; }

    inline bool is_top(int id) const {
        return std::ranges::ssize(data[this->stack(id)]) == this->pos(id) + 1;
    }

    template<bool SYNC = false>
    void move(int id) {
        assert(id == this->removed);
        assert(0 <= this->stack(id) && this->stack(id) < M);
        assert(this->is_top(id));

        this->data[this->stack(id)].pop_back();
        this->address[id] = { -1, -1 };
        ++this->removed;

        if constexpr(SYNC) {
            ::move(id);
        }
    }

    template<bool SYNC = false>
    int move(int id, int to) {
        assert(0 <= id && id < N);
        assert(0 <= to && to < M);
        assert(0 <= this->stack(id) && this->stack(id) < M);
        assert(this->stack(id) != to);

        auto& stk = data[this->stack(id)];
        const int p = this->pos(id);
        const int sz = std::ranges::ssize(stk);

        this->energy += sz - p + 1;
        REP(i, p, sz) {
            this->address[stk[i]] = { to, std::ranges::ssize(this->data[to]) };
            this->data[to].emplace_back(stk[i]);
        }

        stk.erase(std::ranges::begin(stk) + p, std::ranges::end(stk));

        // debug(this->data);

        if constexpr(SYNC) {
            ::move(id, to);
        }

        return this->pos(id);
    }

    int above(const int id) const {
        if(this->is_top(id)) return -1;
        return this->data[this->stack(id)][this->pos(id) + 1];
    }

    int smallest(const int ignore = -1) const {
        int res, min = N + 1;
        REP(i, M) {
            if(ignore == i) continue;
            if(chmin(min, std::ranges::ssize(this->data[i]))) {
                res = i;
            }
        }
        return res;
    }

    inline int score() const {
        return 10'000 - this->energy;
    }

    inline const auto& _debug() const { return this->data; }
};

storage STORAGE;

signed main() {
    {
        [[maybe_unused]] int n, m; input >> n >> m;
    }

    STORAGE.read();
    debug(STORAGE);

    while(STORAGE.removed < N) {
        const int id = STORAGE.removed;
        debug(id, STORAGE.address[id], STORAGE.above(id));
        if(STORAGE.is_top(id)) {
            STORAGE.move<true>(id);
            continue;
        }
        STORAGE.move<true>(STORAGE.above(id), STORAGE.smallest(STORAGE.stack(id)));
        // break;
    }

    debug(STORAGE.score());
}
