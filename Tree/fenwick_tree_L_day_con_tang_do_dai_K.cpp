#include <bits/stdc++.h>
using namespace std;
const int mod=5000000;
int st[51][400005],dp[51][100005];
int a[100005];
void update(int x, int p, int v){
	for(int i=p;i<100000;i+=i&-i) st[x][i]=(st[x][i]+v)%mod;
}
int findind(int x,int p){
	int s=0;
	for(int i=p;i>0;i-=i&-i) s=(s+st[x][i])%mod;
	return s;
}
int find(int x, int l, int r){
	return (findind(x,r)-findind(x,l-1)+mod)%mod;
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,k; cin >> n >> k;
	for(int i=1;i<=n;i++) {
		cin >> a[i];
		a[i]++;
	}
//	build (1,1,1,n);
	for(int i=1;i<=n;i++) dp[1][i]=1;
	
	for(int i=1;i<=n;++i){
		for(int x=1;x<=k;x++){
			if(x>1) dp[x][i]=find(x-1,0,a[i]-1)%mod;
			update(x,a[i],dp[x][i]%mod);
			/*for(int j=1;j<i;j++){
				if(a[j]<a[i]) dp[x][i]=(dp[x][i]+dp[x-1][j])%mod;
			}*/
		}
	}
	int sol=0;
	for(int i=1;i<=n;i++) sol=(sol+dp[k][i])%mod;
	cout << sol;
	return 0;
}
