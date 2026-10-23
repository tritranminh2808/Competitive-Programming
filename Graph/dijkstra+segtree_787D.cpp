#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,V;
vector <pair <int, int > > adj[1000005];
int st2[1000005],st3[1000005],idx=0;;
void build2(int id, int l , int r){
    st2[id]=++idx;
    if(l==r){
        adj[st2[id]].push_back({l,0});
        return;
    }
    int mid=(l+r)/2;
    build2(id*2,l,mid);
    build2(id*2+1,mid+1,r);
    adj[st2[id]].push_back({st2[id*2],0});
    adj[st2[id]].push_back({st2[id*2+1],0});
    
}
void build3(int id, int l , int r){
    st3[id]=++idx;
    if(l==r){
        adj[l].push_back({st3[id],0});
        return;
    }
    int mid=(l+r)/2;
    build3(id*2,l,mid);
    build3(id*2+1,mid+1,r);
    adj[st3[id*2]].push_back({st3[id],0});
    adj[st3[id*2+1]].push_back({st3[id],0});
}
void update2(int id, int l, int r, int lf, int rt, int v, int w){
    if(lf>r||rt<l) return;
    if(lf<=l&&rt>=r){
        adj[v].push_back({st2[id],w});
        return;
    }
    int mid=(l+r)/2;
    update2(id*2,l,mid,lf,rt,v,w);
    update2(id*2+1,mid+1,r,lf,rt,v,w);
}
void update3(int id, int l, int r, int lf, int rt, int v, int w){
    if(lf>r||rt<l) return;
    if(lf<=l&&rt>=r){
        adj[st3[id]].push_back({v,w});
        return;
    }
    int mid=(l+r)/2;
    update3(id*2,l,mid,lf,rt,v,w);
    update3(id*2+1,mid+1,r,lf,rt,v,w);
}
int kc[1000005];
priority_queue<pair<int, int > , vector <pair <int, int > > , greater<pair <int, int > > >pq;
void dijkstra(int u){
    kc[u]=0;
    pq.push({kc[u],u});
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
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> V;
    // cout << "ngu";
    idx=n;
    build2(1,1,n);
    build3(1,1,n);
    // cout << "ngu";
    for(int i=1;i<=1000000;i++) kc[i]=1e18;
    while(m--){
        int ty; cin >> ty;
        if(ty==1){
            int u,v,w; cin >> u >> v >> w;
            adj[u].push_back({v,w});
        }
        else if(ty==2){
            int v, l,r,w; cin >> v >> l >>r >> w;
            update2(1,1,n,l,r,v,w);
        }
        else{
            int v, l,r,w; cin >> v >> l >>r >> w;
            update3(1,1,n,l,r,v,w);
        }
    }
    // cout << "ngu";
    dijkstra(V);
    for(int i=1;i<=n;i++) {
        if(kc[i]==1e18) cout << "-1 ";
        else cout << kc[i] << " ";
    }
    return 0;
}