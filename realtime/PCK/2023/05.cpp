#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int i=0; i<(n); ++i)
#define FOR(i, a, b) for(auto i=(a); i<=(b); ++i)

bool is_prime_f(long n) {
    if(n == 0) return false;
    if(n == 1) return false;
    for(long i=2; i*i<=n; ++i) {
        if(n % i == 0) return false;
    }
    return n;
}

int main() {
    long n; cin >> n;
    constexpr long MAX = 20000;
    valarray<bool> is_prime(true, MAX);
    vector<long> primes;
    is_prime[0] = is_prime[1] = false;
    {
        FOR(i, 2, MAX) {
            if(not is_prime[i]) continue;
            primes.push_back(i);
            for(long j=2*i; j<=MAX; j+=i) is_prime[j] = false;
        }
    }

    // cerr << primes.size() << "\n";

    // for(long p : primes) cerr << p << " ";
    // cerr << "\n";
    // cerr << 2L * 2L * 99824453 << "\n";

    for(long p : primes) {
        REP(t, 2) {
            if(t == 0) {
                long p2 = p * p;
                if(n % p2 != 0) continue;
                if(p == n / p2) continue;
                if(not is_prime_f(n / p2)) continue;
                cout << "Yes\n";
                return 0;
            }
            else {
                if(n % p != 0) continue;
                long q2 = n / p;
                long q = round(sqrt(q2));
                if(q * q != q2) continue;
                if(not is_prime_f(q)) continue;
                if(q == p) continue;
                // cerr << q2 << " " << q << "\n";
                cout << "Yes\n";
                return 0;
            }
        }
    }
    cout << "No\n";
}
