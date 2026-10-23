#include <bits/stdc++.h>
#define int long long
using namespace std;
int c=257;
const int mod=1e9+7;
int hash1[1000005], hash2[1000005],power[1000005];
string a;
int n;
bool check(int l, int r){
	int r2=n-l+1,l2=n-r+1;
	long long memaybeo=(hash1[r]-hash1[l-1]*power[r-l+1])%mod,bomaygay=(hash2[r2]-hash2[l2-1]*power[r2-l2+1])%mod;
	if(memaybeo<0) memaybeo+=mod;
	if(bomaygay<0) bomaygay+=mod;
	if(bomaygay==memaybeo) return true;
	else return false;
}
signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	power[0]=1;
	for(int i = 1; i <= 1e6; i++) power[i] = power[i - 1] * c % mod;
	cin >> a;
	n=a.length();
	a=' '+a+' ';
//	if(check(14,22)) cout << "x";
	for(int i=1;i<=n;i++) hash1[i]=(hash1[i-1]*c+a[i]+1)%mod;
	reverse(a.begin(),a.end());
	for(int i=1;i<=n;i++) hash2[i]=(hash2[i-1]*c+a[i]+1)%mod;
	int l=0,r=n/2;
	while(l<=r){
		int mid=(r+l)/2;
		bool sech=0;
		for(int i=1;i<=n-2*mid+1;i++) {
			if(check(i,i+mid*2-1)){
				sech=1;
				break;
			}
		}
		if(sech==0){
			for(int i=1;i<=n-2*mid;i++) {
				if(check(i,i+mid*2)){
					sech=1;
					break;
				}
			}
		}
		if(sech==0) r=mid-1;
		else l=mid+1;
	}
	int res=(l-1)*2,res2=(l-1)*2+1;
	string sol;
	reverse (a.begin(),a.end());
	for(int i=1;i<=n-res+1;i++){
		if(check(i,i+res-1)){
			string sss;
			for(int j=i;j<=i+res-1;j++) sss+=a[j];
			sol=sss;
			break;
		}
	}
	for(int i=1;i<=n-res2+1;i++){
		if(check(i,i+res2-1)){
			string sss;
			for(int j=i;j<=i+res2-1;j++) sss+=a[j];
			sol=sss;
			break;
		}
	}
	cout << sol;
	return 0;
}
