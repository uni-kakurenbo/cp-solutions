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

#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

#include <atcoder/segtree>

bool op(bool a, bool b) { return a && b; }
bool e() { return true; }
bool f(bool x) { return x; }

class set_mex {
  int len = 0;
  atcoder::segtree<bool, op, e> seg;
  std::set<int> elts;
  int mex_ = 0;

public:
  set_mex() = default;

  void insert(int i) {
    elts.insert(i);
    if (i < len) {
      seg.set(i, true);
      mex_ = calc_mex();
    }
    while (len == mex_) {
      rebuild(std::max(1, 2 * len));
    }
  }

  void erase(int i) {
    elts.erase(i);
    if (i < len) {
      seg.set(i, false);
    }
    mex_ = calc_mex();
  }

  int mex() {
    return mex_;
  }

private:
  void rebuild(int new_len) {
    len = new_len;
    seg = atcoder::segtree<bool, op, e>(std::vector(new_len, false));
    for (auto i: elts) {
      if (i < new_len) {
        seg.set(i, true);
      }
    }
    mex_  = calc_mex();
  }

  int calc_mex() {
    return seg.max_right<f>(0);
  }
};

void solve() {
    set_mex st;

    int n, q; input >> n >> q;

    map<int,int> cnt;
    valarray<int> a(n);

    REP(i, n) {
        int v; input >> v;
        st.insert(v);
        a[i] = v;
        cnt[v]++;
    }

    REP(q) {
        int i, x; input >> i >> x; --i;
        if(--cnt[a[i]] == 0) st.erase(a[i]);
        a[i] = x;
        if(cnt[x]++ == 0) st.insert(x);
        print(st.mex());
    }
}
