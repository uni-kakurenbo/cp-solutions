#include "numeric/factorization.hpp"
#include "random/xorshift.hpp"
#include "random/generator.hpp"
#include "template.hpp"

lib::random_engine<lib::xorshift> rnd;

signed main() {
    int n = 10;
    print(n);

    REP(n) {
        ull res = 0;

        do {
            ull p;
            do {
                p = rnd(1, 2000000);
            } while(not lib::is_prime(p));

            ull q;
            do {
                q = rnd(1, 2000000);
            } while(not lib::is_prime(q));

            res = p*p*q;
        } while(res > 9000000000000000000UL);

        print(res);
    }
}
