#include <bits/stdc++.h>
#define int long long
using namespace std;

vector <pair < int, int > >   adj[100005];
int kc[4][100005];// 0 la tu s, 1 la tu t, 2 la tu u, 3 la tu v
vector < int > t(100005,-1);
void dijkstra(int x,int u)
{
	priority_queue < pair < int, int > , vector < pair < int, int > > , greater<pair < int, int > > > pq;
	kc[x][u]=0;
	pq.push({kc[x][u],u});
	while(!pq.empty()){
		pair <int, int > p=pq.top();
		pq.pop();
		if(kc[x][p.second]<p.first) continue;
		for(auto i: adj[p.second]){
			if(p.first+i.second<kc[x][i.first]){
				kc[x][i.first]=p.first+i.second;
				pq.push({kc[x][i.first],i.first});
				t[i.first]=p.second;
			}
		}
	}
}
vector <pair <int, pair <int, int > > > edge;
vector <pair <int, int > > spd, adj2[200005],adj1[200005];
int dp[200005],dp2[200005];
bool vst[200005],vst2[200005];
vector <int> topo,topo2;
void dfs(int u,int v){
	vst[u]=1;
	// cout << u << " ";
	for(auto i:adj2[u]){
		if(i.first==v) continue;
		if(!vst[i.first])dfs(i.first,u);
	}
	topo.push_back(u);
}
void dfs2(int u,int v){
	// cout << u << " ";
	vst2[u]=1;
	for(auto i:adj1[u]){
		if(i.first==v) continue;
		if(!vst2[i.first])dfs2(i.first,u);
	}
	topo2.push_back(u);
}
signed main(){
	ios_base::sync_with_stdio(0);
	int n,m,u,v,s,t;
	cin >> n >> m >> s >> t >> u >> v;
	for(int i=1;i<=n;++i) {
		kc[0][i]=1e16;
		kc[1][i]=1e16;
		kc[2][i]=1e16;
		kc[3][i]=1e16;
	}
	for(int i=1;i<=m;i++){
		int a,b,c; cin >>a >> b >> c;
		adj[a].push_back({b,c});
		adj[b].push_back({a,c});
		edge.push_back({a,{b,c}});
	}
	dijkstra(0,s);
	dijkstra(1,t);
	dijkstra(2,u);
	dijkstra(3,v);
	int s_t=kc[0][t];
	// cout << s_t;
	set<int> f;
	for(auto i:edge){
		int uu=i.first,vv=i.second.first,w=i.second.second;
		// cout << kc[0][uu] << " " << kc[1][vv]  << " " << w << "\n";
		if(kc[0][uu]+w+kc[1][vv]==s_t) 	{
			adj2[uu].push_back({vv,w});
			adj1[vv].push_back({uu,w});
			// cout << uu << " " << vv << "\n";
			f.insert(uu);
			f.insert(vv);
		}
		if(kc[0][vv]+w+kc[1][uu]==s_t){
			adj2[vv].push_back({uu,w});
			adj1[uu].push_back({vv,w});
			f.insert(uu);
			f.insert(vv);
		}
	}
	for(int i=1;i<=n;i++) {
		dp[i]=kc[2][i];
		dp2[i]=kc[3][i];
	}
	dfs(s,0);
	reverse(topo.begin(),topo.end());
	for(auto i:topo) {
		// cout << i << " ";
		for(auto j:adj2[i]) dp[j.first]=min(dp[j.first],dp[i]);
	}
	dfs2(t,0);
	reverse(topo2.begin(),topo2.end());
	for(auto i:topo2) {
		// cout <<i << ' ';
		for(auto j:adj1[i]) dp2[j.first]=min(dp2[j.first],dp2[i]);
	}
	int ans=INT_MAX;
	for(auto i:f)  /*cout << i << " " << dp[i] << "\n";*/ans=min({ans,dp[i]+kc[3][i],dp2[i]+kc[2][i]});
	cout << ans;
}
 