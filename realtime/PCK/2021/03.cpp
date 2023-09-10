#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int a[n]; for(int& v : a) cin >> v;

    int ans = 0;
    int p = 0;
    for(int& v : a) {
        ans += min({ abs(p - v), abs(10 - p) + v, p + abs(10 - v) });
        p = v;
    }

    cout << ans << "\n";
}
