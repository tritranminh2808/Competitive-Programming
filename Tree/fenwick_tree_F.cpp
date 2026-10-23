#include <bits/stdc++.h>
using namespace std;
int n;
bool cmp(pair <int, int>  x, pair <int, int >  y){
    if(x.first==y.first) return x.second<y.second;
    return x.first < y.first;
}
int st[1000005];
void update(int i, int v){
    for(;i<=100000;i+=i&-i) st[i]+=v;
}
int find(int i){
    int s=0;
    for(;i>0;i-=i&-i) s+=st[i];
    return s;
}
vector <pair <int,int> > g;
int cnt[100005];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    vector <pair <int, int > > v;
    map<pair <int, int > ,int> mp,cc;
    for(int i=1;i<=n;i++){
        int u,x; cin >> u >> x;
        cnt[x]++;
        g.push_back({u,x}); 
        v.push_back({u,x});
    }
    sort(v.begin(),v.end(),cmp);
    // v.erase(unique(v.begin(),v.end()),v.end());
   
    for(auto i:v){
        // cout << i.first << " " << i.second << "\n";
        mp[{i.first,i.second}]=find(i.second)-cc[{i.first,i.second}];
        update(i.second,1);
        cc[{i.first,i.second}]++;
    }
    for(auto i:g) cout << mp[{i.first,i.second}] << "\n";
    return 0;
}