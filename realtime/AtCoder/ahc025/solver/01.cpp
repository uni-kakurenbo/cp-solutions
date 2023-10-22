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

valarray<int> inds, rank;

signed main() {
    cin >> N >> D >> Q;
    debug(N, D, Q);

    inds.resize(N);
    std::iota(ALL(inds), 0);

    int sorted_successfully = true;
    {
        auto comp = [&](int i, int j) -> bool {
            if(query_count >= Q) {
                sorted_successfully = false;
                return lib::rand() % 2;
            }
            const int res = query(std::array<int,1>{ i }, std::array<int,1>{ j });
            return res < 0;
        };

        inds.stable_sort(comp);
        debug(inds);
    }

    if(rank.size() == 0) {
        rank.resize(N);
        REP(i, N) rank[inds[i]] = i;
    }

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

    REP(Q - query_count) {
        int p, q;
        do {
            p = lib::rand() % D, q = lib::rand() % D;
        } while(p == q or divide[p].size() <= 1 or divide[q].size() <= 1);
        const int res = query(divide[p], divide[q]);
        if(res == 0) continue;
        if(res < 0) std::swap(p, q);
        const int d = sorted_successfully ? 1UL : divide[p].size();
        const int mov = lib::rand() % d;
        const auto itr = std::next(divide[p].begin(), mov);
        // std::cerr << mov << " " << *itr << "\n";
        // std::cerr << divide[p].size() << " " << divide[q].size() << "\n";
        divide[q].insert(*itr);
        divide[p].erase(itr);
        // std::cerr << divide[p].size() << " " << divide[q].size() << "\n";

        debug(divide);
    }

    valarray<int> ans(N);
    REP(d, D) ITR(v, divide[d]) ans[v] = d;
    print(ans);
}
