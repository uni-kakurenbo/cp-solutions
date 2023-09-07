#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m; std::cin >> n >> m;
    long t[m], h[m];
    for(int i=0; i<m; ++i) std::cin >> t[i] >> h[i], --h[i];

    std::set<int> yet;
    for(int i=0; i<n; ++i) yet.insert(i);

    long tot = 0;

    using state = std::pair<int,long>;
    std::priority_queue<state,std::vector<state>,std::greater<state>> que;

    for(int i=0; i<m; ++i) {
        que.emplace(h[i], t[i]);
        yet.erase(h[i]);
        tot += t[i];
    }

    while(not que.empty()) {
        auto [ v, r ] = que.top();
        que.pop();

        auto itr = yet.upper_bound(v);
        if(itr == yet.end()) continue;

        tot += r;
        yet.erase(*itr);

        que.emplace(*itr, r);
    }

    std::cout << tot << "\n";
}
