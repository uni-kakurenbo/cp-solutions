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


using size_type = int;
using time_type = int;

using point = std::pair<size_type,size_type>;


namespace global {


size_type K, H, W, N, i0;
time_type T;

std::valarray<std::valarray<bool>> h, v;
std::valarray<std::valarray<std::vector<point>>> next;

point enter;

std::vector<size_type> S, D;

std::valarray<std::valarray<bool>> is_bus;
std::valarray<std::valarray<size_type>> dists;

std::valarray<std::pair<point,time_type>> plant_info;


} // namespace global


template<std::ranges::random_access_range R>
std::string dump_grid(const R& range) {
    assert((size_type)std::ranges::size(range) == global::H);

    std::stringstream res;
    res << "\n";

    REP(row, global::H) {
        assert((size_type)std::ranges::size(range[row]) == global::W);

        res << (global::i0 == row ? " " : "|");
        REP(col, global::W) {
            res << std::setfill('0') << std::right << std::setw(2) << range[row][col];
            res << (col == global::W-1 or global::v[row][col] ? "|" : " ");
        }
        res << "\n";

        res << '|';
        REP(col, global::W) {
            const bool h = (row == global::H - 1 or global::h[row][col]);
            const bool v = (col == global::W - 1 or global::v[row][col]);
            res << (h ? "--" : "  ");

            if(v) res << "|";
            else res << (h ? "-" : " ");
        }
        res << "\n";
    }

    return res.str();
}


void read_input() {
    std::cin >> global::T >> global::H >> global::W >> global::i0;
    global::N = global::H * global::W;
    global::enter = { global::i0, 0 };

    global::h.resize(global::H - 1, std::valarray(false, global::W));
    REP(i, global::H - 1) {
        string s; cin >> s;
        REP(j, global::W) global::h[i][j] = (s[j] == '1');
    }

    global::v.resize(global::H, std::valarray(false, global::W - 1));
    REP(i, global::H) {
        string s; cin >> s;
        REP(j, global::W-1) global::v[i][j] = (s[j] == '1');
    }

    std::cin >> global::K;
    global::S.resize(global::K);
    global::D.resize(global::K);
    REP(i, global::K) std::cin >> global::S[i] >> global::D[i];
}


void construct_graph() {
    global::next.resize(global::H, std::valarray(std::vector<point>{}, global::W));
    REP(i, global::H) REP(j, global::W) {
        if(i + 1 < global::H and !global::h[i][j]) {
            global::next[i][j].emplace_back(i + 1, j);
            global::next[i + 1][j].emplace_back(i, j);
        }
        if(j + 1 < global::W and !global::v[i][j]) {
            global::next[i][j].emplace_back(i, j + 1);
            global::next[i][j + 1].emplace_back(i, j);
        }
    }
}

void culc_distances() {
    global::dists.resize(global::H, std::valarray(-1, global::W));

    queue<point> que;

    que.push(global::enter);
    global::dists[global::enter.first][global::enter.second] = 0;

    while(!que.empty()) {
        auto [ i, j ] = que.front(); que.pop();
        for(auto [ ni, nj ] : global::next[i][j]) {
            if(global::dists[ni][nj] >= 0) continue;

            global::dists[ni][nj] = global::dists[i][j] + 1;
            que.emplace(ni, nj);
        }
    }

    debug(dump_grid(global::dists));
}

void find_bus() {
    std::valarray reachable(std::valarray<bool>(false, global::W), global::H);

    std::set<point> bus;
    size_type reachable_count = 0;

    bus.emplace(global::i0, 0);
    reachable_count = global::next[global::i0][0].size() + 1;
    reachable[global::i0][0] = true;
    ITR(i, j, global::next[global::i0][0]) reachable[i][j] = true;
    debug(reachable_count, global::next[global::i0][0]);

    while(reachable_count < global::N) {
        point new_v;

        {
            spair<size_type> max_rank = { -1, -1 };
            ITR(i, j, bus) {
                ITR(ti, tj, global::next[i][j]) {
                    spair<size_type> rank = { 0, global::next[ti][tj].size() };
                    ITR(vi, vj, global::next[ti][tj]) rank.first += !reachable[vi][vj];
                    if(chmax(max_rank, rank)) new_v = { ti, tj };
                }
            }
        }

        ITR(i, j, global::next[new_v.first][new_v.second]) {
            reachable_count += !reachable[i][j];
            reachable[i][j] = true;
        }
        bus.emplace(new_v);

        // debug(new_v, reachable_count);

        // global::is_bus.resize(global::H, std::valarray<bool>(false, global::W));
        // ITR(i, j, bus) {
        //     global::is_bus[i][j] = true;
        // }
        // debug(dump_grid(global::is_bus));
    }

    global::is_bus.resize(global::H, std::valarray<bool>(false, global::W));
    ITR(i, j, bus) {
        global::is_bus[i][j] = true;
    }

    debug(bus);
    debug(dump_grid(global::is_bus));
}

void schedule() {
    std::valarray<size_type> inds(global::K); std::iota(ALL(inds), 0);
    std::ranges::sort(inds, [&](const size_type i, const size_type j) { return global::D[i] - global::S[i] > global::D[j]- global::S[j]; });

    std::set<point> available;
    REP(i, global::H) REP(j, global::W) if(not global::is_bus[i][j]) available.emplace(i, j);

    std::valarray<std::vector<size_type>> plant_list(global::T + 1), harvest_list(global::T + 1);
    ITR(i, inds) {
        plant_list[global::S[i]].emplace_back(i);
        harvest_list[global::D[i]].emplace_back(i);
    }

    global::plant_info.resize(global::K, { { -1, -1 }, -1 });

    FOR(t, 1, global::T) {
        ITR(i, plant_list[t]) {
            if(available.empty()) break;
            point p;
            size_type min_diff = INF32;
            ITR(q, available) {
                const time_type rest = global::D[i] - t;
                const size_type diff = std::abs(rest - global::dists[q.first][q.second]);
                if(chmin(min_diff, diff)) p = q;
            }
            available.erase(p);
            global::plant_info[i] = { p, t };
        }

        ITR(i, harvest_list[t]) {
            if(global::plant_info[i].second < 0) continue;
            available.emplace(global::plant_info[i].first);
        }
    }

    // debug(global::plant_info);
}

void output() {
    std::vector<std::tuple<size_type,point,time_type>> plan;

    REP(i, global::K) {
        if(global::plant_info[i].second < 0) continue;
        plan.emplace_back(i, global::plant_info[i].first, global::plant_info[i].second);
    }

    // debug(plan);

    std::cout << plan.size() << "\n";
    ITR(k, p, s, plan) {
        std::cout << k+1 << " ";
        std::cout << p.first << " " << p.second << " ";
        std::cout << s << "\n";
    }
}

signed main() {
    debug(__cplusplus);

    read_input();
    construct_graph();

    culc_distances();
    find_bus();

    schedule();

    output();
}
