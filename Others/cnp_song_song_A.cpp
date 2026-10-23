#include <bits/stdc++.h>
using namespace std;
int par[200005],sz[200005],n,m,Q,l[200005],r[200005];
vector <int> adj[200005];
void reset(){
    for(int i=1;i<=n;i++){
        sz[i]=1;
        par[i]=i; 
    }
    for(int i=1;i<=m;i++)adj[i].clear();
}
int find(int u){
    if(u==par[u]) return u;
    return par[u]=find(par[u]);
}
void add(int u, int v){
    u=find(u);
    v=find(v);
    if(u==v) return;
    if(sz[u]<sz[v]) swap(u,v);
    sz[u]+=sz[v];
    par[v]=u;
}
pair <int, int> edge[200005],q[200005];
int sol[200005];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>> n >> m >> Q;
    for(int i=1;i<=m;i++) cin >> edge[i].first >> edge[i].second;
    reset();
    int logm=32;
    for(int i=1;i<=Q;i++) cin >> q[i].first >> q[i].second;
    for(int i=1;i<=Q;i++){
        l[i]=1;r[i]=m;
        sol[i]=-1;
        if(q[i].first==q[i].second) sol[i]=0;
    }

    while(logm--){
        reset();
        for(int i=1;i<=Q;i++){
            if(l[i]>r[i]) continue;
            int mid=(l[i]+r[i])/2;
            adj[mid].push_back(i);
        }
        for(int i=1;i<=m;i++){
            add(edge[i].first,edge[i].second);
            for(auto j:adj[i]){
                if(q[j].first==q[j].second) continue;
                if(find(q[j].first)!=find(q[j].second)) l[j]=i+1;
                else {
                    r[j]=i-1;
                    sol[j]=i;
                }
            }
        }
    }
    for(int i=1;i<=Q;i++) cout << sol[i] << "\n";
    return 0;
}
