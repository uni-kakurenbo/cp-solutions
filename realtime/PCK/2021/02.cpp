#include <bits/stdc++.h>
using namespace std;

int main() {
    int a[4]; cin >> a[0] >> a[1] >> a[2] >> a[3];
    sort(a, a+4);

    cout << int(a[0] == a[1] and a[2] == a[3]) << "\n";
}
