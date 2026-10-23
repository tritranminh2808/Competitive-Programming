#include <bits/stdc++.h>
using namespace std;
int sqr=0;
int a[50005],n,q;
int res[200005];
unordered_map<int,int> newv;
vector <int> b;
void nen(){
	for(int i=0;i<n;i++) b.push_back(a[i]);
	sort(b.begin(),b.end());
	b.erase(unique(b.begin(),b.end()),b.end());
	for(int i=0;i<b.size();i++) newv[b[i]]=i+1;
	for(int i=0;i<n;i++) a[i]=newv[a[i]];
}	
vector <int> block[230];
struct pl{
	int l,r,k;
	bool type;
};
pl query[50005];
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n>> q;
	sqr=sqrt(n);
	for(int i=0;i<n;i++) cin >> a[i];
	for(int i=0;i<q;i++){
		string s; cin >> s;
		if(s[0]=='S'){
			query[i].type=0;
			cin >> query[i].l >> query[i].k;
			b.push_back(query[i].k);
		}
		else{
			query[i].type=1;
			cin >> query[i].l >> query[i].r >> query[i].k;
			b.push_back(query[i].k);
		}
	}
	nen();
	for (int i=0;i<n;i++) block[i/sqr].push_back(a[i]);
	for(int i=0;i<=sqr;i++) sort(block[i].begin(),block[i].end());
	for(int i=0;i<q;i++){
//		string s; cin >> s;
		if(!query[i].type){
			int u=query[i].l,v=query[i].k;
			u--;
			v=newv[v];
			int can=u/sqr;
			auto it=lower_bound(block[can].begin(),block[can].end(),a[u]);
			if(it!=block[can].end()&&*it==a[u]) block[can].erase(it);
            a[u]=v;
            auto it2=lower_bound(block[can].begin(),block[can].end(),v);
            block[can].insert(it2,v);
		}
		else{
			int l=query[i].l,r=query[i].r,k=query[i].k;
			l--;
			r--;
			k=newv[k];
			int sol=0;
			if(l/sqr==r/sqr){
				for(int i=l;i<=r;i++) if(a[i]<=k) sol++;
				cout << sol << "\n";
				continue;
			}
			for(int i=l;i<min((l/sqr+1)*sqr,r+1);i++) if(a[i]<=k) sol++;
			int xx=r/sqr;
			for(int i=max(xx*sqr,l);i<=r;i++) if(a[i]<=k) sol++;
			for(int i=l/sqr+1;i<xx;i++)  sol+=upper_bound(block[i].begin(),block[i].end(),k)- block[i].begin();
            cout << sol << "\n";
		}
	}
	return 0;
}

