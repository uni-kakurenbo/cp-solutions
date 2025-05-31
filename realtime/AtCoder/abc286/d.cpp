/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <cstdint>
#include <vector>
#include <iostream>
#include <ranges>
#include <tr2/dynamic_bitset>

signed main() {
    std::size_t n, x; std::cin >> n >> x;
    std::vector<long> a(n), b(n);
    for(const auto i : std::views::iota(0uz, n)) {
        std::cin >> a[i] >> b[i];
    }

    std::tr2::dynamic_bitset bits(x + 1);

    bits.set(0);

    for(const auto i : std::views::iota(0uz, n)) {
        for(const auto _ : std::views::iota(0l, b[i])) bits |= bits << a[i];
    }

    std::cout << (bits.test(x) ? "Yes" : "No") << "\n";

    return 0;
}
