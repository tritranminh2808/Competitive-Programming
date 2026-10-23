#include <bits/stdc++.h>
using namespace std;
const int p=5e5+5;
int cnt[p],sol[p];
int sqr=0,n,t;
bool cmp(pair <int, pair <int, int > > a, pair <int, pair <int, int > > b){
	if(a.second.first/sqr!=b.second.first/sqr) return a.second.first/sqr<b.second.first/sqr;
	return a.second.second < b.second.second;
}
unordered_map<int,int> newv;
vector <int> b;
int a[500005];
void nen(){
	for(int i=0;i<n;i++) b.push_back(a[i]);
	sort(b.begin(),b.end());
	b.erase(unique(b.begin(),b.end()),b.end());
	for(int i=0;i<b.size();i++) newv[b[i]]=i+1;
	for(int i=0;i<n;i++) a[i]=newv[a[i]];
}	
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> t;
	sqr=sqrt(n);
	vector <pair <int, pair <int, int > > > v;
	for(int i=0;i<n;i++) cin >> a[i];
	nen();
	int id=0;
	while(t--){
		int l,r; cin >> l >> r;
		v.push_back({id,{l-1,r-1}});
		id++;
	}
	sort(v.begin(),v.end(),cmp);
	for(int i=v[0].second.first;i<=v[0].second.second;i++){
		cnt[a[i]]++;
		if(cnt[a[i]]==2) sol[v[0].first]++;
		if(cnt[a[i]]==3) sol[v[0].first]--;
	}
	int ans=sol[v[0].first];
	for(int i=1;i<v.size();i++){
		if(v[i].second.first>v[i-1].second.first){
			for(int j=v[i-1].second.first;j<v[i].second.first;j++) {
				cnt[a[j]]--;
				if(cnt[a[j]]==1) ans--;
				if(cnt[a[j]]==2) ans++;
			}
		}
		else if(v[i].second.first<v[i-1].second.first){
			for(int j=v[i].second.first;j<v[i-1].second.first;j++) {
				cnt[a[j]]++;
				if(cnt[a[j]]==2) ans++;
				if(cnt[a[j]]==3) ans--;
			}
		}

		if(v[i].second.second>v[i-1].second.second){
			for(int j=v[i-1].second.second+1;j<=v[i].second.second;j++) {
				cnt[a[j]]++;
				if(cnt[a[j]]==2) ans++;
				if(cnt[a[j]]==3) ans--;
			}
		}
		else if(v[i].second.second<v[i-1].second.second){
			for(int j=v[i].second.second+1;j<=v[i-1].second.second;j++) {
				cnt[a[j]]--;
				if(cnt[a[j]]==1) ans--;
				if(cnt[a[j]]==2) ans++;
			}
		}
		sol[v[i].first]=ans;
	}
	for(int i=0;i<v.size();i++) cout << sol[i] << "\n";
}
