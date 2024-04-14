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
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "numeric/boundary_seeker.hpp"

void solve() {
    string P = "abcdefghijklmnopqrstuvwxyz";

    i64 n; input >> n;
    string s, t; input >> s >> t;
    i128 sz = std::ranges::ssize(s);

    lib::counter cnt(s);
    debug(cnt);

    lib::inverse<char> inv(s + s + s);
    debug(inv);

    lib::gp_hash_table<char, lib::compressed<i32>> comp;
    ITR(c, is, inv) {
        comp[c] = lib::compressed<i32>(is);
    }
    debug(comp);

    auto find = [&](char x, i128 f, i128 k) -> i128 {
        if(!cnt.contains(x)) return -1;
        k -= 1;

        i128 prev = f / sz;
        f -= prev * sz;

        int rnk = comp[x].rank(f);
        k += rnk;

        i128 base = k / cnt[x];
        k -= cnt[x] * base;

        i128 pos = comp[x].value(k);

        return (prev + base) * sz + pos;
    };

    auto ok = [&](i128 k) -> bool {
        debug_("===============");
        debug(k);

        i128 cur = 0;

        ITR(v, t) {
            debug(v, cur, k);
            i128 nxt = find(v, cur, k);
            debug(nxt);
            if(nxt == -1) return false;
            cur = nxt + 1;
        }

        return cur <= sz * n;
    };

    lib::boundary_seeker<i128> seeker(ok);
    print(seeker.bound(0, INF64));
}
