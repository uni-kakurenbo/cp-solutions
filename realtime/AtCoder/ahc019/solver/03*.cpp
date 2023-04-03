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

#include "random/xorshift.hpp"
#include "random/generator.hpp"

namespace lib {

lib::random_engine<lib::xorshift> rng;

}

namespace sol {

using size_t = std::int32_t;
constexpr size_t INF_SIZE = (std::numeric_limits<size_t>::max() >> 1) - 1;

size_t D, S, V;

using point2d = lib::point<size_t>;

struct point3d : std::tuple<size_t,size_t,size_t> {
  private:
    using base = std::tuple<size_t,size_t,size_t>;

  public:
    using base::tuple;
    using base::operator=;

    point3d() : point3d(-1, -1, -1) {}
    point3d(const size_t id) : point3d(id/S, id%S/D, id%D) {}
    point3d(const base& v) : point3d(std::get<0>(v), std::get<1>(v), std::get<2>(v)) {}

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


} // namespace sol


namespace std {


template <>
struct tuple_size<sol::point3d> : integral_constant<std::size_t,3> {};

template <size_t I>
struct tuple_element<I,sol::point3d> {
  using type = sol::size_t;
};


} // namespace std


namespace sol {


struct polycube : std::vector<point3d> {
  private:
    void normalize() {
        size_t min_x = INF_SIZE, min_y = INF_SIZE, min_z = INF_SIZE;
        ITR(x, y, z, *this) chmin(min_x, x), chmin(min_y, y), chmin(min_z, z);
        ITRR(x, y, z, *this) x -= min_x, y -= min_y, z -= min_z;
    }

  public:
    polycube(const std::vector<point3d>& v) : std::vector<point3d>(v) { normalize(); }
    polycube(const polycube& v) : std::vector<point3d>(ALL(v)) { normalize(); }
    polycube(const point3d& v) : std::vector<point3d>({ v }) { normalize(); }

    polycube& operator+=(const polycube& p) {
        this->reserve(this->size() + p.size());
        std::copy(ALL(p), std::back_inserter(*this));
        return *this;
    }
    friend polycube operator+(polycube p, const polycube& q) { return p += q; }

    friend bool operator==(polycube& p, polycube& q) {
        if(p.size() != q.size()) return false;

        size_t max_x = -1, max_y = -1, max_z = -1;
        ITR(x, y, z, q) chmin(max_x, x), chmin(max_y, y), chmin(max_z, z);

        std::sort(ALL(p));
        REP(i, 6) {
            REP(4) {
                std::sort(ALL(q));
                if(std::equal(ALL(p), ALL(q))) return true;
                ITRR(x, y, _, q) { const size_t t = x; x = max_y - y, y = t; };
                std::swap(max_x, max_y);
            }
            if(i&1) {
                ITRR(_, y, z, q) { const size_t t = y; y = max_z - z, z = t; };
                std::swap(max_y, max_z);
            }
            else {
                ITRR(x, _, z, q) { const size_t t = z; z = max_x - x, x = t; };
                std::swap(max_z, max_x);
            }
        }
        return false;
    }
    friend bool operator!=(polycube& p, polycube& q) { return !(p == q); }
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
size_t N0, N1;
std::vector<size_t> LF0, LR0, LF1, LR1;
std::vector<size_t> L0, L1;
std::set<polycube> P;
std::vector<size_t> P0, P1;

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
        L0.assign(V, 0), L1.assign(V, 0);
        P0.assign(V, -1), P1.assign(V, -1);
    }
}

constexpr point3d ADJ3[] = { { 1, 0 , 0 }, { 0, 1, 0 }, { 0, 0, 1 } };

void connect() {
    auto& L = (N0 < N1 ? L1 : L0);

    point3d p, q;
    do {
        p = lib::rng(V);
        q = p + ADJ3[lib::rng(3)];
    } while(p.valid() and L[p.id()] > 0 and q.valid() and L[q.id()] > 0);

    L[p.id()] = L[q.id()];
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

    {
        size_t n0 = 0, n1 = 0;
        std::vector<size_t> id0(V, -1), id1(V, -1);
        REP(z, D) REP(x, D) {
            const size_t p = z*D + x;
            if(LF0[p] >= 0) {
                point3d q = { x, LF0[p], z };
                if(id0[q.id()] < 0) id0[q.id()] = ++n0;
                L0[q.id()] = id0[q.id()];
                P.emplace(q);
                P0[q.id()] = std::distance(P.begin(), P.find(q));
            }
            if(LF1[p] >= 0) {
                point3d q = { x, LF1[p], z };
                if(id1[q.id()] < 0) id1[q.id()] = ++n1;
                L1[q.id()] = id1[q.id()];
                P.emplace(q);
                P1[q.id()] = std::distance(P.begin(), P.find(q));
            }
        }
        REP(z, D) REP(y, D) {
            const size_t p = z*D + y;
            if(LR0[p] >= 0) {
                point3d q = { LR0[p], y, z };
                if(id0[q.id()] < 0) id0[q.id()] = ++n0;
                L0[q.id()] = id0[q.id()];
                P.emplace(q);
                P0[q.id()] = std::distance(P.begin(), P.find(q));
            }
            if(LR1[p] >= 0) {
                point3d q = { LR1[p], y, z };
                if(id1[q.id()] < 0) id1[q.id()] = ++n1;
                L1[q.id()] = id1[q.id()];
                P.emplace(q);
                P1[q.id()] = std::distance(P.begin(), P.find(q));
            }
        }
        N0 = n0, N1 = n1;
        debug(P);
        debug(P0);
        debug(P1);
    }

    {

    }

    print(std::max(N0, N1));
    print(L0);
    print(L1);
}

}

signed main () {
    sol::init();
    sol::solve();
}
