#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
vector <pair <int, int > >  adj[100005];
int kc[100005];
priority_queue<pair <int,int > , vector <pair <int, int > > , greater<pair <int, int > > > pq;
void dijkstra(){
    while(!pq.empty()){
        pair <int, int > p=pq.top();
        pq.pop();
        if(kc[p.second]<p.first) continue;
        for(auto i:adj[p.second]){
            if(kc[i.first]>p.first+i.second){
                kc[i.first]=p.first+i.second;
                pq.push({kc[i.first],i.first});
            }
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>> n >> m;
    for(int i=1;i<=n;i++) kc[i]=1e18;
    while(m--){
        int a,b,c; cin >> a >> b >> c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    int k; cin >> k;
    while(k--){
        int x; cin >> x;
        pq.push({0,x});
        kc[x]=0;
    }
    dijkstra();
    int q; cin >> q;
    while(q--){
        int u; cin >> u;
        cout << kc[u] << " ";
    }
    return 0;
}