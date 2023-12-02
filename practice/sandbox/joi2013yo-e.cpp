/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 20 GCC */
#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        DEBUG("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

void solve() {
    int n,K;cin >> n >> K;
    std::vector x(2,vector<int>(n)),y(2,vector<int>(n)),z(2,vector<int>(n));
    vector<int>X,Y,Z;

    REP(i,n)REP(j,2){
        cin >> x[j][i] >> y[j][i] >> z[j][i];
        X.push_back(x[j][i]);Y.push_back(y[j][i]);Z.push_back(z[j][i]);
    }

    sort(ALL(X));sort(ALL(Y));sort(ALL(Z));
    X.erase(unique(ALL(X)),X.end());
    Y.erase(unique(ALL(Y)),Y.end());
    Z.erase(unique(ALL(Z)),Z.end());
    debug(X, Y, Z);

    std::vector G(X.size(),std::vector(Y.size(),vector<int>(Z.size())));

    auto idx = [&](int k,vector<int>&xx){
        return lower_bound(ALL(xx),k)-xx.begin();
    };

    REP(i,n){
        REP(a,2)REP(b,2)REP(c,2){
            int dx = idx(x[a][i],X),dy = idx(y[b][i],Y),
            dz = idx(z[c][i],Z);
            debug((a+b+c)%2, dx, dy, dz);
            if((a+b+c)%2)G[dx][dy][dz]--;
            else G[dx][dy][dz]++;
        }
    }
    debug(G);

    REP(i,X.size()-1)REP(j,Y.size())REP(k,Z.size())G[i+1][j][k]+=G[i][j][k];
    REP(j,Y.size()-1)REP(i,X.size())REP(k,Z.size())G[i][j+1][k]+=G[i][j][k];
    REP(k,Z.size()-1)REP(i,X.size())REP(j,Y.size())G[i][j][k+1]+=G[i][j][k];
    debug(G);

    int res = 0;
    REP(i,X.size()-1)REP(j,Y.size()-1)REP(k,Z.size()-1){
        if(G[i][j][k]>=K){
            debug(i, j, k);
            res+=(X[i+1]-X[i])*(Y[j+1]-Y[j])*(Z[k+1]-Z[k]);}
    }
    print(res);
}
