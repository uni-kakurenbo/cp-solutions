/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */

#ifdef LOCAL_JUDGE

constexpr bool DEVENOPMEMT_MODE = true;

#else

constexpr bool DEVENOPMEMT_MODE = false;

#endif


#include <cstdlib>
#include <cstdint>
#include <cassert>

#include <type_traits>

#include <iostream>
#include <fstream>

#include <vector>
#include <array>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <bitset>
#include <initializer_list>

#include <algorithm>
#include <numeric>
#include <utility>
#include <cmath>
#include <chrono>

#include <boost/dynamic_bitset.hpp>
#include <boost/lexical_cast.hpp>

#include "template.hpp"

#include "internal/uncopyable.hpp"

#include "data_structure/disjoint_set_union.hpp"
#include "iterable/compression.hpp"


namespace sol {

using size_t = std::int32_t;

size_t D, S, V;

using point2d = lib::point<size_t>;

struct point3d : std::tuple<size_t,size_t,size_t> {
  private:
    using base = std::tuple<size_t,size_t,size_t>;

  public:
    using base::tuple;

    point3d() : point3d(-1, -1, -1) {}
    point3d(const size_t id) : point3d(id/S, id%S/D, id%D) {}
    point3d(const base& v) : point3d(std::get<0>(v), std::get<1>(v), std::get<2>(v)) {}
    point3d(const point3d& v) : point3d(v.x(), v.y(), v.z()) {}

    inline size_t& x() { return std::get<0>(*this); }
    inline size_t x() const { return std::get<0>(*this); }

    inline size_t& y() { return std::get<1>(*this); }
    inline size_t y() const { return std::get<1>(*this); }

    inline size_t& z() { return std::get<2>(*this); }
    inline size_t z() const { return std::get<2>(*this); }

    inline bool valid() const {
        return (0 <= x() && x() < D) and (0 <= y() && y() < D) and (0 <= z() && z() < D);
    }
    inline explicit operator bool() const { return this->valid(); }

    inline size_t id() const { return x() * S + y() * D + z(); }

    inline point3d& operator+=(const point3d& rhs) { this->x() += rhs.x(), this->y() += rhs.y(), this->z() += rhs.z(); return *this; }
    inline point3d& operator-=(const point3d& rhs) { this->x() -= rhs.x(), this->y() -= rhs.y(), this->z() -= rhs.z(); return *this; }

    inline point3d& operator+=(size_t v) { this->x() += v, this->y() += v, this->z() += v; return *this; }
    inline point3d& operator-=(size_t v) { this->x() -= v, this->y() -= v, this->z() -= v; return *this; }
    inline point3d& operator*=(size_t v) { this->x() *= v, this->y() *= v, this->z() *= v; return *this; }
    inline point3d& operator/=(size_t v) { this->x() *= v, this->y() *= v, this->z() *= v; return *this; }

    friend inline point3d operator+(const point3d& lhs, const point3d& rhs) { return point3d(lhs) += rhs; }
    friend inline point3d operator-(const point3d& lhs, const point3d& rhs) { return point3d(lhs) -= rhs; }

    friend inline point3d operator+(const point3d& lhs, const size_t& rhs) { return point3d(lhs) += rhs; }
    friend inline point3d operator+(const size_t& lhs, const point3d& rhs) { return point3d(rhs) += lhs; }
    friend inline point3d operator-(const point3d& lhs, const size_t& rhs) { return point3d(lhs) -= rhs; }
    friend inline point3d operator-(const size_t& lhs, const point3d& rhs) { return point3d(rhs) -= lhs; }
    friend inline point3d operator*(const point3d& lhs, const size_t& rhs) { return point3d(lhs) *= rhs; }
    friend inline point3d operator*(const size_t& lhs, const point3d& rhs) { return point3d(rhs) *= lhs; }
    friend inline point3d operator/(const point3d& lhs, const size_t& rhs) { return point3d(lhs) /= rhs; }
    friend inline point3d operator/(const size_t& lhs, const point3d& rhs) { return point3d(rhs) /= lhs; }
};


struct field : boost::dynamic_bitset<> {
  private:
    using base = boost::dynamic_bitset<>;

  public:
    using base::dynamic_bitset;
    field(size_t n) : base(n) {}
    field(const std::vector<std::string>& v) : base(lib::reversed(lib::join(v))) {}

    inline bool operator[](const size_t p) const { return this->base::operator[](p); }
    inline auto operator[](const size_t p) { return this->base::operator[](p); }
    inline bool operator[](const point2d& p) const { return this->base::operator[](p.x() * D + p.y()); }
    inline auto operator[](const point2d& p) { return this->base::operator[](p.x() * D + p.y()); }
    inline bool operator[](const point3d& p) const { return this->base::operator[](p.id()); }
    inline auto operator[](const point3d& p) { return this->base::operator[](p.id()); }

    inline std::string to_string() const { return lib::reversed(boost::lexical_cast<std::string>(*this)); }

    inline std::string _debug() const { return this->to_string(); }
};

field F[2], R[2];
field Can[2];
std::vector<size_t> L[2];

void init() {
    {
        std::cin >> D;
        S = D*D;
        V = D*D*D;
    }
    {
        std::vector<std::string> v(D);
        input >> v; sol::F[0] = v;
        input >> v; sol::R[0] = v;
        input >> v; sol::F[1] = v;
        input >> v; sol::R[1] = v;
        debug(sol::F[0], sol::R[0], sol::F[1], sol::R[1]);
    }
    {
        Can[0] = field(V), Can[1] = field(V);
        L[0].assign(V, 0), L[1].assign(V, 0);
    }
}

void solve() {
    {
        REP(n, 2) {
            REPD(x, D) REP(y, D) REPD(z, D) {
                const point3d p = { x, y, z };
                if(F[n][{ z, x }] and R[n][{ z, y }]) {
                    Can[n].set(p.id());
                }
            }
            REPD(x, D) REP(y, D) REPD(z, D) {
                const point3d p = { x, y, z };
                if(F[n][{ z, x }] and R[n][{ z, y }]) {
                    Can[n].set(p.id());
                }
            }
        }
        debug(Can[0]); debug(Can[1]);
    }

    auto put = Can;
    {
        REP(n, 2) {
            REP(z, D) {
                REP(xa, D) REP(ya, D) {
                    const point3d pa = { xa, ya, z };
                    REP(xb, D) REP(yb, D) {
                        const point3d pb = { xb, yb, z };
                        if(put[n][pa] and put[n][pb]) {
                            size_t ala = 0, alb = 0;
                            REP(i, D) {
                                const point3d qa = { xa, i, z }, qb = { i, yb, z };;
                                if(put[n][qa]) ala++;
                                if(put[n][qb]) alb++;
                            }
                            if(ala >= 2 and alb >= 2) {
                                put[n][pa] = put[n][pb] = false;
                                put[n][point3d{ xb, ya, z }] = true;
                            }
                        }
                    }
                }
            }
        }
    }

    size_t cnt[2] = { 0, 0 };
    std::vector<size_t> res[2];
    res[0].assign(V, 0), res[1].assign(V, 0);
    {
        std::vector<size_t> id[2];
        id[0].assign(V, -1), id[1].assign(V, -1);

        REP(n, 2) REP(p, V) {
            if(put[n][p]) {
                if(id[n][p] < 0) id[n][p] = ++cnt[n];
                res[n][p] = id[n][p];
            }
        }
    }


    print(std::max(cnt[0], cnt[1]));
    print(res[0]);
    print(res[1]);
}

}

signed main () {
    sol::init();
    sol::solve();
}
