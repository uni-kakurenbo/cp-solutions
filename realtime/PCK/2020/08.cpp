#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;

    valarray<vector<int>> g(n);
    for(int i=0; i<m; ++i) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].push_back(v);
    }

    int INF = 1 << 30;

    for(int i=0; i<n; ++i) {
        valarray<int> dp[2];
        dp[0].resize(n, -1), dp[1].resize(n, -1);
        dp[i == 0][0] = 0;

        for(int v=0; v<n; ++v) {
            for(int f=0; f<2; ++f) {
                if(dp[f][v] < 0) continue;
                for(int nv : g[v]) {
                    bool nf = f | (nv == i);
                    dp[nf][nv] = max(dp[nf][nv], 0) + dp[f][v] + 1;
                }
            }
        }4

        for(int v : dp[0]) cerr << v << " ";
        cerr << "\n";
        for(int v : dp[1]) cerr << v << " ";
        cerr << "\n";

        cout << dp[1][n-1] << "\n";
    }
}
