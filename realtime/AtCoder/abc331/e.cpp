/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

int n, m, l;
std::vector<i64> a, b;
std::vector<i64> p, q;

void solve() {
    std::cin >> n >> m >> l;
    a.resize(n), b.resize(m);
    p.resize(n), q.resize(m);

    REP(i, n) std::cin >> a[i];
    REP(i, m) std::cin >> b[i];
    std::iota(ALL(p), 0), std::iota(ALL(q), 0);

    std::unordered_set<i64> ng;
    REP(l) {
        i64 i, j; std::cin >> i >> j; --i, --j;
        ng.insert(i * m + j);
    }
    debug(ng);

    std::ranges::sort(p, [&](int i, int j) { return a[i] > a[j]; });
    std::ranges::sort(q, [&](int i, int j) { return b[i] > b[j]; });
    debug(a, b);
    debug(p, q);

    struct comp {
        inline bool operator()(i64 i, i64 j) const {
            return a[p[i/m]] + b[q[i%m]] < a[p[j/m]] + b[q[j%m]];
        }
    };

    std::priority_queue<i64,std::vector<i64>,comp> que;
    que.push(0);

    std::unordered_set<i64> al;
    while(true) {
        debug(que.size());
        assert(not que.empty());
        i64 ij = que.top(); que.pop();
        i64 i = ij / m;
        i64 j = ij % m;
        i64 v = a[p[i]] + b[q[j]];

        // debug(ij, v, i, j, p[i], q[]);
        if(i < n-1 and not al.contains((i + 1) * m + j)) {
            que.push((i + 1) * m + j);
            al.insert((i + 1) * m + j);
        }
        if(j < m-1 and not al.contains(i * m + (j + 1))) {
            que.push(i * m + (j + 1));
            al.insert(i * m + (j + 1));
        }

        if(ng.contains(p[i] * m + q[j])) continue;

        std::cout << v;
        return;
    }
}
