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
bool used[100005];
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int q; cin >> q;
    while(q--){
        cin >> n >> m;
        timer = 0;
        cntcomp = 0;
        while(!st.empty()) st.pop();
        for(int i = 1; i <= n; i++){
            adj[i].clear();
            num[i] = low[i] = comp[i] = 0;
            del[i] = false;
            used[i]=0;
        }
        // cout << n;
        vector <pair <int ,int > > edge;
        for(int i=1;i<=m;i++){
            int u,v; 
            cin >> u >> v;
            used[u]=used[v]=1;
            adj[u].insert(v);
            edge.push_back({u,v});
        }
        for(int i=1;i<=n;i++) if(used[i]&&!num[i]) dfs(i);
        // cout << cntcomp ;
        vector<vector<int>> dag(cntcomp+1);
        vector<int> indeg(cntcomp+1, 0);

        for(auto &e : edge){
            int cu = comp[e.first];
            int cv = comp[e.second];
            if(cu != cv){
                dag[cu].push_back(cv);
            }
        }
        for(int u = 1; u <= cntcomp; u++){
            sort(dag[u].begin(), dag[u].end());
            dag[u].erase(unique(dag[u].begin(), dag[u].end()), dag[u].end());
            for(int v : dag[u]){
                indeg[v]++;
            }
        }
        queue<int> q;
        for(int c = 1; c <= cntcomp; c++){
            if(indeg[c] == 0) 
                q.push(c);
        }

        vector<int> topo;
        topo.reserve(cntcomp);
        while(!q.empty()){
            int u = q.front(); q.pop();
            topo.push_back(u);
            for(int v : dag[u]){
                if(--indeg[v] == 0)
                    q.push(v);
            }
        }
        bool ok = true;
        for(int i = 0; i+1 < (int)topo.size(); i++){
            int u = topo[i], v = topo[i+1];
            if(!binary_search(dag[u].begin(), dag[u].end(), v)){
                ok = false;
                break;
            }
        }
        if(ok) cout << "YES\n";
        else cout << "NO\n";
    }
}