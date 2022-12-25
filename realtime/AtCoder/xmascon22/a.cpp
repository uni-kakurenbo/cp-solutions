/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */

#include "random/xorshift.hpp"
#include "random/generator.hpp"

using Point = complex<int>;

struct Grid {
    array<array<bool,500>,500> data;
    vector<string> history;

    Grid() { REP(i, 500) this->data[i].fill(false); }

    void read() {
        REP(i, 500) REP(j, 500) {
            char c; cin >> c;
            data[i][j] = c == '#';
        }
    }

    void drop(Point point, int d, bool c) {
        stringstream ss;
        ss << "drop " << point.real() << " " << point.imag() << " " << d << (c ? " 255 255 255" : " 0 0 0");
        history.push_back(ss.str());

        Grid nxt;
        REP(i, 500) REP(j, 500) {
            Point p = { i , j };
            Point q = p == point ? p : point + (int)sqrt(1 + (ld)d*d / (1.0 *(point.real() - p.real())*((point.real() - p.real())) + 1.0 *(point.imag() - p.imag())*((point.imag() - p.imag())))) * (p - point);
            // debug(p.real(), p.imag());
            // debug(q.real(), q.imag());
            if(q.real() < 0 or q.real() >= 500 or q.imag() < 0 or q.imag() >= 500) continue;
            nxt.data[q.real()][q.imag()] = this->data[i][j];
        }

        REP(i, 500) REP(j, 500) {
            if(hypot((ld)point.real() - i, (ld)point.imag() - j) <= d) {
                nxt.data[i][j] = c;
            }
        }

        this->data = nxt.data;
    }

    int diff(const Grid &grid) {
        int diff = 0;
        REP(i, 500) REP(j, 500) {
            diff += abs(grid.data[i][j] - this->data[i][j]);
        }
        return diff;
    }

    string _debug() const {
        string res;
        REP(i, 500) {
            REP(j, 500) res += this->data[i][j] ? '#' : '.';
            res += "\n";
        }
        return res;
    }
};

using namespace Lib;

signed main() {
    int w, h, n; cin >> w >> h >> n;

    Grid goal; goal.read();

    RandomEngine<XorShift> random;

    Grid best;
    int best_diff = INT32_MAX;
    REP(trial, 5) {
        debug(trial, best_diff);
        Grid cur;
        int c_diff = INT32_MAX;
        REP(i, 500) {
            auto cpd = best;
            cpd.drop({ random(500), random(500) }, random(1, 300), (bool)random(2));
            int diff = goal.diff(cpd);
            if(diff < c_diff) {
                c_diff = diff;
                cur = cpd;
            }
        }
        if(c_diff < best_diff) {
            best_diff = c_diff;
            best = cur;
        }
        debug(best);
    }

    REP(i, best.history.size()) {
        print(best.history[i]);
    }

    return 0;
}
