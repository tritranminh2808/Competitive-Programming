#include <bits/stdc++.h>
// #define int long long
using namespace std;
using ll = long long;
ll f[100005];
int par[100005],vst[100005];
ll x[100005],y[100005];
const ll gay=1e-9;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    ll h;
	for(int i=1;i<=100005;i++){
		f[i]=1e18;
		par[i]=-1;
	}
    cin >> n>> h;
    for(int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    priority_queue<pair <ll ,int >, vector <pair <ll, int > > , greater <pair <ll, int > > > pq;
    // firts la khoang cach, second la chi so bien
    for(int i=1;i<=n;i++) {
        f[i]=y[i]*y[i];
        pq.push({f[i],i});
    }
    ll sol=1e18;
    while(!pq.empty()){
        pair <ll ,int > p=pq.top();
        pq.pop();
        if(vst[p.second]) continue;
        vst[p.second]=1;
        if(p.first>=sol) break;
        sol=min(sol,max(p.first,(h-y[p.second])*(h-y[p.second])));
        for(int i=1;i<=n;i++){
            if(vst[i]) continue;
            ll a=abs(x[p.second]-x[i]),b=abs(y[p.second]-y[i]) ;
            ll w=(a*a+b*b);
            w=max(w,p.first);
            if(w<f[i]){
                f[i]=w;
                pq.push({f[i],i});
            }
        }
    }
    sol=sqrt(sol);
    cout << sol;
    return 0;
}