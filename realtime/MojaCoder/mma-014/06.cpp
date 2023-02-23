/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ GCC */
/* #region template */
#include <bits/stdc++.h>
using namespace std;

#include "template.hpp"
/* #endregion */

//BEGIN CUT HERE
// O(F E \log V)
template<typename Flow, typename Cost>
struct PrimalDual{
  struct Edge{
    int dst;
    Flow cap;
    Cost cost;
    int rev;
    Edge(int dst,Flow cap,Cost cost,int rev):
      dst(dst),cap(cap),cost(cost),rev(rev){}
  };

  vector<vector<Edge>> G;
  vector<Cost> h,dist;
  vector<int> prevv,preve;

  PrimalDual(int n):G(n),h(n),dist(n),prevv(n),preve(n){}

  void add_edge(int u,int v,Flow cap,Cost cost){
    int e=G[u].size();
    int r=(u==v?e+1:G[v].size());
    G[u].emplace_back(v,cap,cost,r);
    G[v].emplace_back(u,0,-cost,e);
  }

  Cost residual_cost(int src,Edge &e){
    return e.cost+h[src]-h[e.dst];
  }

  void dijkstra(int s){
    struct P{
      Cost first;
      int second;
      P(Cost first,int second):first(first),second(second){}
      bool operator<(const P&a) const{return first>a.first;}
    };
    priority_queue<P> pq;

    dist[s]=0;
    pq.emplace(dist[s],s);
    while(!pq.empty()){
      P p=pq.top();pq.pop();
      int v=p.second;
      if(dist[v]<p.first) continue;
      for(int i=0;i<(int)G[v].size();i++){
        Edge &e=G[v][i];
        if(e.cap==0) continue;
        if(!(dist[v]+residual_cost(v,e)<dist[e.dst])) continue;
        dist[e.dst]=dist[v]+e.cost+h[v]-h[e.dst];
        prevv[e.dst]=v;
        preve[e.dst]=i;
        pq.emplace(dist[e.dst],e.dst);
      }
    }
  }

  Cost res;

  bool build(int s,int t,Flow f,
             function<void(decltype(h)&)> init=[](decltype(h) &p){
               fill(p.begin(),p.end(),0);
             }){
    res=0;
    init(h);
    const Cost INF = numeric_limits<Cost>::max();
    while(f>0){
      fill(dist.begin(),dist.end(),INF);
      dijkstra(s);
      if(dist[t]==INF) return false;

      for(int v=0;v<(int)h.size();v++)
        if(dist[v]<INF) h[v]=h[v]+dist[v];

      Flow d=f;
      for(int v=t;v!=s;v=prevv[v])
        d=min(d,G[prevv[v]][preve[v]].cap);

      f-=d;
      res=res+h[t]*d;
      for(int v=t;v!=s;v=prevv[v]){
        Edge &e=G[prevv[v]][preve[v]];
        e.cap-=d;
        G[v][e.rev].cap+=d;
      }
    }
    return true;
  }

  Cost get_cost(){return res;}
};

//BEGIN CUT HERE
// O((F+F') E \log V), F': sum of caps with negative cost
template<typename Flow, typename Cost>
struct NegativeEdge{
  PrimalDual<Flow, Cost> G;
  vector<Flow> fs;
  Cost sum;
  int S,T;
  NegativeEdge(int n):G(n+2),fs(n+2,0),sum(0),S(n),T(n+1){}

  void use_edge(int u,int v,Flow cap,Cost cost){
    fs[u]-=cap;
    fs[v]+=cap;
    sum=sum+cost*cap;
  }

  void add_edge(int u,int v,Flow cap,Cost cost){
    if(cost<Cost(0)){
      use_edge(u,v,cap,cost);
      swap(u,v);
      cost=-cost;
    }
    G.add_edge(u,v,cap,cost);
  }

  bool build(){
    Flow f=0;
    for(int i=0;i<S;i++){
      if(fs[i]>0){
        f+=fs[i];
        G.add_edge(S,i,+fs[i],Cost(0));
      }
      if(fs[i]<0){
        G.add_edge(i,T,-fs[i],Cost(0));
      }
    }
    return G.build(S,T,f);
  }

  bool build(int ts,int tt,Flow tf){
    fs[ts]+=tf;
    fs[tt]-=tf;
    return build();
  }

  Cost get_cost(){
    return sum+G.get_cost();
  }
};


signed main() {
    int n; cin >> n;
    vector<ll> a(n); input >> a;
    vector d(n, vector<ll>(n-1)); input >> d;
    debug(a, d);

    NegativeEdge<ll,ll> G(n*n+2);

    REP(i, n) {
        ll sum = 0;
        REP(j, n-1) {
            sum -= d[i][j];
            G.add_edge(i, n+j, 1, sum);
        }
    }

    REP(i, n) G.add_edge(2*n, i, 1, -a[i]);
    REP(i, n-1) G.add_edge(n+i, 2*n+1, 1, 0);

    G.build(2*n, 2*n+1, n);

    print(-G.get_cost());

    return 0;
}
