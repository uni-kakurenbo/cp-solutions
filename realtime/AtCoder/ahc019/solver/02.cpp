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

field F0, F1, R0, R1;
field Can0, Can1;
std::vector<size_t> LF0, LR0, LF1, LR1;

void init() {
    {
        std::cin >> D;
        S = D*D;
        V = D*D*D;
    }
    {
        std::vector<std::string> v(D);
        input >> v; sol::F0 = v;
        input >> v; sol::R0 = v;
        input >> v; sol::F1 = v;
        input >> v; sol::R1 = v;
        debug(sol::F0, sol::R0, sol::F1, sol::R1);
    }
    {
        Can0 = field(V), Can1 = field(V);
        LF0.assign(S, -1), LR0.assign(S, -1);
        LF1.assign(S, -1), LR1.assign(S, -1);
    }
}

void solve() {
    {
        REP(x, D) REP(y, D) REP(z, D) {
            if(F0[{ z, x }] and R0[{ z, y }]) {
                Can0.set(point3d{ x, y, z }.id());
                chmax(LF0[z*D + x], y), chmax(LR0[z*D + y], x);
            }
            if(F1[{ z, x }] and R1[{ z, y }]) {
                Can1.set(point3d{ x, y, z }.id());
                chmax(LF1[z*D + x], y), chmax(LR1[z*D + y], x);
            }
        }
        debug(Can0); debug(Can1);
        debug(LF0); debug(LR0);
        debug(LF1); debug(LR1);
    }

    std::vector<size_t> res0(V), res1(V);
    size_t n0 = 0, n1 = 0;
    {
        std::vector<size_t> id0(V, -1), id1(V, -1);
        REP(z, D) REP(x, D) {
            size_t p = z*D + x;
            if(LF0[p] >= 0) {
                size_t q = point3d{ x, LF0[p], z}.id();
                if(id0[q] < 0) id0[q] = ++n0;
                res0[q] = id0[q];
            }
            if(LF1[p] >= 0) {
                size_t q = point3d{ x, LF1[p], z}.id();
                if(id1[q] < 0) id1[q] = ++n1;
                res1[q] = id1[q];
            }
        }
        REP(z, D) REP(y, D) {
            size_t p = z*D + y;
            if(LR0[p] >= 0) {
                size_t q = point3d{ LR0[p], y, z}.id();
                if(id0[q] < 0) id0[q] = ++n0;
                res0[q] = id0[q];
            }
            if(LR1[p] >= 0) {
                size_t q = point3d{ LR1[p], y, z}.id();
                if(id1[q] < 0) id1[q] = ++n1;
                res1[q] = id1[q];
            }
        }
    }

    print(std::max(n0, n1));
    print(res0);
    print(res1);
}

}

signed main () {
    sol::init();
    sol::solve();
}
