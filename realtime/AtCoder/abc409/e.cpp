/*
 * @uni_kakurenbo
 * https://github.com/uni-kakurenbo/competitive-programming-workspace
 *
 * CC0 1.0  http://creativecommons.org/publicdomain/zero/1.0/deed.ja
 */
/* #language C++ 23 GCC */
// #define DEBUGGER_ENABLED

#include "template/standard.hpp"

void solve();

signed main() {
    debug(__cplusplus);
    int $ = 1;
    // std::cin >> $;
    for(int _ = 0; _ < $; ++_) {
        debug_("Case: #" + std::to_string(_));
        solve();
    }
    return 0;
}

template <class E, class V, E (*merge)(E, E), E (*e)(), E (*put_edge)(V, int), V (*put_vertex)(E, int)>
struct RerootingDP {
    struct edge {
        int to, idx, xdi;
    };
    RerootingDP(int n_ = 0) : n(n_), inner_edge_id(0) {
        es.resize(2*n-2);
        start.resize(2*n-2);
        if (n == 1) es_build();
    }
    void add_edge(int u, int v, int idx, int xdi){
        start[inner_edge_id] = u;
        es[inner_edge_id] = {v,idx,xdi};
        inner_edge_id++;
        start[inner_edge_id] = v;
        es[inner_edge_id] = {u,xdi,idx};
        inner_edge_id++;
        if (inner_edge_id == 2*n-2){
            es_build();
        }
    }
    std::vector<V> build(int root_ = 0){
        root = root_;
        std::vector<V> subdp(n); subdp[0] = put_vertex(e(),0);
        outs.resize(n);
        std::vector<int> geta(n+1,0);
        for (int i = 0; i < n; i++) geta[i+1] = start[i+1] - start[i] - 1;
        geta[root+1]++;
        for (int i = 0; i < n; i++) geta[i+1] += geta[i];
        auto dfs = [&](auto sfs, int v, int f) -> void {
            E val = e();
            for (int i = start[v]; i < start[v+1]; i++){
                if (es[i].to == f){
                    std::swap(es[start[v+1]-1],es[i]);
                }
                if (es[i].to == f) continue;
                sfs(sfs,es[i].to,v);
                E nval = put_edge(subdp[es[i].to],es[i].idx);
                outs[geta[v]++] = nval;
                val = merge(val,nval);
            }
            subdp[v] = put_vertex(val, v);
        };
        dfs(dfs,root,-1);
        return subdp;
    }
    std::vector<V> reroot(){
        std::vector<E> reverse_edge(n);
        reverse_edge[root] = e();
        std::vector<V> answers(n);
        auto dfs = [&](auto sfs, int v) -> void {
            int le = outs_start(v);
            int ri = outs_start(v+1);
            int siz = ri - le;
            std::vector<E> rui(siz+1);
            rui[siz] = e();
            for (int i = siz-1; i >= 0; i--){
                rui[i] = merge(outs[le+i],rui[i+1]);
            }
            answers[v] = put_vertex(merge(rui[0],reverse_edge[v]),v);
            E lui = e();
            for (int i = 0; i < siz; i++){
                V rdp = put_vertex(merge(merge(lui,rui[i+1]),reverse_edge[v]),v);
                reverse_edge[es[start[v]+i].to] = put_edge(rdp,es[start[v]+i].xdi);
                lui = merge(lui,outs[le+i]);
                sfs(sfs,es[start[v]+i].to);
            }
        };
        dfs(dfs,root);
        return answers;
    }
    private:
    int n, root, inner_edge_id;
    std::vector<E> outs;
    std::vector<edge> es;
    std::vector<int> start;
    int outs_start(int v){
        int res = start[v] - v;
        if (root < v) res++;
        return res;
    }
    void es_build(){
        std::vector<edge> nes(2*n-2);
        std::vector<int> nstart(n+2,0);
        for (int i = 0; i < 2*n-2; i++) nstart[start[i]+2]++;
        for (int i = 0; i < n; i++) nstart[i+1] += nstart[i];
        for (int i = 0; i < 2*n-2; i++) nes[nstart[start[i]+1]++] = es[i];
        std::swap(es,nes);
        std::swap(start,nstart);
    }
};

i64 x[100010];
i64 cost[100010];

spair<i64> merge(spair<i64> a, spair<i64> b){
    return { a.first + b.first, a.second + b.second };
}
spair<i64> e(){
    return { 0, 0 };
}
spair<i64> put_edge(auto v, int i){
    return { v.first, v.second + std::abs(v.first) * cost[i] };
}
spair<i64> put_vertex(auto e, int v){
    return { e.first + x[v], e.second };
}

#include "template/warnings.hpp"
void solve() {
    i32 n; input >> n;
    REP(i, n) input >> x[i];
    // uni::graph<i32> g(n); g.read_bidirectionally<true>(n - 1);

    RerootingDP<spair<i64>,spair<i64>,merge,e,put_edge,put_vertex> g(n);
    REP(i, n-1) {
        i32 u, v, w; cin >> u >> v >> w;
        cost[i] = w;
        g.add_edge(u-1,v-1,i,i);
    }

    g.build();

    i64 ans = INF64;
    ITR(k, v, g.reroot()) {
        chmin(ans, v);
    }

    print(ans);

    // auto dfs = [&](auto&& self, auto v, auto p) {
    //     i64 cost = 0;
    //     ITR(e, g[v]) {
    //         if(e == p) continue;
    //         cost += e.cost * x[v];
    //     }
    //     return cost;
    // };
}
