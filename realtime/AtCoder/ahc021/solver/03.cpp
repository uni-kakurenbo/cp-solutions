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

    constexpr coord() noexcept {}
    constexpr coord(int i, int j) noexcept : i(i), j(j) {}

    constexpr int id() const noexcept {
        return this->i * (this->i + 1) / 2 + j;
    }

    inline int distance(const coord& other) const noexcept {
        return std::max(std::abs(this->i - other.i), std::abs(this->j - other.j));
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
    friend inline constexpr coord operator-(const coord& p) { return { -p.i, -p.j }; }

    friend inline constexpr bool operator==(const coord& p, const coord& q) { return p.i == q.i and p.j == q.j; }
    friend inline constexpr bool operator!=(const coord& p, const coord& q) { return p.i != q.i or p.j != q.j; }

    inline operator bool() const noexcept { return 0 <= this->i and this->i < lib::N and 0 <= this->j and this->j <= this->i; }

    inline std::pair<int,int> _debug() const noexcept { return { this->i, this->j }; }
};

constexpr coord VICINITIES2[2] = { { 1, 0 }, { 1, 1 } };
constexpr coord VICINITIES6[6] = { { -1, -1 }, { -1, 0 }, { 0, -1 }, { 0, 1 }, { 1, 0 }, { 1, 1 } };

constexpr coord REV[] = { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 0 }, { 2, 1 }, { 2, 2 }, { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 }, { 5, 0 }, { 5, 1 }, { 5, 2 }, { 5, 3 }, { 5, 4 }, { 5, 5 }, { 6, 0 }, { 6, 1 }, { 6, 2 }, { 6, 3 }, { 6, 4 }, { 6, 5 }, { 6, 6 }, { 7, 0 }, { 7, 1 }, { 7, 2 }, { 7, 3 }, { 7, 4 }, { 7, 5 }, { 7, 6 }, { 7, 7 }, { 8, 0 }, { 8, 1 }, { 8, 2 }, { 8, 3 }, { 8, 4 }, { 8, 5 }, { 8, 6 }, { 8, 7 }, { 8, 8 }, { 9, 0 }, { 9, 1 }, { 9, 2 }, { 9, 3 }, { 9, 4 }, { 9, 5 }, { 9, 6 }, { 9, 7 }, { 9, 8 }, { 9, 9 }, { 10, 0 }, { 10, 1 }, { 10, 2 }, { 10, 3 }, { 10, 4 }, { 10, 5 }, { 10, 6 }, { 10, 7 }, { 10, 8 }, { 10, 9 }, { 10, 10 }, { 11, 0 }, { 11, 1 }, { 11, 2 }, { 11, 3 }, { 11, 4 }, { 11, 5 }, { 11, 6 }, { 11, 7 }, { 11, 8 }, { 11, 9 }, { 11, 10 }, { 11, 11 }, { 12, 0 }, { 12, 1 }, { 12, 2 }, { 12, 3 }, { 12, 4 }, { 12, 5 }, { 12, 6 }, { 12, 7 }, { 12, 8 }, { 12, 9 }, { 12, 10 }, { 12, 11 }, { 12, 12 }, { 13, 0 }, { 13, 1 }, { 13, 2 }, { 13, 3 }, { 13, 4 }, { 13, 5 }, { 13, 6 }, { 13, 7 }, { 13, 8 }, { 13, 9 }, { 13, 10 }, { 13, 11 }, { 13, 12 }, { 13, 13 }, { 14, 0 }, { 14, 1 }, { 14, 2 }, { 14, 3 }, { 14, 4 }, { 14, 5 }, { 14, 6 }, { 14, 7 }, { 14, 8 }, { 14, 9 }, { 14, 10 }, { 14, 11 }, { 14, 12 }, { 14, 13 }, { 14, 14 }, { 15, 0 }, { 15, 1 }, { 15, 2 }, { 15, 3 }, { 15, 4 }, { 15, 5 }, { 15, 6 }, { 15, 7 }, { 15, 8 }, { 15, 9 }, { 15, 10 }, { 15, 11 }, { 15, 12 }, { 15, 13 }, { 15, 14 }, { 15, 15 }, { 16, 0 }, { 16, 1 }, { 16, 2 }, { 16, 3 }, { 16, 4 }, { 16, 5 }, { 16, 6 }, { 16, 7 }, { 16, 8 }, { 16, 9 }, { 16, 10 }, { 16, 11 }, { 16, 12 }, { 16, 13 }, { 16, 14 }, { 16, 15 }, { 16, 16 }, { 17, 0 }, { 17, 1 }, { 17, 2 }, { 17, 3 }, { 17, 4 }, { 17, 5 }, { 17, 6 }, { 17, 7 }, { 17, 8 }, { 17, 9 }, { 17, 10 }, { 17, 11 }, { 17, 12 }, { 17, 13 }, { 17, 14 }, { 17, 15 }, { 17, 16 }, { 17, 17 }, { 18, 0 }, { 18, 1 }, { 18, 2 }, { 18, 3 }, { 18, 4 }, { 18, 5 }, { 18, 6 }, { 18, 7 }, { 18, 8 }, { 18, 9 }, { 18, 10 }, { 18, 11 }, { 18, 12 }, { 18, 13 }, { 18, 14 }, { 18, 15 }, { 18, 16 }, { 18, 17 }, { 18, 18 }, { 19, 0 }, { 19, 1 }, { 19, 2 }, { 19, 3 }, { 19, 4 }, { 19, 5 }, { 19, 6 }, { 19, 7 }, { 19, 8 }, { 19, 9 }, { 19, 10 }, { 19, 11 }, { 19, 12 }, { 19, 13 }, { 19, 14 }, { 19, 15 }, { 19, 16 }, { 19, 17 }, { 19, 18 }, { 19, 19 }, { 20, 0 }, { 20, 1 }, { 20, 2 }, { 20, 3 }, { 20, 4 }, { 20, 5 }, { 20, 6 }, { 20, 7 }, { 20, 8 }, { 20, 9 }, { 20, 10 }, { 20, 11 }, { 20, 12 }, { 20, 13 }, { 20, 14 }, { 20, 15 }, { 20, 16 }, { 20, 17 }, { 20, 18 }, { 20, 19 }, { 20, 20 }, { 21, 0 }, { 21, 1 }, { 21, 2 }, { 21, 3 }, { 21, 4 }, { 21, 5 }, { 21, 6 }, { 21, 7 }, { 21, 8 }, { 21, 9 }, { 21, 10 }, { 21, 11 }, { 21, 12 }, { 21, 13 }, { 21, 14 }, { 21, 15 }, { 21, 16 }, { 21, 17 }, { 21, 18 }, { 21, 19 }, { 21, 20 }, { 21, 21 }, { 22, 0 }, { 22, 1 }, { 22, 2 }, { 22, 3 }, { 22, 4 }, { 22, 5 }, { 22, 6 }, { 22, 7 }, { 22, 8 }, { 22, 9 }, { 22, 10 }, { 22, 11 }, { 22, 12 }, { 22, 13 }, { 22, 14 }, { 22, 15 }, { 22, 16 }, { 22, 17 }, { 22, 18 }, { 22, 19 }, { 22, 20 }, { 22, 21 }, { 22, 22 }, { 23, 0 }, { 23, 1 }, { 23, 2 }, { 23, 3 }, { 23, 4 }, { 23, 5 }, { 23, 6 }, { 23, 7 }, { 23, 8 }, { 23, 9 }, { 23, 10 }, { 23, 11 }, { 23, 12 }, { 23, 13 }, { 23, 14 }, { 23, 15 }, { 23, 16 }, { 23, 17 }, { 23, 18 }, { 23, 19 }, { 23, 20 }, { 23, 21 }, { 23, 22 }, { 23, 23 }, { 24, 0 }, { 24, 1 }, { 24, 2 }, { 24, 3 }, { 24, 4 }, { 24, 5 }, { 24, 6 }, { 24, 7 }, { 24, 8 }, { 24, 9 }, { 24, 10 }, { 24, 11 }, { 24, 12 }, { 24, 13 }, { 24, 14 }, { 24, 15 }, { 24, 16 }, { 24, 17 }, { 24, 18 }, { 24, 19 }, { 24, 20 }, { 24, 21 }, { 24, 22 }, { 24, 23 }, { 24, 24 }, { 25, 0 }, { 25, 1 }, { 25, 2 }, { 25, 3 }, { 25, 4 }, { 25, 5 }, { 25, 6 }, { 25, 7 }, { 25, 8 }, { 25, 9 }, { 25, 10 }, { 25, 11 }, { 25, 12 }, { 25, 13 }, { 25, 14 }, { 25, 15 }, { 25, 16 }, { 25, 17 }, { 25, 18 }, { 25, 19 }, { 25, 20 }, { 25, 21 }, { 25, 22 }, { 25, 23 }, { 25, 24 }, { 25, 25 }, { 26, 0 }, { 26, 1 }, { 26, 2 }, { 26, 3 }, { 26, 4 }, { 26, 5 }, { 26, 6 }, { 26, 7 }, { 26, 8 }, { 26, 9 }, { 26, 10 }, { 26, 11 }, { 26, 12 }, { 26, 13 }, { 26, 14 }, { 26, 15 }, { 26, 16 }, { 26, 17 }, { 26, 18 }, { 26, 19 }, { 26, 20 }, { 26, 21 }, { 26, 22 }, { 26, 23 }, { 26, 24 }, { 26, 25 }, { 26, 26 }, { 27, 0 }, { 27, 1 }, { 27, 2 }, { 27, 3 }, { 27, 4 }, { 27, 5 }, { 27, 6 }, { 27, 7 }, { 27, 8 }, { 27, 9 }, { 27, 10 }, { 27, 11 }, { 27, 12 }, { 27, 13 }, { 27, 14 }, { 27, 15 }, { 27, 16 }, { 27, 17 }, { 27, 18 }, { 27, 19 }, { 27, 20 }, { 27, 21 }, { 27, 22 }, { 27, 23 }, { 27, 24 }, { 27, 25 }, { 27, 26 }, { 27, 27 }, { 28, 0 }, { 28, 1 }, { 28, 2 }, { 28, 3 }, { 28, 4 }, { 28, 5 }, { 28, 6 }, { 28, 7 }, { 28, 8 }, { 28, 9 }, { 28, 10 }, { 28, 11 }, { 28, 12 }, { 28, 13 }, { 28, 14 }, { 28, 15 }, { 28, 16 }, { 28, 17 }, { 28, 18 }, { 28, 19 }, { 28, 20 }, { 28, 21 }, { 28, 22 }, { 28, 23 }, { 28, 24 }, { 28, 25 }, { 28, 26 }, { 28, 27 }, { 28, 28 }, { 29, 0 }, { 29, 1 }, { 29, 2 }, { 29, 3 }, { 29, 4 }, { 29, 5 }, { 29, 6 }, { 29, 7 }, { 29, 8 }, { 29, 9 }, { 29, 10 }, { 29, 11 }, { 29, 12 }, { 29, 13 }, { 29, 14 }, { 29, 15 }, { 29, 16 }, { 29, 17 }, { 29, 18 }, { 29, 19 }, { 29, 20 }, { 29, 21 }, { 29, 22 }, { 29, 23 }, { 29, 24 }, { 29, 25 }, { 29, 26 }, { 29, 27 }, { 29, 28 }, { 29, 29 } };

struct operation {
    coord p, q;

    operation(const coord& p, const coord& q) : p(p), q(q) {}
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
    std::array<bool,M> locked = { 0 };


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

    inline void _swap(const coord& pos, const coord& trg) noexcept {
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

    inline coord find(const int v) const noexcept {
        REP(i, lib::N) FOR(j, i) {
            if(this->data(i, j) == v) {
                return { i, j };
            }
        }
        return { -1, -1 };
    }

    inline void swap(const coord& pos, const coord& trg) noexcept {
        this->_swap(pos, trg);
        this->history.emplace_back(pos, trg);
    }
    inline void swap(const coord& pos, const int dir) noexcept {
        this->swap(pos, pos + VICINITIES2[dir]);
    }

    inline coord pull(coord pos) noexcept {
        int val = this->data(pos);
        auto trg = REV[val];

        debug(pos, trg);

        if(pos.i == trg.i) return pos;

        coord found;

        queue<coord> que;
        vector<pair<int,coord>> dists(lib::M, { -1, { -1, -1 } });

        que.push(pos), dists[pos.id()] = { 0, { -1, -1 } };

        {

            while(!que.empty()) {
                auto v = que.front(); que.pop();

                ITR(vic, VICINITIES6) {
                    auto nv = v + vic;

                    if(!nv) continue;
                    if(dists[nv.id()].first >= 0) continue;
                    if(this->locked[nv.id()]) continue;

                    dists[nv.id()] = { dists[v.id()].first + 1, v };

                    if(nv.i == trg.i) {
                        found = nv;
                        goto brk;
                    }

                    que.emplace(nv);
                }
            }
        }

        brk:;

        std::vector<coord> path;
        {
            auto now = found;
            while(now.i >= 0) {
                path.emplace_back(now);
                now = dists[now.id()].second;
                // debug(now);
            }
        }

        std::reverse(ALL(path));
        debug(path);
        REP(i, path.size()-1) this->swap(path[i], path[i+1]);

        return found;
    }

    inline operation restore() noexcept {
        // assert(not this->history.empty());
        const auto& [ pos, dir] = this->history.back();
        this->_swap(pos, pos + VICINITIES2[dir]);
        this->history.pop_back();
        return { pos, pos + VICINITIES2[dir] };
    }

    inline void read() noexcept {
        this->data.read();
        this->error = this->count_error();
    }

    inline std::string to_string() const noexcept {
        std::ostringstream res;
        res << this->history.size() << "\n";
        ITR(p, q, this->history) {
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

    debug(init.score());

    std::array<int,lib::M> dists = { 0 };

    REP(v, lib::M) {
        auto found = init.find(v);
        debug(v, found);
        dists[v] = found.distance(lib::REV[v]);
    }
    debug(dists);

    std::vector<int> inds(lib::M); std::iota(ALL(inds), 0);
    std::sort(ALL(inds), [&](int a, int b) { return dists[a] < dists[b]; });

    debug(inds);

    // ITR(v, inds) {
    //     init.pull(init.find(v));
    // }

    REP(v, lib::M) {
        lib::coord pos;
        const auto q = init.pull(init.find(v));
        init.locked[q.id()] = true;
    }

    debug(init.score());
    init.print();

    return 0;
}
