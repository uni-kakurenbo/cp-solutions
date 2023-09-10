#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int r[n]; for(int& v : r) cin >> v;
    reverse(r, r + n);

    int res = 0;
    int mx = 0;
    for(int v : r) {
        if(mx < v) {
            res++;
            mx = v;
        }
    }

    cout << res << "\n";
}
