#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int i=0; i<(n); ++i)
#define FOR(i, a, b) for(auto i=(a); i<=(b); ++i)

constexpr pair<int,int> DIRS[4] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };

int main() {
    int h, w; cin >> h >> w;
    valarray row(valarray<int>(w-1), h), col(valarray<int>(h-1), w);

    REP(i, h) REP(j, w-1) cin >> row[i][j], row[i][j] %= 3;
    REP(i, w) REP(j, h-1) cin >> col[i][j], col[i][j] %= 3;

    auto id = [&](int i, int j) { return i * w + j; };
    auto can_adv = [&](int i, int j, int d, int t) {
        if(d == 0) return col[j][i] == t;
        if(d == 1) return col[j][i-1] == t;
        if(d == 2) return row[i][j] == t;
        if(d == 3) return row[i][j-1] == t;
        assert(false);
    };

    valarray<long> dists[3];
    REP(i, 3) dists[i].resize(h*w, -1);
    {
        // { (i, j), d }
        queue<pair<int,int>> que;
        que.emplace(id(0, 0), 0);
        dists[0][id(0, 0)] = 0;

        while(not que.empty()) {
            auto [ v, d ] = que.front(); que.pop();
            int i = v / w, j = v % w;
            int nd = (d + 1) % 3;

            // cerr << "(" << i << ", " << j << ") " << d << "\n";

            if(i == h-1 and j == w-1) {
                cout << dists[d][v] << "\n";
                return 0;
            }

            REP(dir, 4) {
                auto [ di, dj ] = DIRS[dir];
                int ni = i + di, nj = j + dj;
                int nv = id(ni, nj);
                if(ni < 0 or nj < 0 or ni >= h or nj >= w) continue;
                if(dists[nd][nv] >= 0) continue;
                if(not can_adv(i, j, dir, nd)) continue;
                dists[nd][nv] = dists[d][v] + 1;
                que.emplace(nv, nd);
            }
        }
    }

    cout << "-1\n";
}
