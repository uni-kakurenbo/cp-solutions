#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int x; cin >> x;
    int xs[n]; for(int& v : xs) cin >> v;

    sort(xs, xs + n);

    int ans = 0;
    ans += min(abs(x - xs[0]), abs(x - xs[n-1]));
    ans += xs[n-1] - xs[0];
    cout << ans << "\n";
}
