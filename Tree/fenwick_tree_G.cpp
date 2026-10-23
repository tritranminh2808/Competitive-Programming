#include <bits/stdc++.h>
using namespace std;
int st[1000005];
void update(int i, int v){
	for(;i<=1000000;i+=i&-i) st[i]+=v;
}
int find(int x){
	int s=0;
	for(int i=x;i>0;i-=i&-i) s+=st[i];
	return s;
}
struct pl{
	int typ,k,l,r; 
};
pl q[200005];
unordered_map<int, int > newv;
int oldv[1000005];
vector <int> b;
void nen(){
	sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    for(int i=0;i<b.size();i++) {
        newv[b[i]]=i+1;
        oldv[i+1]=b[i];
    }
}
int cnt[3000005];
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n; cin >>n ;
	for(int i=1;i<=n;i++){
        char c; cin >> c;
		if(c=='+') q[i].typ=1;
        if(c=='-') q[i].typ=2;
        if(c=='?') q[i].typ=3;
		if(q[i].typ==1) {
			cin >> q[i].k;
			b.push_back(q[i].k);
		}
		else if(q[i].typ==2){
			cin >> q[i].k;
			b.push_back(q[i].k);
		}
		else {
			cin >> q[i].k >> q[i].l >> q[i].r;
			b.push_back(q[i].l);
		    b.push_back(q[i].r);
		}
	}
    nen();
    for(int i=1;i<=n;i++){
        if(q[i].typ==1||q[i].typ==2) q[i].k=newv[q[i].k];
        else {
            q[i].l=newv[q[i].l];
            q[i].r=newv[q[i].r];
        }
    }
    for(int i=1;i<=n;i++){
        // cout << q[i].k << "\n";
        if(q[i].typ==1) {
            update(q[i].k,1);
            cnt[q[i].k]++;
        }
        else if(q[i].typ==2) {
            if(cnt[q[i].k]<1) continue;
            update(q[i].k,-1);
            cnt[q[i].k]--;
        }
        else{
            int l=q[i].l,r=q[i].r;
            if(find(r)-find(l-1)<q[i].k){
                cout << 0 << "\n";
                continue;
            }
            while(l<r){
                int mid=(l+r)/2;
                if(find(mid)-find(q[i].l-1)<q[i].k) l=mid+1;
                else r=mid;
            }
            cout << oldv[l] << "\n";
        }
    }

	
}
