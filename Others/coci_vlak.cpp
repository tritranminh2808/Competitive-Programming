#include <bits/stdc++.h>
using namespace std;
int st[26][100005],cnt1[100005],cnt2[100005];
int nina[100005],emili[100005];//cua nina hay emili
int node=0;
void update(string s,bool x){
	int id=0;
	for(int i=0;i<s.length();++i){
		int nid=st[s[i]-'a'][id];
		if(nid==-1){
			st[s[i]-'a'][id]=++node;	
			nid=node;
		}
		if(x) nina[st[s[i]-'a'][id]]=1;
		else emili[st[s[i]-'a'][id]]=1;
		cnt1[nid]++;
		id=nid;
	}
}
int dp[100005][2];
bool play(int u, int t/*t=0 thi la luot nina, t=1 la luot emili*/){
	auto &a=dp[u][t];
	if(a!=-1) return a;
	if(!t){
		for(int i=0;i<26;++i){
			int v=st[i][u];
			if(v!=-1&&nina[v]&&!play(v,1)) return a=1;
		}
		return a=0;
	}
	else{
		for(int i=0;i<26;++i){
			int v=st[i][u];
			if(v!=-1&&emili[v]&&!play(v,0)) return a=1;
		}
		return a=0;
	}
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	memset(st,-1,sizeof(st));
	memset(dp,-1,sizeof(dp));
	int n; cin >> n;
	while(n--){
		string s; cin >> s;
		update(s,1);
	}
	int m; cin >> m;
//	node=0;
	while(m--){
		string s; cin >> s;
		update(s,0);
	}
	if(play(0,0)) cout << "Nina";
	else cout << "Emilija";
}
