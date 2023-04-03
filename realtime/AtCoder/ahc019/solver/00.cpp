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

void set_D(const size_t d) {
    D = d;
    S = d*d;
    V = d*d*d;
}

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

void solve() {
    field B0(V), B1(V);
    {
        REP(x, D) REP(y, D) REP(z, D) {
            B0[{ x, y, z }] = F0[{ z, x }] and R0[{ z, y }];
            B1[{ x, y, z }] = F1[{ z, x }] and R1[{ z, y }];
        }
        debug(B0); debug(B1);
    }

    lib::dsu ds0(V), ds1(V);
    {
        REP(i, V) {
            point3d p = i;
            ITR(d, (std::vector<point3d>{ { 0, 0, 1 }, { 0, 1, 0 }, { 1, 0, 0 } })) {
                point3d q = p + d;
                if(!q) continue;
                if(B0[p] and B0[q]) ds0.merge(p.id(), q.id());
                if(B1[p] and B1[q]) ds1.merge(p.id(), q.id());
            }
        }
        debug(ds0.groups()); debug(ds1.groups());
    }

    size_t n = 0;
    std::vector<size_t> res0(V), res1(V);
    {
        std::vector<size_t> id0(V, -1), id1(V, -1);
        REP(p, V) {
            if(B0[p]) {
                size_t l = ds0.leader(p);
                if(id0[l] < 0) id0[l] = ++n;
                res0[p] = id0[l];
            }
            if(B1[p]) {
                size_t l = ds1.leader(p);
                if(id1[l] < 0) id1[l] = ++n;
                res1[p] = id1[l];
            }
        }
        debug(res0); debug(res1);
    }

    print(n);
    print(res0);
    print(res1);
}

}

signed main () {
    sol::size_t D; std::cin >> D;
    sol::set_D(D);
    std::vector<std::string> v(D);
    input >> v; sol::F0 = v;
    input >> v; sol::R0 = v;
    input >> v; sol::F1 = v;
    input >> v; sol::R1 = v;
    debug(sol::F0, sol::R0, sol::F1, sol::R1);
    sol::solve();
}
