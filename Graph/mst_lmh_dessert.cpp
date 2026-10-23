#include <bits/stdc++.h>
#define int long long
using namespace std;
using ll = long long;
ll f[100005],par[100005],vst[100005];
int x[100005],y[100005];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
	for(int i=1;i<=100005;i++){
		f[i]=1e18;
		par[i]=-1;
	}
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> x[i] >> y[i];
	f[1]=0;
    par[1]=0;
    for(int i=1;i<=n;i++){
        int maxx=1e18,cur=-1;
        for(int j=1;j<=n;j++){
            if(!vst[j]&&f[j]<maxx){
                maxx=f[j];
                cur=j;
            }
        }
        if(cur==-1) break;
        vst[cur]=1;
        for(int j=1;j<=n;j++){
            if(vst[j]) continue;
            int w=abs(x[cur]-x[j])+abs(y[cur]-y[j]);
            w=max(w,f[cur]);
            if(f[j]>w){
                f[j]=w;
                par[j]=cur;
            }
        }
    }
    vector<int> path;
    for(int v = n; v != 0; v = par[v])  path.push_back(v);
    reverse(path.begin(), path.end());
	cout << f[n] << "\n";
    for(int u : path)  cout << u << " ";
    

    return 0;
}