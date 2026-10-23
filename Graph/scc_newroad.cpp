#include <bits/stdc++.h>
// #define int long long
using namespace std;
int n,m;
set <int> adj[100005];
int dfn[100005],low[100005],bel[100005],sz[100005],dem[100005];
int idx=0,cc=0;
deque<int> st;
bool inst[100005];
void dfs(int u){
    dfn[u]=low[u]=++idx;
    st.push_back(u);
    inst[u]=1;
    for(auto i:adj[u]){
        if(!dfn[i]){
            dfs(i);
            low[u]=min(low[u],low[i]);
        }
        else if(inst[i]) low[u]=min(low[u],dfn[i]);
    }
    if(low[u]==dfn[u]){
        cc++;
        while(1){
            int v=st.back();
            st.pop_back();
            inst[v]=0;
            bel[v]=cc;
            sz[cc]++;
            if(v==u) break;
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v; 
        cin >> u >> v;
        adj[u].insert(v);
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i);
    for(int i=1;i<=n;i++){
        for(auto j:adj[i]) if(bel[i]==bel[j]) dem[bel[i]]++;
    }
    long long sol=0;
    for(int i=1;i<=cc;i++) sol+=1LL*sz[i]*(sz[i]-1)-dem[i];
    cout << sol;
}