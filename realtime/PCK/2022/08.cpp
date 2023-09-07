#include <bits/stdc++.h>
using namespace std;

int main() {
    int h, w; cin >> h >> w;
    valarray<string> grid(h);
    for(auto& row : grid) cin >> row;

    auto id = [&](int i, int j) { return i * w + j; };

    queue<pair<int,int>> que;
    valarray<int> dists[2];
    dists[0].resize(h * w, -1), dists[1].resize(h * w, -1);

    for(int i=0; i<h; ++i) {
        for(int j=0; j<w; ++j) {
            if(grid[i][j] == 'S') {
                que.emplace(0, id(i, j));
                dists[0][id(i,j)] = 0;
            }
        }
    }

    while(not que.empty()) {
        auto [ f, v ] = que.front(); que.pop();
        int i = v / w, j = v % w;

        if(grid[i][j] == 'G') {
            std::cout << dists[f][id(i, j)] << "\n";
            return 0;
        }

        constexpr std::pair<int,int> DIRS[4] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

        for(int d=0; d<4; ++d) {
            bool nf = f;

            if(
                (grid[i][j] == 'U' and d != 0) or
                (grid[i][j] == 'D' and d != 1) or
                (grid[i][j] == 'L' and d != 2) or
                (grid[i][j] == 'R' and d != 3)
            ) {
                if(f) continue;
                nf = true;
            }

            int ni = i + DIRS[d].first, nj = j + DIRS[d].second;
            if(ni < 0 or ni >= h or nj < 0 or nj >= w) continue;

            if(dists[nf][id(ni, nj)] >= 0) continue;
            if(grid[ni][nj] == '#') continue;

            dists[nf][id(ni,nj)] = dists[f][id(i,j)] + 1;

            que.emplace(nf, id(ni, nj));
        }
    }

    std::cout << "-1\n";
}
