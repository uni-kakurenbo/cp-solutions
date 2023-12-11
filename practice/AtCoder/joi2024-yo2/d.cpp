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

#include "data_structure/segment_tree.hpp"
#include "algebraic/bit_and.hpp"

void solve() {
    int n; input >> n;
    lib::grid<int> G(n, n);
    REP(i, n) REP(j, n) {
        char v; input >> v;
        if(v == 'R') G(i, j) = 0;
        if(v == 'Y') G(i, j) = 1;
        if(v == 'B') G(i, j) = 2;
    }
    debug(G);

    valarray<vector<int>> p(2 * n - 1), q(2 * n - 1);
    REP(i, n) REP(j, n) {
        int pi = i + j;
        p[pi].push_back(G(i, j));
    }
    REPD(i, n) REP(j, n) {
        int qi = (n - i - 1) + j;
        q[qi].push_back(G(i, j));
    }

    debug(p);
    debug(q);

    using tree = lib::segment_tree<lib::algebraic::bit_and<bool>>;
    valarray<std::array<tree, 3>> P(2 * n - 1), Q(2 * n - 1);
    REP(i, 2 * n - 1) REP(v, 3) {
        P[i][v] = tree(p[i].size());
        Q[i][v] = tree(q[i].size());
        REP(j, p[i].size()) {
            P[i][v][j] = (p[i][j] == v);
            Q[i][v][j] = (q[i][j] == v);
        }
    }

    debug(P);
    debug(Q);

    lib::grid<spair<int>> pl(n, n), pr(n, n), ql(n, n), qr(n, n);

    REP(i, n) REP(j, n) {
        int v = G(i, j);

        int pi = i + j;
        int pj = lib::min(i, n - j - 1);
        int qi = (n - i - 1) + j;
        int qj = lib::min(n - i - 1, n - j - 1);

        debug(i, j, v);
        debug(pi, pj);
        debug(qi, qj);
        debug(P[pi][v]);
        debug(Q[qi][v]);

        int _pl = P[pi][v].min_left(pj + 1, [&](auto x) { return x; }) - pj;
        int _pr = P[pi][v].max_right(pj, [&](auto x) { return x; }) - pj - 1;
        int _ql = Q[qi][v].min_left(qj + 1, [&](auto x) { return x; }) - qj;
        int _qr = Q[qi][v].max_right(qj, [&](auto x) { return x; }) - qj - 1;

        pl[i][j] = { std::clamp(i - _pl, 0, n-1), std::clamp(j + _pl, 0, n-1) };
        pr[i][j] = { std::clamp(i + _pr, 0, n-1), std::clamp(j - _pr, 0, n-1) };
        ql[i][j] = { std::clamp(i + _ql, 0, n-1), std::clamp(j + _ql, 0, n-1) };
        qr[i][j] = { std::clamp(i - _qr, 0, n-1), std::clamp(j - _qr, 0, n-1) };
    }

    debug(pl);
    debug(pr);
    debug(ql);
    debug(ql);
    debug(pr);
    debug(pl(4, 8), pr(4, 8), ql(4, 8), qr(4, 8));

    lib::grid<int> cnt(n, n);

    REP(i, n) REP(j, n) {
        int pi = i + j;
        int pj = lib::min(i, n - j - 1);
        int qi = (n - i - 1) + j;
        int qj = lib::min(n - i - 1, n - j - 1);

        spair<int> cand;

        { // pl, ql
            if(ql(pl(i, j)) == pl(ql(i, j))) {
                cand = ql(pl(i, j));
                cnt((cand.first + i) / 2, (cand.second + j) / 2) += std::abs(i - cand.first) * 2;
            }
        }
        { // pl, qr
            if(qr(pl(i, j)) == pl(qr(i, j))) {
                cand = qr(pl(i, j));
                cnt((cand.first + i) / 2, (cand.second + j) / 2) += std::abs(i - cand.first) * 2;
            }
        }
        { // pr, ql
            if(ql(pr(i, j)) == pr(ql(i, j))) {
                cand = ql(pr(i, j));
                cnt((cand.first + i) / 2, (cand.second + j) / 2) += std::abs(i - cand.first) * 2;
            }
        }
        { // pr, qr
            if(qr(pr(i, j)) == pr(qr(i, j))) {
                cand = qr(pr(i, j));
                cnt((cand.first + i) / 2, (cand.second + j) / 2) += std::abs(i - cand.first) * 2;
            }
        }
    }

    i64 ans = 0;
    REP(i, n) REP(j, n) chmax(ans, cnt(i, j));

    debug(ans);
}
