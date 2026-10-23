#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
vector <pair <int, int >> adj[200005];
int color[200005];
int sum[200005];
vector <unordered_map<int, int >*> mp;
long long c[200005],cnt[200005],res[200005];
void dfs(int u, int v){
    
    mp[u]=new unordered_map<int, int > ();
    (*mp[u])[color[u]]=1;
    c[u]=1LL*(sum[color[u]]-1);
    for(auto i:adj[u]){
        if(i.first==v) continue;
        dfs(i.first,u);
        res[i.second]=c[i.first];
        auto *a=mp[u];
        auto *b=mp[i.first];
        if(a->size()<b->size()){
            swap(mp[u],mp[i.first]);       
            swap(a,b);
            swap(c[u],c[i.first]);
        }
        for(auto &it:*b){
            int o=0;
            if(a->find(it.first)!=a->end()) o=a->find(it.first)->second;
            c[u]-=1LL*o*(sum[it.first]-o);
            int nw=o+it.second;
            (*a)[it.first]=nw;
            c[u]+=1LL*nw*(sum[it.first]-nw);
        }
        delete b;
    }
}
signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for(int i=1;i<=n;i++) {
        cin >> color[i];
        sum[color[i]]++;
    }
	for(int i=1;i<n;i++){
		int a,b; cin >> a >> b;
		adj[a].push_back({b,i});
		adj[b].push_back({a,i});
	}
    mp.assign(n+1,NULL);
    dfs(1,0);
    delete mp[1];
    for(int i=1;i<n;i++) cout << res[i] << "\n";
	return 0;
}
