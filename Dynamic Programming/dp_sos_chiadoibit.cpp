#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int n;
int a[400005];
int inf=1<<10;
int f[(1<<20)+1];
int ans[400005];
signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for(int i=0;i<=(1<<20);i++) f[i]=1;
	for(int i=1;i<=n;i++) {
		cin >> a[i];
		int x1=a[i]>>10,x2=a[i]&(inf-1);
		for(int j=0;j<inf;j++)	if((x1&j)==x1) f[(j<<10)|x2]=a[i]*f[(j<<10)|x2]%mod;
		int res=1;
		for(int j=0;j<inf;j++) if((x2&j)==j) res=res*f[(x1<<10)|j]%mod;
        ans[i]=res;
	}
    for(int i=1;i<=n;i++) cout << ans[i]<< "\n";
	return 0;
}
