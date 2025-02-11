/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
// #define DEBUGGER_ENABLED

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

#include "template/warnings.hpp"


template <class Monoid>
struct SegmentTree {
  using T = typename Monoid::type;
  int N_, N;
  std::vector<T> dat;

  SegmentTree(const int N_) : N_(N_) {
    assert(N_ > 0);
    N = 1;
    while (N < N_) {
      N <<= 1;
    }
    dat.assign(2 * N - 1, Monoid::identity());
  }

  SegmentTree(const std::vector<T> &dat_) : N_(dat_.size()) {
    assert(N_ > 0);
    N = 1;
    while (N < N_) {
      N <<= 1;
    }
    dat.assign(2 * N - 1, Monoid::identity());
    std::copy(dat_.begin(), dat_.end(), dat.begin() + N - 1);
    for (int i = N - 2; i >= 0; i--) {
      dat[i] = Monoid::merge(dat[2 * i + 1], dat[2 * i + 2]);
    }
  }

  int size() { return N_; }

  void update(int key, T val) {
    assert(0 <= key && key < N_);

    key += N - 1;
    dat[key] = val;

    while (key > 0) {
      key = (key - 1) / 2;
      dat[key] =
          Monoid::merge(dat[2 * key + 1], dat[2 * key + 2]);  // rewrite here
    }
  }

  inline const T &operator[](const int k) const { return dat.at(N - 1 + k); }
  inline T &operator[](const int k) { return dat.at(N - 1 + k); }

  T query(int low, int high) const {
    T left_ret = Monoid::identity(), right_ret = Monoid::identity();
    for (low += N, high += N; low < high; low >>= 1, high >>= 1) {
      if (low & 1) {
        left_ret = Monoid::merge(left_ret, dat[low - 1]);
        low++;
      }
      if (high & 1) {
        high--;
        right_ret = Monoid::merge(dat[high - 1], right_ret);
      }
    }
    return Monoid::merge(left_ret, right_ret);
  }
};

template <typename T>
struct RangeMinQuery {
  using type = std::pair<T, int>;
  static type identity() {
    return std::make_pair(std::numeric_limits<T>::max(), 0);
  }
  static type merge(const type &l, const type &r) { return std::min(l, r); }
};


template <typename T>
struct ManhattanMinimumSpanningTree {
  int n;
  std::vector<std::pair<T, T>> points;
  std::vector<std::tuple<i32, i32, T>> graph;
  T mincost;

  ManhattanMinimumSpanningTree(std::vector<std::pair<T, T>> &points)
      : n(points.size()), points(points) {}

  void line_sweep() {
    std::vector<int> ids(n);
    std::iota(ids.begin(), ids.end(), 0);

    std::sort(ids.begin(), ids.end(), [&](int i, int j) {
      return (points[i].second - points[i].first <
              points[j].second - points[j].first) ||
             (points[i].second - points[i].first ==
                  points[j].second - points[j].first &&
              points[i].second > points[j].second) ||
             (points[i].second - points[i].first ==
                  points[j].second - points[j].first &&
              points[i].second == points[j].second && i > j);
    });

    std::vector<std::tuple<T, T, int>> y_idx;
    for (int i = 0; i < n; i++) {
      int x, y;
      std::tie(x, y) = points[i];
      y_idx.emplace_back(y, x, i);
    }
    std::sort(y_idx.begin(), y_idx.end());

    std::vector<int> idx_to_idx(n);
    for (int i = 0; i < n; i++) {
      idx_to_idx[std::get<2>(y_idx[i])] = i;
    }

    SegmentTree<RangeMinQuery<T>> segt(n);
    for (int i = 0; i < n; i++) {
      auto res = segt.query(idx_to_idx[ids[i]], n);
      if (res != RangeMinQuery<T>::identity()) {
        int idx;
        std::tie(std::ignore, idx) = res;
        T dist = std::abs(points[ids[i]].first - points[idx].first) +
                 std::abs(points[ids[i]].second - points[idx].second);
        graph.emplace_back(ids[i], idx, dist);
      }
      segt.update(
          idx_to_idx[ids[i]],
          std::make_pair(points[ids[i]].first + points[ids[i]].second, ids[i]));
    }
  }

  void create_graph() {
    for (int s = 0; s < 2; s++) {
      for (int t = 0; t < 2; t++) {
        for (int u = 0; u < 2; u++) {
          line_sweep();

          for (auto &p : points) std::swap(p.first, p.second);
        }
        for (auto &p : points) p.first = -p.first;
      }
      for (auto &p : points) p.second = -p.second;
    }
  }
};


#include "graph/manhattan_minimum_spanning_tree.hpp"
#include "graph/shortest_path.hpp"

constexpr i32 M = 1'000'000'000;

void solve() {
    i32 n; input >> n;
    vector<i32> a(n), b(n);
    a.resize(n), b.resize(n);
    input >> uni::views::zip(a, b);

    a.insert(a.begin(), 0);
    b.insert(b.begin(), 0);

    REP(i, 0, M, M / 10) {
        a.push_back(i);
        b.push_back(0);
    }

    REP(i, 0, M, M / 10) {
        a.push_back(0);
        b.push_back(i);
    }

    auto f = [&](auto A, auto B) {
        const i32 N = A.size();

        uni::graph<i64> g(N);

        std::vector<spair<i64>> points(N);
        REP(i, N) points[i] = { A[i], B[i] };

        ManhattanMinimumSpanningTree<i64> edges(points);
        edges.create_graph();
        debug(edges.graph.size());

        ITRP(u, v, w, edges.graph) {
            if(A[v] < A[u] && B[v] > B[u]) continue;
            if(A[u] < A[v] && B[u] > B[v]) continue;
            if(A[v] > A[u] && B[v] < B[u]) continue;
            if(A[u] > A[v] && B[u] < B[v]) continue;

            if(A[u] > A[v] || B[u] > B[v]) std::swap(u, v);

            g.add_edge(u, v, w);
        }

        debug(g.edges().ssize());
        assert(g.edges().ssize() >= N);

        std::priority_queue<std::pair<i64, i32>, std::vector<std::pair<i64, i32>>, std::greater<std::pair<i64, i32>>> pq;
        vector<i32> pv(N, -1);
        vector<i64> used(N, false);

        vector<tuple<i32,i32,i32,i32>> res;

        pq.emplace(0, 0);

        while(!pq.empty()) {
            // debug(pq);
            auto [ c, v ] = pq.top(); pq.pop();

            if(used[v]) continue;
            used[v] = true;

            if(pv[v] >= 0) {
                res.emplace_back(A[pv[v]], B[pv[v]], A[v], B[v]);
            }

            ITR(e, g[v]) {
                if(used[e]) continue;
                // if(ds[e] <= nd) continue;
                pv[e] = v;
                pq.emplace(e.cost, e);
            }
        }

        return std::make_pair(res, pv);
    };

    vector<i32> a1 = a, b1 = b;
    // {
    //     auto [_, pv] = f(a1, b1);
    //     debug(pv);

    //     ITR(v, p, pv | uni::views::enumerate) {
    //         if(p < 0) continue;

    //         if(std::abs(a[p] - a[v]) < std::abs(b[p] - b[v])) {
    //             a1.push_back(a[p]), b1.push_back(b[v]);
    //         }
    //         else {
    //             a1.push_back(a[v]), b1.push_back(b[p]);
    //         }
    //     }
    // }

    auto [res, _] = f(a1, b1);

    print(res.size());
    ITR(row, res) {
        auto [ x0, y0, x1, y1 ] = row;
        // if(x0 > x1 || y0 > y1) std::swap(x0, x1), std::swap(y0, y1);

        // debug(x0, x1, y0, y1);
        assert(x0 <= x1 && y0 <= y1);

        print(x0, y0, x1, y1);
    }
}
