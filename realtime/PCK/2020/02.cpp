#include <bits/stdc++.h>
using namespace std;

int main() {
    int w, m, s; cin >> w >> m >> s;
    std::cout << ((int)(s <= m) | ((int)(w - s <= m) << 1)) << "\n";
}
