#include <bits/stdc++.h>
// #define int long long
using namespace std;
int n,m;
set <int> adj[100005];
int num[100005],low[100005],comp[100005];
int timer=0,cntcomp=0;
bool del[100005];
stack<int> st;
void dfs(int u){
    // cout << u << " ";
    num[u]=low[u]=++timer;
    st.push(u);
    for(auto i:adj[u]){
        if(!del[i]){
            if(num[i]) low[u]=min(low[u],num[i]);
            else{
                dfs(i);
                low[u]=min(low[u],low[i]);
            }
        }
    }
    if(low[u]==num[u]){
        int v;
        cntcomp++;
        do{
            v=st.top();
            st.pop();
            del[v]=1;
            comp[v]=cntcomp;
        }while(u!=v);
    }
}
int dag[100005];
bool selectt[100005];
signed main(){
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    cin >> n >> m;
    // cout << n;
    vector <pair <int ,int > > edge;
    for(int i=1;i<=m;i++){
        int u,v; 
        cin >> u >> v;
        adj[u].insert(v);
        edge.push_back({u,v});
    }
    for(int i=1;i<=n;i++) if(!num[i]) dfs(i);
    // cout << cntcomp ;
    set<int> complist;
    for(int i=1;i<=n;i++) complist.insert(comp[i]);
    for(auto i:edge){
        int u=comp[i.first],v=comp[i.second];
        // cout << u << " " << v << "\n";
        if(u!=v)dag[v]++;
    }
    for(auto i:complist) {
        if(dag[i]==0){
            // cout << i;
            selectt[i]=1;
        }
    }int cnt=0;
    for(auto i:complist) if(selectt[i]) cnt++;
    cout << cnt ;
    // for(int i=1;i<=n;i++) if(selectt[comp[i]]) cout << i << " ";
}