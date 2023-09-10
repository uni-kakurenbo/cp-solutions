#include <bits/stdc++.h>
using namespace std;

int main() {
    int d, x, y; cin >> d >> x >> y;
    cout << (abs(x) + abs(y) <= d ? "Yes" : "No") << "\n";
}
