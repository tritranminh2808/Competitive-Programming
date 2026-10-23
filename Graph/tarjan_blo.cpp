#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,sse4.2,popcnt")
#pragma GCC optimize("unroll-loops")
#pragma GCC diagnostic ignored "-Wunused-result"
#pragma GCC diagnostic ignored "-Wformat-security"
#define int long long
using namespace std;
using ll=long long;
int n,m;
vector <pair <int, int > > adj[100005];
int num[100005],low[100005],sz[100005],dem[100005],ans[100005];
int cnt=0;
stack <int> st;
vector <int> comp[100005];
int cau=0,khop=0;
void dfs(int u,int p){
    int cntchild=0;
    num[u]=low[u]=++cnt;
    sz[u]=1;
    for(auto i:adj[u]){
       
        if(i.second!=p){
            if(num[i.first])  low[u]=min(low[u],num[i.first]);
            else {
                dfs(i.first,i.second);
                sz[u]+=sz[i.first];
                cntchild++;
                low[u]=min(low[u],low[i.first]);
                if(low[i.first]>=num[u]) comp[u].push_back(sz[i.first]);
            }
        }
    }
    if(p==0&&cntchild<2) comp[u].clear();
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v; 
        cin >> u >> v;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }
    dfs(1, 0);

    ll total=n*(n - 1);
    for (int u=1;u<=n;u++) {
        ll dem = 0;
        ll noi = 0;
        for (ll s : comp[u]) {
            dem += s;
            noi += s * (s - 1);
        }
        ll rem=(n - 1)-dem;
        if (rem > 0) noi+=rem*(rem - 1);
        ans[u] = total - noi;
    }
    for (int i = 1; i <= n; i++)  cout << ans[i] << '\n';
    
}