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
    i64 n; input >> n;
    string s, t; input >> s >> t;

    i64 sz = std::ranges::ssize(s);

    lib::counter cnt(s);
    lib::inverse<char> inv(s + s);

    std::unordered_map<char, lib::compressed<i32>> comp;
    ITR(c, inds, inv) comp[c] = lib::compressed<i32>(inds);

    auto find = [&](char v, i64 f, i64 k) -> i64 {
        i64 ct = cnt[v];
        if(ct == 0) return -1;

        const auto& cp = comp[v];

        i64 prev = f / sz;
        f %= sz;

        k += cp.rank(f);

        i64 base = k / ct;
        k %= ct;

        i64 pos = cp.value(k);

        return (prev + base) * sz + pos;
    };

    auto ok = [&](i64 k) {
        if(k == 0) return true;

        i64 cur = 0;

        ITR(v, t) {
            i64 nxt = find(v, cur, k - 1);
            if(nxt == -1) return false;
            cur = nxt + 1;
        }

        return cur <= n * sz;
    };

    lib::boundary_seeker<i64> seeker(ok);
    print(seeker.bound(0));
}
