/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>

#include "template.hpp"
/* #endregion */

#include "numeric/boundary_seeker.hpp"
#include "hash/sequence_hasher.hpp"

signed main() {
    int n; cin >> n;
    string s; cin >> s;
    lib::sequence_hasher hash(ALL(s));

    auto valid = [&](i64 m) -> bool {
        unordered_map<u64,int> mp;
        FORD(i, n-m) mp[hash.subseq(i, m).val()] = i;
        FORD(i, n-m) {
            u64 h = hash.subseq(i, m).val();
            if(not mp.count(h)) continue;
            if(mp[h] <= i - m) return true;
        }
        return false;
    };

    lib::boundary_seeker<int> seeker(valid);

    print(seeker.bound(0, n));
    return 0;
}
