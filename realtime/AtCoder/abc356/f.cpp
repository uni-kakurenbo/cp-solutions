/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

#include "include/template.hpp"
#include "template/debug.hpp"
using namespace std;

void solve();

int main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "template/warnings.hpp"

// Description: 区間をsetで管理するデータ構造(なお実装はmap)．各クエリO(log区間数)．

using uni::i32;
using uni::i64;

// #### attention! : [l, r] ( include r, not [l, r) )
class SegmentMap : public std::map<i64, i64> {
private:
    bool flagToMergeAdjacentSegment;
public:
    // if merge [l, c] and [c+1, r], set flagToMergeAdjacentSegment to true
    SegmentMap(bool flagToMergeAdjacentSegment) :
        flagToMergeAdjacentSegment(flagToMergeAdjacentSegment) {}
    // __exist -> iterator pair(l, r) (contain p)
    // noexist -> map.end()
    auto get(i64 p) const {
        auto it = upper_bound(p);
        if (it == begin() || (--it)->second < p) return end();
        return it;
    }
    // insert segment [l, r]
    void insert(i64 l, i64 r) {
        auto itl = upper_bound(l), itr = upper_bound(r + flagToMergeAdjacentSegment);
        if (itl != begin()) {
            if ((--itl)->second < l - flagToMergeAdjacentSegment) ++itl;
        }
        if (itl != itr) {
            l = std::min(l, itl->first);
            r = std::max(r, std::prev(itr)->second);
            erase(itl, itr);
        }
        (*this)[l] = r;
    }
    // remove segment [l, r]
    void remove(i64 l, i64 r) {
        auto itl = upper_bound(l), itr = upper_bound(r);
        if (itl != begin()) {
            if ((--itl)->second < l) ++itl;
        }
        if (itl == itr) return;
        int tl = std::min(l, itl->first), tr = std::max(r, std::prev(itr)->second);
        erase(itl, itr);
        if (tl < l) (*this)[tl] = l - 1;
        if (r < tr) (*this)[r + 1] = tr;
    }
    // Is p and q in same segment?
    bool same(i64 p, i64 q) const {
        const auto&& it = get(p);
        return it != end() && it->first <= q && q <= it->second;
    }
};


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

void solve() {
    i64 q, k; input >> q >> k;

    tree<i64, null_type, less<i64>, rb_tree_tag, tree_order_statistics_node_update> set;
    SegmentMap segs(true);

    REP(q) {
        i64 t, x; input >> t >> x;
        if(t == 1) {
            if(set.find(x) != set.end()) {
                set.erase(x);

                auto itr = set.lower_bound(x);
                if(itr != set.end() && itr != set.begin() && *itr - *std::prev(itr) > k) {
                    debug("remove", *std::prev(itr) + 1, *itr - 1);
                    segs.remove(*std::prev(itr) + 1, *itr - 1);
                }
                else if(itr != set.end() && *itr - x <= k) {
                    debug("remove", x, *itr - 1);
                    segs.remove(x, *itr - 1);
                }
                else if(itr != set.begin() && x - *(--itr) <= k) {
                    debug("remove", *itr + 1, x);
                    segs.remove(*itr + 1, x);
                }
            }
            else {
                set.insert(x);
                {
                    auto itr = set.upper_bound(x);
                    if(itr != set.end() && *itr - x <= k) {
                        debug("add", x, *itr);
                        segs.insert(x, *itr);
                    }
                }
                {
                    auto itr = set.lower_bound(x);
                    if(itr != set.begin() && x - *std::prev(itr) <= k) {
                        --itr;
                        debug("add", *itr, x);
                        segs.insert(*itr, x);
                    }
                }
                segs.insert(x, x);
            }
        }
        if(t == 2) {
            if(k == 0) {
                print(1);
            }
            else {
                auto [ l, r ] = *segs.get(x);
                debug(x, l, r);
                assert(set.find(l) != set.end());
                assert(set.find(r) != set.end());
                auto v = set.order_of_key(r) - set.order_of_key(l) + 1;
                print(v);
            }
        }

        debug(segs, set);
    }
}
