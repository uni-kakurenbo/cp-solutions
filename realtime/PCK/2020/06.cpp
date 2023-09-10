#include <bits/stdc++.h>
using namespace std;

int main() {
    string pat[] = {
        "BRYG",
        "GYRB",

        "BGRY",
        "YRGB",

        "RGYB",
        "BYGR"
    };

    char c0, c1; cin >> c0 >> c1;

    int pt_i = -1, pt_j = -1;

    for(int i=0; i<6; i++) {
        for(int j=0; j<4; j+=2) {
            if(pat[i][j] == c0 and pat[i][(j+1)%4] == c1) {
                pt_i = i, pt_j = j;
                goto det;
            }
        }
    }

  det:
    assert(pt_i >= 0 and pt_j >= 0);
    // cerr << c0 << " " << c1 << "\n";
    // cerr << pt_i << " " << pt_j << "\n";

    int n; cin >> n;
    for(int i=0; i<n; ++i) {
        int x, y; cin >> x >> y;
        int r = x/2;
        int c = y*2 + x%2;
        // cerr << r << " " << c << "\n";
        cout << pat[pt_i][((pt_j - (r%2) + ((r%2) ? -1 : 1) * c + 4) % 4 + 4) % 4] << "\n";
    }
}
