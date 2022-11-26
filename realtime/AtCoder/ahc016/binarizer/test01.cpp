/*********************************************
 * 最小二乗法                                *
 *********************************************/
#include <iostream>
#include <string>
#include <valarray>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <numeric>


#include "val_array.hpp"
#include "numeric/matrix.hpp"
#include "iterable/accumulation.hpp"

template<class I, class T = typename std::iterator_traits<I>::value_type, class F = double> T binarize(I first, I last) {
    const int n = std::distance(first, last);
    std::valarray<int> sums(n+1), prod_sums(n+1);
    {
        int index = 0;
        for(auto itr=first; itr!=last; ++itr, ++ index) {
            sums[index+1] = sums[index] + *itr;
            prod_sums[index+1] = prod_sums[index] + index * *itr;
        }
    }

    {
        T val = n / 2;
        while(true) {
            debug(val);
            T sum0 = sums[val];
            T sum1 = sums[n-1] - sums[val];

            if(sum0 <= 0 or sum1 <= 0) {
                val++;
                continue;
            };

            T prod_sum0 = prod_sums[val];
            T prod_sum1 = prod_sums[n-1] - prod_sums[val];

            F ave0 = (F)prod_sum0 / sum0;
            F ave1 = (F)prod_sum1 / sum1;
            // debug(ave0, ave1);

            const int t = ((ave0 + ave1) / 2 + 0.5);
            if(val == t) {
                return t;
            }

            val = t;
        }
    }
}

int main() {

    int h[] = { 4, 7, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 21, 30, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    std::reverse(ALL(h));
    int t = binarize(ALL(h));
    debug(t);
    debug(std::reduce(std::begin(h), std::begin(h)+t));

    return 0;
}
