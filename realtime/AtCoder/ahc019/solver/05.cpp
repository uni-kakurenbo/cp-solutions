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

template<class T> struct vector : std::vector<T> {
  private:
    using base = std::vector<T>;

  public:
    using std::vector<T>::vector;

    inline const auto& operator[](const size_t p) const { return this->base::operator[](p); }
    inline auto& operator[](const size_t p) { return this->base::operator[](p); }
    inline const auto& operator[](const point2d& p) const { return this->base::operator[](p.x() * D + p.y()); }
    inline auto& operator[](const point2d& p) { return this->base::operator[](p.x() * D + p.y()); }
    inline const auto& operator[](const point3d& p) const { return this->base::operator[](p.id()); }
    inline auto& operator[](const point3d& p) { return this->base::operator[](p.id()); }
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


size_t unique() {
    static size_t res = 0;
    return res++;
}

struct polycube : vector<point3d> {
    size_t id = unique();
    std::vector<point3d> normalized;

  private:
    void normalize() {
        std::sort(ALL(*this));
        this->erase(std::unique(ALL(*this)), this->end());

        normalized.resize(this->size());
        std::copy(this->begin(), this->end(), this->normalized.begin());

        size_t min_x = INF_SIZE, min_y = INF_SIZE, min_z = INF_SIZE;
        ITR(x, y, z, this->normalized) chmin(min_x, x), chmin(min_y, y), chmin(min_z, z);
        ITRR(x, y, z, this->normalized) x -= min_x, y -= min_y, z -= min_z;

        std::sort(ALL(this->normalized));
    }

  public:
    polycube() { this->normalize(); }
    polycube(const vector<point3d>& v) : vector<point3d>(v) { this->normalize(); }
    polycube(const point3d& v) : vector<point3d>({ v }) { this->normalize(); }

    explicit operator bool() const { return this->size() > 0; }

    polycube& operator+=(const polycube& p) {
        this->reserve(this->size() + p.size());
        std::copy(ALL(p), std::back_inserter(*this));
        this->normalize();
        return *this;
    }
    friend polycube operator+(polycube p, const polycube& q) { return p += q; }

    inline bool equals(const polycube& p) {
        if(this->size() != p.size()) return false;

        size_t max_x = -1, max_y = -1, max_z = -1;
        ITR(x, y, z, this->normalized) chmin(max_x, x), chmin(max_y, y), chmin(max_z, z);

        REP(i, 6) {
            REP(4) {
                std::sort(ALL(this->normalized));
                if(std::equal(ALL(this->normalized), ALL(p.normalized))) return true;
                ITRR(x, y, _, this->normalized) { const size_t t = x; x = max_y - y, y = t; };
                std::swap(max_x, max_y);
            }
            if(i&1) {
                ITRR(_, y, z, this->normalized) { const size_t t = y; y = max_z - z, z = t; };
                std::swap(max_y, max_z);
            }
            else {
                ITRR(x, _, z, this->normalized) { const size_t t = z; z = max_x - x, x = t; };
                std::swap(max_z, max_x);
            }
        }
        return false;
    }
};

template<class T, size_t N> struct multi_collector {
    using value_typ = T;

  private:
    size_t _limit = std::numeric_limits<size_t>::max();

    vector<std::pair<T,std::array<size_t,N>>> _data;

  public:
    inline auto& data() { return _data; }
    inline auto data() const { return _data; }

    inline size_t size() const { return _data.size(); }

    inline auto begin() { return _data.begin(); }
    inline auto begin() const { return _data.begin(); }

    inline auto end() { return _data.end(); }
    inline auto end() const { return _data.end(); }

    inline void limit(const size_t l) { this->_limit = l; }

    struct reference;

    inline reference operator[](const size_t i) { return reference{ this, i }; }

    struct reference {
      private:
        multi_collector *const _super;
        size_t _n;

        inline auto _find(const T& v) {
            REP(itr, _super->begin(), _super->end()) {
                if(_super->_limit <= itr->second[_n]) continue;
                if(itr->first.equals(v)) return itr;
            }
            return _super->end();
        }

      public:
        reference(multi_collector *const super, const size_t n) : _super(super), _n(n) {}

        inline size_t push(const T& v) {
            auto itr = this->_find(v);
            if(itr == _super->end()) {
                _super->_data.emplace_back(v, std::array<size_t,2>{});
                itr = std::prev(_super->end());
            };
            itr->second[_n]++;
            return itr - _super->begin();
        }

        inline bool remove(const T& v) {
            auto itr = this->_find(v);
            if(itr == _super->end()) return false;
            return itr->second[_n]--, true;
        }

        inline size_t count(const T& v) const {
            auto itr = this->_find(v);
            if(itr == _super->end()) return 0;
            return itr->second[_n];
        }

        inline size_t count() const {
            size_t res = 0;
            REP(itr, _super->begin(), _super->end()) {
                res += itr->second[_n];
            }
            return res;
        }
    };
};

using polycube_collector = multi_collector<polycube,2>;

struct cube {
    size_t id, shape;

    cube() : cube(-1, -1) {}
    cube(const size_t id, const size_t shape) : id(id), shape(shape) {}
    cube(const size_t shape) : id(unique()), shape(shape) {}

    inline bool valid() const { return id >= 0; }
    explicit operator bool() const { return id >= 0; }

    std::pair<size_t, size_t> _debug() const { return { id, shape }; }
};

struct field : boost::dynamic_bitset<> {
  private:
    using base = boost::dynamic_bitset<>;

  public:
    using base::dynamic_bitset;
    field(size_t n) : base(n) {}
    field(const vector<std::string>& v) : base(lib::reversed(lib::join(v))) {}

    inline bool operator[](const size_t p) const { return this->base::operator[](p); }
    inline auto operator[](const size_t p) { return this->base::operator[](p); }
    inline bool operator[](const point2d& p) const { return this->base::operator[](p.x() * D + p.y()); }
    inline auto operator[](const point2d& p) { return this->base::operator[](p.x() * D + p.y()); }
    inline bool operator[](const point3d& p) const { return this->base::operator[](p.id()); }
    inline auto operator[](const point3d& p) { return this->base::operator[](p.id()); }

    inline std::string to_string() const { return lib::reversed(boost::lexical_cast<std::string>(*this)); }

    inline std::string _debug() const { return this->to_string(); }
};

std::array<field,2> F, R, Can;
std::array<vector<polycube>,2> Put;
std::array<vector<size_t>,2> L;
polycube_collector Ps;


void init() {
    {
        std::cin >> D;
        S = D*D;
        V = D*D*D;
    }
    {
        vector<std::string> v(D);
        input >> v; sol::F[0] = v;
        input >> v; sol::R[0] = v;
        input >> v; sol::F[1] = v;
        input >> v; sol::R[1] = v;
        debug(sol::F[0], sol::R[0], sol::F[1], sol::R[1]);
    }
    {
        Can[0] = Can[1] = field(V);
        Put[0].assign(V, {}), Put[1].assign(V, {});
        L[0].assign(V, 0), L[1].assign(V, 0);
    }
}

void make_valid() {
    REP(n, 2) {
        REPD(x, D) REP(y, D) REPD(z, D) {
            const point3d p = { x, y, z };
            if(F[n][{ z, x }] and R[n][{ z, y }]) {
                Can[n].set(p.id());
                Ps[n].push(Put[n][p] = p);
            }
        }
    }
    debug(Can[0]); debug(Can[1]);
    debug(Ps);
}

void make_simple_solution() {
    REP(n, 2) REP(z, D) REP(xa, D) REP(ya, D) {
        const point3d pa = { xa, ya, z };
        REP(xb, D) REP(yb, D) {
            const point3d pb = { xb, yb, z };

            if(pa == pb) continue;
            if(!Put[n][pa] or !Put[n][pb]) continue;

            {
                size_t ala = 0, alb = 0;
                REP(i, D) {
                    const point3d qa = { xa, i, z }, qb = { i, yb, z };;
                    if(Put[n][qa]) ala++;
                    if(Put[n][qb]) alb++;
                }
                if(ala < 2 or alb < 2) continue;
            }

            {
                Put[n][pa] = Put[n][pb] = {};
                Ps[n].remove(pa), Ps[n].remove(pb);
            }
            {
                point3d p = { xb, ya, z };
                Ps[n].push(Put[n][p] = p);
            }
        }
    }

    // debug(Put[0]);
    // debug(Put[1]);
}

constexpr point3d ADJ3[] = { { 1, 0 , 0 }, { 0, 1, 0 }, { 0, 0, 1 } };

bool connect(const size_t n) {
    point3d p, q;
    do {
        p = lib::rng(V);
        q = p + ADJ3[lib::rng(3)];
    } while(!Put[n][p] or !q or !Put[n][q]);

    // if(Put[n][p].size() > 1) return false;
    // if(Put[n][q].size() > 1) return false;

    debug(p, Put[n][p]); debug(q, Put[n][q]);

    if(Put[n][p]) Ps[n].remove(Put[n][p]);
    if(Put[n][q]) Ps[n].remove(Put[n][q]);

    const auto block = Put[n][p] + Put[n][q] + point3d{p} + point3d{q};

    ITRR(t, Put[n][p]) Put[n][t] = block;
    ITRR(t, Put[n][q]) Put[n][t] = block;
    Put[n][p] = Put[n][q] = block;

    debug(Put[n][p], Put[n][q]);

    Ps[n].push(block);

    return true;
}

void solve() {
    make_valid();
    make_simple_solution();

    REP(10 * Ps[0].count()) connect(0);
    REP(10 * Ps[1].count()) connect(1);

    debug(Ps);

    size_t Cnt = 0;

    vector<size_t> res[2];
    res[0].assign(V, 0), res[1].assign(V, 0);
    {
        polycube_collector cubes; cubes.limit(1);

        REP(n, 2) {
            REP(p, V) {
                if(!Put[n][p]) continue;
                if(res[n][p]) continue;
                size_t id = cubes[n].push(Put[n][p])+1;

                debug(point3d{p}, Put[n][p]);
                ITR(q, Put[n][p]) {
                    dev_assert(!res[n][q]);
                    res[n][q] = id;
                }
            }
        }

        debug(cubes);

        Cnt = cubes.size();
    }
    debug(Cnt);

    print(Cnt);
    print(res[0]);
    print(res[1]);
}


} // namespace sol

signed main () {
    sol::init();
    sol::solve();
}
