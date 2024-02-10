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
#include "algebraic/helper.hpp"

struct S {
    i64 len = 0;
    i64 cnt = 0;
    i64 val = 0;
    i64 rev = 0;

    S re() const { return { len, cnt, rev, val }; }
    S() = default;
    S(i64 len, i64 cnt, i64 val, i64 rev) : len(len), cnt(cnt), val(val), rev(rev) {}
    S(i64 len, i64 cnt, i64 val) : S(len, cnt, val, val) {}
    S(i64 len) : len(len), val(len), rev(val) {}

    std::tuple<i64,i64,i64,i64> _debug() const { return { len, cnt, val, rev }; }
};

S e() { return {}; }
S op(S a, S b) {
    return {
        a.len + b.len,
        a.cnt + b.cnt,
        a.val + b.val + b.len * a.cnt,
        a.val + b.val + a.len * b.cnt
    };
}

using monoid = lib::algebraic::monoid_helper<S, op, e>;

void solve() {
    int n; input >> n;
    i64 l; input >> l;
    valarray<i64> p(n); input >> p;
    p.sort();

    lib::segment_tree<monoid> cost(l + 1, S{ 1 });
    ITR(v, p) cost[v] += S{ 0, 1, 1 };
    debug(cost);
    debug(cost.fold(30, 100));

    int q; input >> q;
    REP(q) {
        i64 s, g, t; input >> s >> g >> t;

        S x;
        if(s <= g) {
            x = op(x, p.front() - s);
            if(s <= p.back()) {
                if(s <= p.front()) {
                    if(g <= p.back()) {
                        if(g <= p.front()) {
                            x = op(x, p.back() - p.front());
                            x = op(x, S{ 0, 1, 0 });
                            x = op(x, cost(g, p.back()).fold().val().re());
                        }
                        else {
                            x = op(x, p.back() - p.front());
                            x = op(x, cost(p.front(), g).fold().val());
                            x = op(x, std::abs(p.back() - g));
                            x = op(x, cost(g, p.back()).fold().val().re());
                        }
                    }
                    else {
                        x = op(x, cost(p.front(), g).fold().val());
                    }
                }
                else {
                    if(g <= p.back()) {
                        x = op(x, cost(p.front(), g).fold().val());
                        x = op(x, std::abs(p.back() - g));
                        x = op(x, cost(g, p.back()).fold().val().re());
                    }
                    else {
                        x = op(x, cost(p.front(), g).fold().val());
                    }
                }
            }
            else {
                x = op(x, s - p.front());
                x = op(x, cost(p.front(), p.back()).fold().val());
                x = op(x, g - p.back());
            }
        }
        else {
            if(g <= p.back()) {
                if(g <= p.front()) {
                    if(s <= p.back()) {
                        if(s <= p.front()) {
                            x = op(x, p.front() - s);
                            x = op(x, p.back() - p.front());
                            x = op(x, cost(p.front(), p.back()).fold().val().re());
                            x = op(x, p.front() - g);
                        }
                        else {
                            x = op(x, p.back() - s);
                            x = op(x, cost(p.front(), p.back()).fold().val().re());
                            x = op(x, p.front() - g);
                        }
                    }
                    else {
                        x = op(x, s - p.back());
                        x = op(x, cost(p.front(), p.back()).fold().val().re());
                        x = op(x, p.front() - g);
                    }
                }
                else {
                    if(s <= p.back()) {
                        x = op(x, s - p.back());
                        x = op(x, cost(p.front(), p.back()).fold().val().re());
                        x = op(x, g - p.front());
                    }
                    else {
                        x = op(x, s - p.back());
                        x = op(x, cost(g, p.back()).fold().val().re());
                        x = op(x, g - p.front());
                        x = op(x, cost(g, p.front()).fold().val());
                    }
                }
            }
            else {
                x = op(x, s - p.front());
                x = op(x, cost(p.front(), p.back()).fold().val());
                x = op(x, g - p.back());
            }
        }
        debug(x);

        print.yesno(x.val + n <= t);
    }
}
