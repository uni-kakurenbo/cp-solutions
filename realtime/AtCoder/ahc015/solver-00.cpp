/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */

#include <bits/stdc++.h>
using namespace std;

/* #expanded [template.hpp] */
#include <iostream>
#ifdef LOCAL_JUDGE
    #include<debug>
    #define debug(...) Debug::debug(Debug::split(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
    #define DEBUG(...) do { Debug::DEBUG(nullptr, "\033[3;35m#" + to_string(__LINE__) + "\033[m  "); Debug::DEBUG(__VA_ARGS__); Debug::DEBUG(nullptr, "\033[m\n"); } while(0);
#else
    #define debug(...) { ; }
    #define DEBUG(...) { ; }
#endif
#define INF32 2147483647
#define INF64 9223372036854775807LL
#define until(...) while(!(__VA_ARGS__))
#define REP(i,n) for(int i=0, i##_length=int(n); i<i##_length; ++i)
#define REPD(i,n) for(auto i=(n)-1; i>=0; --i)
#define LOOP(n) REP($_, (n))
#define FOR(i,l,r) for(auto i=(l), i##_last=(r); i<=i##_last; ++i)
#define FORD(i,l,r) for(auto i=(l), i##_last=(r); i>=i##_last; --i)
#define ITR(x,v) for(const auto &x : (v))
#define ITRP(x,v) for(auto x : (v))
#define ITRR(x,v) for(auto &x : (v))
#define ITRM(x,y,v) for(const auto [x, y] : (v))
#define ITRMP(x,y,v) for(auto [x, y] : (v))
#define ITRMR(x,y,v) for(auto &[x, y] : (v))
#define ALL(x) std::begin((x)),std::end((x))
#define RALL(x) std::rbegin((x)),std::rend((x))
#define $F first
#define $S second
using ll = long long;
using ull = unsigned long long;
using ld = long double;
constexpr char ln = '\n';
constexpr char spc = ' ';
__attribute__((constructor)) inline void fast_io() { std::ios::sync_with_stdio(false), std::cin.tie(nullptr); }
template<class T1, class T2> inline auto mod(T1 x, T2 r) { return (x%r+r)%r; }
template<class T> inline bool chmax(T &a, T b) { return (a<b ? a=b, true : false); }
template<class T> inline bool chmin(T &a, T b) { return (a>b ? a=b, true : false); }
/* [template.hpp] */
/* #expanded [dev_assert.hpp] */
#ifdef LOCAL_JUDGE
    #include <cassert>
    #define dev_assert(...) assert(__VA_ARGS__)
#else
    #define dev_assert(...) ({ ; })
#endif
/* [dev_assert.hpp] */

using Score = ll;
using Candy = short;

template<const int SIZE> using Candies = array<Candy,SIZE*SIZE>;

struct UnionFind {
    using Group = vector<int>;
    using Groups = vector<Group>;

    int N;
    UnionFind(int N) : N(N), parent_or_size(N, -1) {}

    int unite(int a, int b) {
        dev_assert(0 <= a && a < N);
        dev_assert(0 <= b && b < N);
        int x = root(a), y = root(b);
        if (x == y) return x;
        if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    inline bool same(int a, int b) {
        return root(a) == root(b);
    }

    int root(int a) {
        dev_assert(0 <= a && a < N);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = root(parent_or_size[a]);
    }

    int size(int a) {
        dev_assert(0 <= a && a < N);
        return -parent_or_size[root(a)];
    }

    void build_groups(Groups *res) {
        vector<int> roots(N), group_size(N);
        for(int i=0; i<N; ++i) {
            roots[i] = root(i);
            ++group_size[roots[i]];
        }
        res->resize(N);
        for(int i=0; i<N; ++i) (*res)[i].reserve(group_size[i]);
        for(int i=0; i<N; ++i) (*res)[roots[i]].emplace_back(i);
        return;
    }

  private:
    vector<int> parent_or_size;
};

template<const int SIZE>
struct Container {
    // static constexpr int DIS[] = { 1, -1, 0, 0 }, DJS[] = { 0, 0, -1, 1 };

    array<Candy,SIZE*SIZE> buffer;

    Container(initializer_list<Candy> candies) {
        copy(ALL(candies), this->buffer.begin());
    }

    Container() {
        this->buffer.fill(-1);
    }

    const Candy& get(const int p) const {
        dev_assert(0 <= p and p < SIZE*SIZE);
        return buffer[p];
    }
    const Candy& get(const int i, const int j) const {
        dev_assert(0 <= i and i < SIZE), dev_assert(0 <= j and j < SIZE);
        return this->get(i*SIZE+j);
    }

    inline void put(const int p, const int candy) {
        dev_assert(0 <= p and p < SIZE*SIZE);
        dev_assert(0 <= candy and candy < 3);
        buffer[p] = candy;
    }
    inline void put(const int i, const int j, const int candy) {
        dev_assert(0 <= i and i < SIZE), dev_assert(0 <= j and j < SIZE);
        this->put(i*SIZE+j, candy);
    }

    inline void pic(const int p) {
        dev_assert(0 <= p and p < SIZE*SIZE);
        buffer[p] = -1;
    }
    inline void pic(const int i, const int j) {
        dev_assert(0 <= i and i < SIZE), dev_assert(0 <= j and j < SIZE);
        this->pic(i*SIZE+j);
    }

    void tilt(const int dir) {
        if(dir == 0) { // F ↓
            FOR(i, 1, SIZE-1) REP(j, SIZE) {
                int ni = i, nj = j;
                while(
                    ni-1 >= 0 and
                    this->get(ni, nj) >= 0 and this->get(ni-1, nj) == -1
                ) {
                    this->put(ni-1, nj, this->get(ni, nj));
                    this->pic(ni, nj);
                    --ni;
                }
            }
        }
        if(dir == 1) { // B ↑
            REPD(i, SIZE-1) REP(j, SIZE) {
                int ni = i, nj = j;
                while(
                    ni+1 < SIZE and
                    this->get(ni, nj) >= 0 and this->get(ni+1, nj) == -1
                ) {
                    this->put(ni+1, nj, this->get(ni, nj));
                    this->pic(ni, nj);
                    ++ni;
                }
            }
        }
        if(dir == 2) { // L ←
            FOR(j, 1, SIZE-1) REP(i, SIZE) {
                int ni = i, nj = j;
                while(
                    nj-1 >= 0 and
                    this->get(ni, nj) >= 0 and this->get(ni, nj-1) == -1
                ) {
                    this->put(ni, nj-1, this->get(ni, nj));
                    this->pic(ni, nj);
                    --nj;
                }
            }
        }
        if(dir == 3) { // R →
            REPD(j, SIZE-1) REP(i, SIZE) {
                int ni = i, nj = j;
                while(
                    nj+1 < SIZE and
                    this->get(ni, nj) >= 0 and this->get(ni, nj+1) == -1
                ) {
                    this->put(ni, nj+1, this->get(ni, nj));
                    this->pic(ni, nj);
                    ++nj;
                }
            }
        }
    }
    string _debug() const {
        constexpr char VIS[] = { '-', '@', '#', '$' };
        string res = "\n";
        REP(i, SIZE) {
            REP(j, SIZE) {
                res += VIS[this->get(i, j)+1];
            }
            res += "\n";
        }
        return res;
    }
};

template<const int SIZE>
struct Evaluator {
    static constexpr Score BASE_SCORE = 1000000;

    array<int,3> flavor_count;
    Score adjustment;

    Evaluator(const Candies<SIZE> &candies) {
        flavor_count.fill(0);
        ITR(candy, candies) {
            ++this->flavor_count[candy];
        }
        this->adjustment = transform_reduce(ALL(flavor_count), Score{}, plus<Score>{}, [](Score e) { return e*e; });
    }

    Score evaluate(const Container<SIZE> &container) const {
        UnionFind uf(SIZE*SIZE+1);
        REP(i, SIZE) REP(j, SIZE) {
            if(container.get(i,j) == -1) {
                // uf.unite(i*SIZE+j, SIZE*SIZE);
                continue;
            }
            if(i+1 < SIZE and container.get(i,j) == container.get(i+1,j)) uf.unite(i*SIZE+j, (i+1)*SIZE+j);
            if(j+1 < SIZE and container.get(i,j) == container.get(i,j+1)) uf.unite(i*SIZE+j, i*SIZE+(j+1));
        }
        UnionFind::Groups groups;
        uf.build_groups(&groups);
        Score score = 0;
        ITR(group, groups) {
            // debug(group);
            if(group.size() == 0 or uf.same(SIZE*SIZE, group[0])) continue;
            score += group.size()*group.size();
        }
        return score;
        // return -1;
    }

    Score evaluate(const UnionFind::Groups &groups) const {
        Score score = 0;
        ITR(group, groups) {
            score += group.size()*group.size();
        }
        return score;
    }

    Score calc_score(const Container<SIZE>  &container) const {
        return this->evaluate(container) * BASE_SCORE / this->adjustment;
    }
    Score calc_score(const UnionFind::Groups &groups) const {
        return this->evaluate(groups) * BASE_SCORE / this->adjustment;
    }
};

constexpr int SIZE = 10;
constexpr int LENGTH = SIZE*SIZE;

constexpr char DIRCTIONS[] = { 'F', 'B', 'L', 'R' };


signed main() {
    mt19937 engine(998244353);

    Candies<SIZE> fs;
    ITRR(f, fs) cin >> f, --f;

    Evaluator<SIZE> evaluator(fs);
    Container<SIZE> curr_box;

    REP(i, LENGTH) {
        int p; cin >> p;

        int pos = -1;
        {
            int i = 0;
            while(p > 0) {
                if(curr_box.get(i) == -1) --p;
                pos = i++;
            }
        }
        debug(pos);
        curr_box.put(pos, fs[i]);

        Container<SIZE> next_box;
        Score max_score = -1; int max_dir = -1;

        constexpr int DIR[] = { 0, 1, 2, 3 };
        ITR(dir, DIR) {
            auto temp_box = curr_box;
            temp_box.tilt(dir);
            Score temp_score = evaluator.evaluate(temp_box);
            if(temp_score > max_score or (temp_score == max_score and engine()%2 == 0)) {
                max_dir = dir;
                max_score = temp_score;
                next_box = move(temp_box);
            }
        }
        curr_box = move(next_box);
        cout << DIRCTIONS[max_dir] << endl;
        debug(curr_box);
    }

    debug(evaluator.adjustment);
    debug(evaluator.evaluate(curr_box));
    debug(evaluator.calc_score(curr_box));
    debug(curr_box);


    return 0;
}

/*
Candies<5> candies = {
        0, 0, 0, 0, 2,
        0, 0, 0, 0, 2,
        1, 2, 0, 1, 2,
        1, 2, 0, 1, 2,
        2, 1, 1, 1, 1
    };
    Evaluator<5> evaluator(candies);

    Container<5> container = {
       -1, 0, 0, 0, 2,
       -1, 0, 0, 0, 2,
        1, 2, 0, 1, 2,
        1, 2, 0, 1, 2,
        2, 1, 1, 1, 1
    };

    debug(evaluator.evaluate(container));
*/
