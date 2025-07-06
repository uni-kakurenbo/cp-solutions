/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "template/warnings.hpp"
void solve() {
    i64 n; input >> n;
    vector<i64> a(n); input >> a;
    a.sort();

    if(n <= 2) {
        print.yes();
        return;
    }

    {
        auto b = a;
        b.unique();

        if(b.size() == 1) {
            print.yes();
            return;
        }
    }

    if(a.contains(0)) {
        vector<i64> v;
        ITR(x, a) if(x != 0) v.push_back(x);

        if(v.size() == 1) {
            print.yes();
            return;
        }

        print.no();
        return;
    }

    {
        bool can = true;
        REP(i, 1, n) {
            if(a[i] * a[0] != a[1] * a[i - 1]) {
                can = false;
                break;
            }
        }

        if(can) {
            print.yes();
            return;
        }
    }

    vector<i64> pos;
    vector<i64> neg;

    ITR(x, a) {
        if(x > 0) pos.push_back(x);
        else neg.push_back(x);
    }

    pos.sort();
    neg.sort().reverse();

    if(pos.size() < neg.size()) {
        std::swap(pos, neg);
    }

    if(pos.size() - neg.size() > 1) {
        print.no();
        return;
    }

    bool f = true;

    chk:

    std::vector<i64> c = { pos[0] };

    REP(i, neg.size()) {
        c.push_back(neg[i]);
        if(i + 1 < pos.size()) c.push_back(pos[i + 1]);
    }

    debug(c);

    {
        bool can = true;
        REP(i, 1, n) {
            if(c[i] * c[0] != c[1] * c[i - 1]) {
                can = false;
                break;
            }
        }

        if(can) {
            print.yes();
            return;
        }
    }

    if(f && pos.size() == neg.size()) {
        std::swap(pos, neg);
        f = false;
        goto chk;
    }

    print.no();

    return;
}
