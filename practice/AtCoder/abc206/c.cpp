#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#define REP(i,n) for(int i=0, i##_length=int(n); i<i##_length; ++i)
#define REPD(i,n) for(int i=(n)-1; i>=0; --i)
#define LOOP(n) REP(_$, (n))
#define FOR(i,l,r) for(ll i=(l), i##_last=ll(r); i<=i##_last; ++i)
#define FORD(i,l,r) for(ll i=(l), i##_last=ll(r); i>=i##_last; --i)
#define ITR(x,v) for(auto x : v)
#define ITRR(x,v) for(auto &x : v)
#define ITRP(x,y,v) for(auto [x, y] : v)
#define ITRPR(x,y,v) for(auto &[x, y] : v)

#define All(x) x.begin(),x.end()

#define chmax(a, b) a=max(a, b)
#define chmin(a, b) a=min(a, b)


int main() {
    ll n; cin >> n;
    ll ans = n * (n-1)/2;
    map<ll, ll> mp;
    REP(i, n) {
        ll a; cin >> a;
        mp[a]++;
    }

    ITRP(k, v, mp) {
        if(v <= 1) continue;
        ans -= v * (v-1)/2;
    }

    cout << ans << endl;
    return 0;
}
