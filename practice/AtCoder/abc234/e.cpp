/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
#include "template"
#include "output"

Output print;

namespace Internal {
    template<class T> T max(T a, T b) { return std::max(a, b); }
    template<class T> T min(T a, T b) { return std::min(a, b); }
}

template<class T, T (*op)(T,T)> struct Apply {
    Apply(T&& v) : _v(v) {}
    template<class U> Apply& operator<<=(U&& val) & noexcept {
        _v = op(_v, forward<U>(val));
        return *this;
    }
    T val() const { return _v; }

  private:
    T _v;
};

template<class T> using Max = Apply<T,Internal::max<T>>;
template<class T> using Min = Apply<T,Internal::min<T>>;

signed main() {
    ll x; cin >> x;

    Min<ll> ans = INF64;

    FOR(inc, -9, 9) {
        FOR(d0, 1, 9) {
            int d = d0;
            ll num = d;
            while(num < x) {
                d += inc;
                if(d < 0 or d > 9) break;
                num *= 10;
                num += d;
            }
            if(num >= x) {
                ans <<= num;
            }
        }
    }

    print(ans);

    return 0;
}
