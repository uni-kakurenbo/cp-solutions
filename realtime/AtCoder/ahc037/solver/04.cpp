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
    long $ = 1;
    // std::cin >> $;
    for(long _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

#include "template/warnings.hpp"


template <class Monoid>
struct SegmentTree {
  using T = typename Monoid::type;
  long N_, N;
  std::vector<T> dat;

  SegmentTree(const long N_) : N_(N_) {
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
    for (long i = N - 2; i >= 0; i--) {
      dat[i] = Monoid::merge(dat[2 * i + 1], dat[2 * i + 2]);
    }
  }

  long size() { return N_; }

  void update(long key, T val) {
    assert(0 <= key && key < N_);

    key += N - 1;
    dat[key] = val;

    while (key > 0) {
      key = (key - 1) / 2;
      dat[key] =
          Monoid::merge(dat[2 * key + 1], dat[2 * key + 2]);  // rewrite here
    }
  }

  inline const T &operator[](const long k) const { return dat.at(N - 1 + k); }
  inline T &operator[](const long k) { return dat.at(N - 1 + k); }

  T query(long low, long high) const {
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
  using type = std::pair<T, long>;
  static type identity() {
    return std::make_pair(std::numeric_limits<T>::max(), 0);
  }
  static type merge(const type &l, const type &r) { return std::min(l, r); }
};


template <typename T>
struct ManhattanMinimumSpanningTree {
  long n;
  std::vector<std::pair<T, T>> points;
  std::vector<std::tuple<i64, i64, T>> graph;
  T mincost;

  ManhattanMinimumSpanningTree(std::vector<std::pair<T, T>> &points)
      : n(points.size()), points(points) {}

  void line_sweep() {
    std::vector<long> ids(n);
    std::iota(ids.begin(), ids.end(), 0);

    std::sort(ids.begin(), ids.end(), [&](long i, long j) {
      return (points[i].second - points[i].first <
              points[j].second - points[j].first) ||
             (points[i].second - points[i].first ==
                  points[j].second - points[j].first &&
              points[i].second > points[j].second) ||
             (points[i].second - points[i].first ==
                  points[j].second - points[j].first &&
              points[i].second == points[j].second && i > j);
    });

    std::vector<std::tuple<T, T, long>> y_idx;
    for (long i = 0; i < n; i++) {
      long x, y;
      std::tie(x, y) = points[i];
      y_idx.emplace_back(y, x, i);
    }
    std::sort(y_idx.begin(), y_idx.end());

    std::vector<long> idx_to_idx(n);
    for (long i = 0; i < n; i++) {
      idx_to_idx[std::get<2>(y_idx[i])] = i;
    }

    SegmentTree<RangeMinQuery<T>> segt(n);
    for (long i = 0; i < n; i++) {
      auto res = segt.query(idx_to_idx[ids[i]], n);
      if (res != RangeMinQuery<T>::identity()) {
        long idx;
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
    for (long s = 0; s < 2; s++) {
      for (long t = 0; t < 2; t++) {
        for (long u = 0; u < 2; u++) {
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

#include "utility/timer.hpp"


constexpr i64 M = 1'000'000'000;

void solve() {
    uni::timer timer(1800);

    i64 n; input >> n;
    vector<i64> a(n), b(n);
    a.resize(n), b.resize(n);
    input >> uni::views::zip(a, b);

    a.insert(a.begin(), 0);
    b.insert(b.begin(), 0);

    {

        std::vector<spair<i64>> points(a.size());
        REP(i, a.size()) points[i] = { a[i], b[i] };
        std::ranges::sort(points);

        REP(i, 0, M, M / 50) {
            if(std::ranges::binary_search(points, std::make_pair(i, 0L))) continue;
            a.push_back(i);
            b.push_back(0);
        }

        REP(i, 0, M, M / 50) {
            if(std::ranges::binary_search(points, std::make_pair(0L, i))) continue;

            a.push_back(0);
            b.push_back(i);
        }
    }


    auto f = [&](auto A, auto B) {
        const i64 N = A.size();

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
            assert(w == std::abs(A[u] - A[v]) + std::abs(B[u] - B[v]));

            g.add_edge(u, v, w);
        }

        debug(g.edges().ssize());
        assert(g.edges().ssize() >= N);

        std::priority_queue<std::tuple<i64, i64, i64, i64>, std::vector<std::tuple<i64, i64, i64, i64>>, std::greater<std::tuple<i64, i64, i64, i64>>> pq;
        vector<i64> pv(N, -1);
        vector<i64> used(N, false);

        vector<tuple<i64,i64,i64,i64>> res;

        pq.emplace(0, 0, 0, -1);

        i64 cost = 0;

        while(!pq.empty()) {
            // debug(pq);
            auto [ c, d, v, p ] = pq.top(); pq.pop();

            if(used[v]) continue;
            used[v] = true;

            if(p >= 0) {
                pv[v] = p;
                cost += c;

                res.emplace_back(A[p], B[p], A[v], B[v]);
            }

            ITR(e, g[v]) {
                if(used[e]) continue;
                pq.emplace(e.cost, d + e.cost, e, v);
            }
        }

        return std::make_tuple(res, pv, cost);
    };

    auto next = [&](auto A, auto B, auto pv) {
        vector<i64> a1 = A, b1 = B;

        std::vector<spair<i64>> points(A.size());
        REP(i, A.size()) points[i] = { A[i], B[i] };
        std::ranges::sort(points);

        vector<vector<i64>> children(A.size());

        ITR(v, p, pv | uni::views::enumerate) {
            if(p < 0) continue;
            children[p].push_back(v);
        }

        ITR(v, cs, children | uni::views::enumerate) {
            if(cs.size() <= 1) continue;

            i64 ma0 = INF32, mb0 = INF32;
            i64 ma1 = INF32, mb1 = INF32;

            ITR(c, cs) {
                if(std::abs(A[c] - A[v]) < std::abs(B[c] - B[v]) || cs.size() <= 2) {
                    chmin(ma0, A[c]), chmin(mb0, B[c]);
                }
                else {
                    chmin(ma1, A[c]), chmin(mb1, B[c]);
                }
            }

            if(ma0 < INF32 && !std::ranges::binary_search(points, std::make_pair(ma0, mb0))) a1.push_back(ma0), b1.push_back(mb0);
            if(ma1 < INF32 && !std::ranges::binary_search(points, std::make_pair(ma1, mb1))) a1.push_back(ma1), b1.push_back(mb1);
        }

        return std::make_pair(a1, b1);
    };

    auto [res, pv, cost] = f(a, b);
    debug(cost);

    while(!timer.expired()) {
        auto [ na, nb ]= next(a, b, pv);
        auto [ n_res, n_pv, n_cost ] = f(na, nb);
        debug(n_cost);

        if(n_cost < cost && na.ssize() < 5 * n) {
            a = na, b = nb;
            res = n_res;
            pv = n_pv;
            cost = n_cost;
        }
        else {
            break;
        }
    }

    print(res.size());
    ITR(row, res) {
        auto [ x0, y0, x1, y1 ] = row;
        // if(x0 > x1 || y0 > y1) std::swap(x0, x1), std::swap(y0, y1);

        // debug(x0, x1, y0, y1);
        assert(x0 <= x1 && y0 <= y1);

        print(x0, y0, x1, y1);
    }
}
