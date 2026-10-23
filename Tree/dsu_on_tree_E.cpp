#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<pair <int, int > , null_type,less<pair <int, int > >,rb_tree_tag,
tree_order_statistics_node_update> oset;

int n,l,r;
vector <int> adj[200005];
int color[200005],d[200005];
set<int> st[200005];
void dfs1(int u, int v){
    st[u].insert(color[u]);
    for(auto i:adj[u]){
        if(i==v) continue;
        dfs1(i,u);
        if(st[u].size()<st[i].size()) swap(st[u],st[i]);
        for(auto j:st[i]) st[u].insert(j);
        st[i].clear();
    }
    d[u]=st[u].size();
}
multiset<int> ss[200005];
long long res[200005];
void dfs2(int u, int v){
    ss[u].insert(d[u]);
    for(auto i:adj[u]){
        if(i==v) continue;
        dfs2(i,u);
        if(ss[u].size()<ss[i].size()) swap(ss[u],ss[i]);
        for(auto j:ss[i]) {
            res[u]+=ss[u].upper_bound(j-l)-ss[u].lower_bound(j-r);
            res[u]+=ss[u].upper_bound(j+r)-ss[u].lower_bound(j+l);
            ss[u].insert(j);
        }
        ss[i].clear();
    }
    // for(auto i:ss[u]) {
    //     res[u]+=*ss[u].upper_bound(i-l)-*ss[u].lower_bound(i-r);
    //     res[u]+=*ss[u].upper_bound(i+r)-*ss[u].lower_bound(i+l);
    // }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> l >> r;
    for(int i=1;i<=n;i++) cin >> color[i];
    for(int i=1;i<n;i++){
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,0);
    for(int i=1;i<=n;i++) cout << res[i] << " ";
    return 0;
}