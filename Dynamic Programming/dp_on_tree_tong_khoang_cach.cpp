#include <bits/stdc++.h>
#define pb push_back
using namespace std;
using ll=long long;
vector <int> adj[200005];
long long ans[200005];
int sz[200005],n;
void dfs1(int u,int v){
    sz[u]=1;
    for(auto i:adj[u]){
        if(i==v) continue;
        dfs1(i,u);
        sz[u]+=sz[i];
        ans[u]+=ans[i]+sz[i];
    }
}
void dfs2(int u, int v){
    for(auto i:adj[u]){
        if(i==v) continue;
        ans[i]=ans[u]+n-2*sz[i];
        dfs2(i,u);
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>> n;
    for(int i=1;i<n;i++){
        int u,v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs1(1,0);
    dfs2(1,0);
    for(int i=1;i<=n;i++) cout << ans[i] << " ";
    return 0;
}