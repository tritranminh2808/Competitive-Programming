#include <bits/stdc++.h>
#define int long long
//#define jump up
using namespace std;
int n,m,q;
int a[200005],dep[200005];
vector <int> adj[200005];
int maxx[18][200005],up[18][200005];
void dfs(int u, int v){
	for(auto i:adj[u]){
		if(i==v) continue;
		up[0][i]=u;
		maxx[0][i]=max(a[i],a[u]);
		dep[i]=dep[u]+1;
		dfs(i,u);
	}
}
void build(){
	for(int i=1;i<=17;i++){
		for(int j=1;j<=n;j++) {
			up[i][j]=up[i-1][up[i-1][j]];
			maxx[i][j]=max(maxx[i-1][j],maxx[i-1][up[i-1][j]]);
		}
	}
}
int lca(int u,int v){
	if(dep[u]>dep[v]) swap(u,v);
	int dist=dep[v]-dep[u];
	int maxn=0;
	for(int i=17;i>=0;i--){
		if(dist>=(1<<i)){
			dist-=(1<<i);
			maxn=max(maxn,maxx[i][v]);
			v=up[i][v];
		}
	}
	if(u==v) return maxn;
	for(int i=17;i>=0;i--){
//		if(up[i][u]==0||up[i][v]==0) continue;
		if(up[i][u]!=up[i][v]){
			maxn=max(maxn,maxx[i][v]);
			maxn=max(maxn,maxx[i][u]);
			u=up[i][u];
			v=up[i][v];
		}
	}
	maxn=max({maxn,maxx[0][u],maxx[0][v]});
	return maxn;
}
int f[200005];
signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	freopen("ship.inp","r",stdin);
	freopen("ship.out","w",stdout);
	cin >> n ;
	m=n-1;
	for(int i=1;i<=n;i++) cin >> a[i];
	while(m--){
		int u,v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1,0);
	build();
//	cout << lca(1,4);
	cin >> q;
	int sol=0;
	while(q--){
//		if(f[u]==0&&u!=1) continue;
		int u,v; cin >> u >> v;
		if(f[u]==0&&u!=1) continue;
		f[v]=max(f[v],f[u]+lca(u,v));
		sol=max(sol,f[v]);
	}
	cout << sol;
	return 0;
}
