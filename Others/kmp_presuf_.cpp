#include <bits/stdc++.h>
using namespace std;
int pre[1000005];
int ans[1000005];
int main(){
	string s;
	cin >> s;
	pre[0]=0;
	for(int i=1;i<s.length();i++){
		int j=pre[i-1];
		while(j>0&&s[i]!=s[j]) j=pre[j-1];
		if(s[i]==s[j]) j++;	
		pre[i]=j;
	}
//	for(int i=0;i<s.length();i++) cout << pre[i] << " ";
	for(int i=0;i<s.length();i++) ans[i]++;
	for(int i=s.length()-1;i>=0;i--) {
		if (pre[i] > 0) {
    	ans[ pre[i] - 1 ] += ans[i];
	}

	}
//	for(int i=0;i<s.length();i++) cout << ans[i] << " ";
	int ind = s.length();
	vector <pair <int, int > > v;
	while(ind != 0){
//	    cout << ind << " " << ans[ind-1] << "\n";
		v.push_back({ind,ans[ind-1]});
	    ind = pre[ind-1];
	}
	cout << v.size() << "\n";
	reverse(v.begin(),v.end());
	for(auto i : v) cout << i.first << " " << i.second << "\n";
	return 0;
}