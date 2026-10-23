#include <bits/stdc++.h>
#define int long long
using namespace std;
int k;
string t,s;
//const int mod=1e9+7;
int f[20][2][11][2];
int backtrack(int id,bool l,int last,bool zero){
	if(id==s.size()) return 1;
	int &a=f[id][l][last][zero];
	if(a!=-1) return a;
	a=0;
	for(int i=0;i<=9;i++){
		if((l||i<=s[id]-'0')&&(i!=last||!zero)) a=(a+backtrack(id+1,l||i<s[id]-'0',i,zero||i!=0));
	}
	return a;
}
string iii(string s){
	int ss=0;
	for(auto i:s){
		ss*=10;
		ss+=i-'0';
	}
	string tt;
	ss--;
//	cout << ss;
	do{
		tt+='0'+ss%10;
		ss/=10;
	}
	while(ss!=0);
	reverse(tt.begin(),tt.end());
	return tt;
}
signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;
	cin >> s;
	for(int i=0;i<=19;++i){
		for(int j=0;j<=10;j++){
			f[i][0][j][0]=-1;
			f[i][1][j][0]=-1;
			f[i][0][j][1]=-1;
			f[i][1][j][1]=-1;
		}
	}
	int s1=backtrack(0,0,0,0);
//	s=t;
	s=iii(t);
//	cout << s;
	for(int i=0;i<=19;++i){
		for(int j=0;j<=10;j++){
			f[i][0][j][0]=-1;
			f[i][1][j][0]=-1;
			f[i][0][j][1]=-1;
			f[i][1][j][1]=-1;
		}
	}
	int s2=backtrack(0,0,0,0);
//	cout << s1;
	cout << s1-s2;
//	cout << sol;
	return 0;
}
