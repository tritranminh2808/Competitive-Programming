#include <bits/stdc++.h>
// #define int long long
using namespace std;
int n,m;
vector <pair <int, int > > adj[100005];
int num[100005],low[100005],bel[100005],sz[100005],dem[100005],cnta[100005],cntb[100005];
int cnt=0,c=0,sza,szb,totala,totalb;
bool del[100005];
stack <int> st;
int comp[100005],cntcomp=0;
vector <pair <int ,int > > cau;
int A[100005],B[100005];
void dfs(int u,int p){
    num[u]=low[u]=++cnt;
    if(A[u]) cnta[u]++;
    if(B[u])cntb[u]++;
    for(auto i:adj[u]){
        if(i.second!=p){
            if(num[i.first])  low[u]=min(low[u],num[i.first]);
            else {
                dfs(i.first,i.second);
                cnta[u]+=cnta[i.first];
                cntb[u]+=cntb[i.first];
                low[u]=min(low[u],low[i.first]);
                if(low[i.first]>num[u])cau.push_back({u,i.first});

            }
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> sza >> szb;
    for(int i=0;i<sza;i++){
        int u; cin >> u;
        A[u]=1;
    }
    for(int i=0;i<szb;i++){
        int u; cin >> u;
        B[u]=1;
    }
    // cout << totala << " " << totalb;
    for(int i=1;i<=m;i++){
        int u,v; 
        cin >> u >> v;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }
    for(int i=1;i<=n;i++) if(!num[i]) dfs(i,0);
    int sol=0;
    for(auto i:cau){
        int u=i.first,v=i.second;
        if(cnta[v]==sza||cnta[v]==0||cntb[v]==szb||cntb[v]==0) sol++;
    }
    cout << sol;
}