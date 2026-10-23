#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[200005];
int n,q;
vector <int>  adj[200005];
bool vst[200005];
int e[500005],st[18][400005];
int sz;
vector <int> euler;
struct pl{
	int maxx,sum,pre,suf;
};
const int inf=-1e16;
pl ST[1600005];
pl merge(pl x, pl y){
	pl c;
	c.sum=x.sum+y.sum;
	c.pre=max(x.pre,x.sum+y.pre);
	c.suf=max(y.suf,y.sum+x.suf);
	c.maxx=max({x.maxx,y.maxx,x.suf+y.pre});
	return c;
}
void buildseg(int id, int l, int r){
//	cout << id << " ";
	if(l==r){
		ST[id]={e[l],e[l],e[l],e[l]};
		return;
	}
	int mid=(l+r)/2;
	buildseg(id*2,l,mid);
	buildseg(id*2+1,mid+1,r);
	ST[id]=merge(ST[id*2],ST[id*2+1]);
}
pl findseg(int id, int l, int r, int lf, int rt){
	if(lf>r||rt<l) return {inf,0,inf,inf};
	if(lf<=l&&rt>=r) return ST[id];
	int mid=(l+r)/2;
	return merge(findseg(id*2,l,mid,lf,rt),findseg(id*2+1,mid+1,r,lf,rt));
}
void build(int i){
    vst[i]=1;
    euler.push_back(i);
    for(auto j:adj[i]){
        if(!vst[j]) {
            build(j);
            euler.push_back(i);
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<n;i++){
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    euler.push_back(0);
    build(1);
    unordered_map<int, int> fir;
    for(int i=1;i<euler.size();i++) {
        if(!fir.count(euler[i])) fir[euler[i]]=i;
        if(fir.size()==n) break;
    }
    // for(auto i:fir) cout << i.first << " " << i.second << "\n";
    sz=euler.size();
    for(int i=1;i<sz;i++) e[i]=a[euler[i]];
    // for(int i=1;i<sz;i++) cout << e[i] << " ";
    // cout << "\n";
    // build_rmq();
    buildseg(1,1,sz-1);
    while(q--){
        int u,v; cin >> u >> v;
        cout << max((int)0,findseg(1,1,sz-1,fir[u],fir[v]).maxx) << "\n";
    }
    return 0;
}