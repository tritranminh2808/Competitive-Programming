#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
vector <int> adj[200005];
int dep[200005],high[1005],jump[200005][18];
int cnt[200005];	
int c1[200005],c2[200005];
void dfs(int u,int v){
	for(auto i:adj[u]){
		if(i==v) continue;
//		high[i.first]=high[u]+i.second;
		dep[i]=dep[u]+1;
		jump[i][0]=u;
		dfs(i,u);
	
	}
}
void build(){
	for(int j=1;j<=17;j++) for(int i=1;i<=n;i++) jump[i][j]=jump[jump[i][j-1]][j-1];
}
int lca(int u, int v){
	if(dep[u]>dep[v]) swap(u,v);
	int dist=dep[v]-dep[u];
	for(int i=17;i>=0;i--){
		if(dist>= (1<<i)){
			dist-=(1<<i);
			v=jump[v][i];
		}
	}
	if(u==v) return u;
	for(int i=17;i>=0;--i){
		if(jump[v][i]==0||jump[u][i]==0) continue;
		if(jump[u][i]!=jump[v][i]){
			u=jump[u][i];
			v=jump[v][i];
		}
	}
	return jump[u][0];
}
vector <pair <int, int > > edge;
map<pair <int, int > , int > mp;
void cal(int u, int v){
	for(auto i:adj[u]){
		if(i==v) continue;
		cal(i,u);
		int u1=u,v1=v,u2=u,i2=i;
		if(u1>v1) swap(u1,v1);
		if(i2>u2) swap(u2,i2);
		mp[{u1,v1}]+=mp[{i2,u2}];
	}
}
signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for(int i=1;i<n;i++){
		int a,b; cin >> a >> b>> c1[i-1] >> c2[i-1];
		adj[a].push_back(b);
		adj[b].push_back(a);
		edge.push_back({a,b});
	}
//	dijkstra(1);
	dfs(1,0);
	build();
    // cout << lca(1,2);
    // return 0;
	for(int i=2;i<=n;i++){
		int x=lca(i,i-1);
		int ii=jump[i][0];
		int iii=jump[i-1][0];
		int iiii=jump[x][0];
		int j=i-1,p=i;
		if(ii<p) swap(p,ii); 
		if(iii<j) swap(j,iii); 
		if(iiii<x) swap(x,iiii); 
		mp[{p,ii}]++;
		mp[{j,iii}]++;
		mp[{x,iiii}]-=2;
	}
    // return 0;
	cal(1,0);
	long long res=0;
	for(int i=0;i<edge.size();i++){
		int a=c1[i],b=c2[i];
		int u=edge[i].first,v=edge[i].second;
		if(u>v) swap(u,v);
		res+=min(a*mp[{u,v}],b);
	}
	cout << res;
//	cout << 1;
	return 0;
}
