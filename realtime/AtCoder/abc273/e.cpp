/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region tmplate */
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL_JUDGE
    #include<debug>
    #define debug(...) Debug::debug(Debug::split(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
    #define DEBUG(...) do { Debug::DEBUG(nullptr, "\033[3;35m#" + to_string(__LINE__) + "\033[m  "); Debug::DEBUG(__VA_ARGS__); Debug::DEBUG(nullptr, "\033[m\n"); } while(0);
#else
    #define debug(...) { ; }
    #define DEBUG(...) { ; }
#endif

#define INF32 2147483647
#define INF64 9223372036854775807LL

#define until(...) while(!(__VA_ARGS__))

#define REP(i,n) for(int i=0, i##_length=int(n); i<i##_length; ++i)
#define REPD(i,n) for(int i=(n)-1; i>=0; --i)
#define LOOP(n) REP(_$, (n))
#define FOR(i,l,r) for(ll i=(l), i##_last=ll(r); i<=i##_last; ++i)
#define FORD(i,l,r) for(ll i=(l), i##_last=ll(r); i>=i##_last; --i)

#define ITRP(x,v) for(auto x : (v))
#define ITRR(x,v) for(auto &x : (v))
#define ITR(x,v) for(const auto &x : (v))
#define ITRMP(x,y,v) for(auto [x, y] : (v))
#define ITRMR(x,y,v) for(auto &[x, y] : (v))
#define ITRM(x,y,v) for(const auto [x, y] : (v))

#define ALL(x) begin((x)),end((x))
#define RALL(x) rbegin((x)),rend((x))

#define $F first
#define $S second

using ll = long long;
using ull = unsigned long long;
using ld = long double;

constexpr char ln = '\n';
constexpr char spc = ' ';

inline void fast_io() { ios::sync_with_stdio(false), cin.tie(nullptr); }

template<class T1, class T2> inline auto mod(T1 x, T2 r) { return (x%r+r)%r; }

template<class T> inline bool chmax(T &a, T b) { return (a<b ? a=b, true : false); }
template<class T> inline bool chmin(T &a, T b) { return (a>b ? a=b, true : false); }

template<class T> auto operator<<(ostream &out, const T &val) -> decltype(val.val(), out)& {
    return out << val.val();
}
/* #endregion */

template<class T, class ID = int, template<class,class> class Storage = unordered_map>
struct RestorableStack {
  private:
    struct Node;
    using NodePtr = shared_ptr<Node>;

    struct Node {
        optional<T> val = nullopt;
        NodePtr parent;
    };

    NodePtr node;
    Storage<ID,NodePtr> storage;

  public:
    RestorableStack() { this->clear(); };

    inline bool empty() const {
        return !node->val.has_value();
    }
    inline bool stored(ID x) const {
        return storage.count(x);
    }

    inline T top() const {
        return node->val.value();
    }
    template<class U> inline auto top_or(U &&v) const {
        return node->val.value_or(v);
    }

    inline void push(T x) {
        node.reset(new Node{x, node});
    }
    inline void pop() {
        node = node->parent;
    }
    inline void save(ID x) {
        storage[x] = node;
    }
    inline void load(ID x) {
        node = storage[x];
    }
    inline void clear() {
        node.reset(new Node{});
    }
};

signed main() {
    fast_io();

    int q; cin >> q;
    RestorableStack<int> A;
    LOOP(q) {
        string query; cin >> query;
        if (query == "ADD") {
            int x; cin >> x; A.push(x);
            cout << A.top() << spc;
        }
        if (query == "DELETE") {
            if(!A.empty()) A.pop();
            cout << A.top_or(-1) << spc;
        }
        if (query == "SAVE") {
            int x; cin >> x; A.save(x);
            cout << A.top_or(-1) << spc;
        }
        if (query == "LOAD") {
            int x; cin >> x;
            A.stored(x) ? A.load(x) : A.clear();
            cout << A.top_or(-1) << spc;
        }
    }

    return 0;
}
