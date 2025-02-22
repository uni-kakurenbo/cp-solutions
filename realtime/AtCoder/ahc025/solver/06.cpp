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

#include "timer.hpp"

int N, D, Q;
int query_count = 0;

template<std::ranges::range R0, std::ranges::range R1>
int query(const R0& r0, const R1& r1) noexcept {
    cout << std::ranges::size(r0) << " " << std::ranges::size(r1) << " ";
    print << r0 << " " << r1;
    cout << std::endl;

    char res; cin >> res;

    ++query_count;
    debug(query_count, r0, r1, res);

    if(res == '<') return -1;
    if(res == '=') return 0;
    if(res == '>') return 1;

    assert(false);
}

std::vector<std::set<int>> or_less;
std::map<spair<std::vector<int>>,int> memo;

template<std::ranges::range R0, std::ranges::range R1>
int compare(const R0& r0, const R1& r1) noexcept {
    std::vector<int> v0(std::ranges::begin(r0), std::ranges::end(r0));
    std::vector<int> v1(std::ranges::begin(r1), std::ranges::end(r1));

    int rev = 1;

    std::ranges::sort(v0), std::ranges::sort(v1);
    if(v0 == v1) return 0;
    if(v0 > v1) std::swap(v0, v1), rev = -1;

    if(v0.size() == 1 and v1.size() == 1) {
        const int u0 = v0[0], u1 = v1[0];

        std::vector<int> visited(N, false);
        auto search = [&](auto&& search, int v, int s, int t) noexcept -> int {
            if(v == s) visited.assign(N, false);
            if(visited[v]) return false;
            visited[v] = true;
            ITR(nv, or_less[v]) {
                if(v != s) or_less[s].insert(v);
                if(nv == t) return true;
                search(search, nv, s, t);
            }
            return false;
        };
        if(search(search, u0, u0, u1)) return rev;
        if(search(search, u1, u1, u0)) return -rev;
    }

    if(memo.contains({ v0, v1 })) return memo[{ v0, v1 }] * rev;

    const auto res = query(v0, v1);

    if(v0.size() == 1 and v1.size() == 1) {
        const int u0 = v0[0], u1 = v1[0];
        if(res < 0) or_less[u1].insert(u0);
        if(res > 0) or_less[u0].insert(u1);
    }
    return (memo[{ v0, v1 }] = res) * rev;

    assert(false);
}

valarray<int> inds, rank;

signed main() {
    lib::timer timer(1500);

    cin >> N >> D >> Q;
    debug(N, D, Q);

    or_less.resize(N);
    inds.resize(N);
    std::iota(ALL(inds), 0);

    int sorted_successfully = true;
    {
        auto comp = [&](int i, int j) -> bool {
            if(query_count >= Q) {
                sorted_successfully = false;
                return lib::rand() % 2;
            }
            const int res = compare(std::array<int,1>{ i }, std::array<int,1>{ j });
            return res < 0;
        };

        inds.stable_sort(comp);
        debug(inds);
    }

    if(rank.size() == 0) {
        rank.resize(N);
        REP(i, N) rank[inds[i]] = i;
    }
    debug(or_less);

    struct comp_by_order {
        inline bool operator()(const int i, const int j) const noexcept {
            return rank[i] < rank[j];
        }
    };

    valarray<lib::set<int,comp_by_order>> divide(D);
    {
        int i = N;
        while(true) {
            REP(j, D) {
                divide[j].insert(inds[--i]);
                if(i <= 0) break;
            }
            if(i <= 0) break;
            std::ranges::reverse(divide);
        }
    }

    int count = 0;
    while(
        (Q - query_count > 3 * (D - 1) / 2) and
        not timer.expired()
    ) {
        debug(query_count, Q);
        valarray<int> p(D); std::iota(ALL(p), 0);

        {
            valarray<int> ans(N);
            REP(d, D) ITR(v, divide[d]) ans[v] = d;
            print("#c", ans);
        }

        const auto [ min, max ] = std::minmax_element(
            ALL(p),
            [&](int i, int j) {
                if(divide[i].empty()) return true;
                if(divide[j].empty()) return false;
                return compare(divide[i], divide[j]) < 0;
            }
        );

        if(count++ < 3 * D) {
            divide[*min].insert(divide[*max].min());
            divide[*max].erase(divide[*max].begin());
        }
        else {
            int min_diff = INF32;
            int u, v;
            REP(30) {
                const int i = lib::rand() % divide[*min].size();
                const int j = lib::rand() % divide[*max].size();
                auto itr0 = std::next(divide[*min].begin(), i);
                auto itr1 = std::next(divide[*max].begin(), j);
                if(chmin(min_diff, std::abs(rank[*itr0] - rank[*itr1]))) {
                    u = *itr0, v = *itr1;
                }
            }
            debug(min_diff, u, v, rank[u], rank[v]);
            divide[*min].insert(v);
            divide[*max].insert(u);
            divide[*min].remove(u);
            divide[*max].remove(v);
            print("# swap:", u, v);
        }
        debug(divide);
    }
    debug(query_count);

    REP(Q - query_count) {
        cout << "1 1 0 1" << std::endl;
        char _; cin >> _;
    }

    valarray<int> ans(N);
    REP(d, D) ITR(v, divide[d]) ans[v] = d;
    print(ans);
}
