#include <bits/stdc++.h>
#define int long long
using namespace std;
using ll=long long;
int base=26;
vector <ll> b;
unordered_map<ll,int> mp;
void nen(){
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    for(int i=0;i<b.size();i++) mp[b[i]]=i+1;
}
int st[1000006];
void update(int i,int v){
    for(;i<=100000;i+=i&-i) st[i]+=v;
}
int find(int i){
    int s=0;
    for(;i>0;i-=i&-i) s+=st[i];
    return s;
}
bool cmp(pair <string, ll> a, pair <string, ll>  b){
    return a.first>b.first;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    vector <pair <string, ll> > a(n+1);
    for(int i=0;i<n;i++) cin >> a[i].first;
    for(int i=0;i<n;++i) {
        
        string s=a[i].first;
        reverse(s.begin(),s.end());
        ll hs=0;
        for(int j=0;j<s.length();j++) hs=hs*base+s[j]-'a'+1;
        for(int j=s.length();j<10;j++) hs=hs*base+1;
        
        a[i].second=hs;
        b.push_back(hs);
    }
    nen();
    sort(a.begin(),a.end(),cmp);
    unordered_map<int, int > mm,chk;
    for(int i=0;i<n;i++) {
        // cout << a[i].first  << "\n";
        a[i].second=mp[a[i].second];
        mm[a[i].second]++;
    }
    long long ans=0;
    for(int i=0;i<n;i++){
        // cout << a[i].first << " " << a[i].second << "\n";
        if(chk[a[i].second]==1) continue;
        chk[a[i].second]=1;
        ans+=mm[a[i].second]*find(a[i].second-1);
        update(a[i].second,mm[a[i].second]);
    } 
    cout << ans;
    return 0;
} 