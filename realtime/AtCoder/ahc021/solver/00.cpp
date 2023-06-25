/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

#pragma GCC optimize("O2")

#include "internal/uncopyable.hpp"
#include "timer.hpp"
#include "random/xorshift.hpp"
#include "random/generator.hpp"


namespace lib {


using cost_type = std::int64_t;

using score_type = std::int64_t;
using rating_type = std::int64_t;

lib::random_engine<lib::xorshift> rng;


constexpr int N = 30;
constexpr int M = 465;

struct coord {
    int i = -1, j = -1;

    constexpr coord(int i, int j) noexcept : i(i), j(j) {}

    constexpr int id() const noexcept {
        return this->i * (this->i + 1) / 2 + j;
    }

    inline constexpr coord& operator+=(const coord other) {
        this->i += other.i, this->j += other.j;
        return *this;
    }
    inline constexpr coord& operator-=(const coord other) {
        this->i -= other.i, this->j -= other.j;
        return *this;
    }
    friend inline constexpr coord operator+(coord p, const coord& q) { return p += q; }
    friend inline constexpr coord operator-(coord p, const coord& q) { return p -= q; }

    inline operator bool() const noexcept { return 0 <= this->i and this->i < lib::N and 0 <= this->j and this->j <= this->i; }
};

constexpr coord VICINITIES2[2] = { { 1, 0 }, { 1, 1 } };
constexpr coord VICINITIES6[6] = { { -1, -1 }, { -1, 0 }, { 0, -1 }, { 0, 1 }, { 1, 0 }, { 1, 1 } };

struct operation {
    coord pos;
    int dir;

    operation(const coord& pos, int dir) : pos(pos), dir(dir) {}
};

struct pyramid {
    std::array<int,M> values;

    inline int& operator()(const coord& p) noexcept { return this->values[p.id()]; }
    inline const int& operator()(const coord& p) const noexcept { return this->values[p.id()]; }
    inline const int& operator()(const int i, const int j) const noexcept { return this->values[coord(i, j).id()]; }

    inline auto _debug() const noexcept {
        std::ostringstream res;
        REP(i, N) {
            FOR(j, i) res << this->values[coord(i, j).id()] << " ";
            res << "\n";
        }
        return res.str();
    }

    inline void read() noexcept { input >> this->values; }
};

struct solution {
    std::vector<operation> history;
    pyramid data;

    int error = 0;

    solution(const pyramid& data = {}) noexcept : data(data) {}

    inline rating_type rating() const noexcept { return this->score(); }

    inline score_type score() const noexcept {
        if(this->error == 0) return 100'000 - 5 * this->history.size();
        return 50000 - 50 * this->error;
    }

    friend inline bool operator<(const solution& a, const solution& b) noexcept {
        return a.rating() < b.rating();
    }

    inline int count_error() const noexcept {
        int res = 0;
        REP(i, N-1) FOR(j, i) {
            res += this->data(i, j) > this->data(i+1, j);
            res += this->data(i, j) > this->data(i+1, j+1);
        }
        return res;
    }

    inline void _swap(const coord& pos, const int dir) noexcept {
        const auto trg = pos + VICINITIES2[dir];

        ITR(vic, VICINITIES2) {
            if(pos + vic) this->error -= this->data(pos) > this->data(pos + vic);
            if(pos - vic) this->error -= this->data(pos - vic) > this->data(pos);
            if(trg + vic) this->error -= this->data(trg) > this->data(trg + vic);
            if(trg - vic) this->error -= this->data(trg - vic) > this->data(trg);
        }
        this->error += this->data(pos) > this->data(trg);

        std::swap(this->data(pos), this->data(trg));

        ITR(vic, VICINITIES2) {
            if(pos + vic) this->error += this->data(pos) > this->data(pos + vic);
            if(pos - vic) this->error += this->data(pos - vic) > this->data(pos);
            if(trg + vic) this->error += this->data(trg) > this->data(trg + vic);
            if(trg - vic) this->error += this->data(trg - vic) > this->data(trg);
        }
        this->error -= this->data(pos) > this->data(trg);
    }

    inline void swap(const coord& pos, const int dir) noexcept {
        this->_swap(pos, dir);
        this->history.emplace_back(pos, dir);
    }

    inline operation restore() noexcept {
        assert(not this->history.empty());
        const auto& [ pos, dir] = this->history.back();
        this->_swap(pos, dir);
        this->history.pop_back();
        return { pos, dir };
    }

    inline void read() noexcept {
        this->data.read();
        this->error = this->count_error();
    }

    inline std::string to_string() const noexcept {
        std::ostringstream res;
        res << this->history.size() << "\n";
        ITR(p, dir, this->history) {
            const auto q = p + VICINITIES2[dir];
            res << p.i << " " << p.j << " ";
            res << q.i << " " << q.j << "\n";
        }
        return res.str();
    }


    inline std::string _debug() const noexcept { return this->to_string(); }

    inline void dump() const noexcept {
        debug(this->score(), this->rating());
        debug(*this);
    }

    inline void print() const noexcept {
        std::cout << this->to_string() << std::endl;
    }
};


} // namespace lib


signed main() {
    lib::solution init; init.read();
    lib::timer timer(1800);

    debug(init.score());

    while(not timer.expired()) {
        int i = lib::rng(lib::N - 1);

        auto prev_score = init.score();

        init.swap({ i, lib::rng(0, i) }, lib::rng(2));

        if(prev_score >= init.score()) {
            init.restore();
            assert(prev_score == init.score());
        }
        else {
            debug(init.score());
        }
    }

    debug(init.score());
    init.print();

    return 0;
}
