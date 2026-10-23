#include <bits/stdc++.h>
using namespace std;
const int pp=3e5+5;
int par[pp],sz[pp];
struct pl{
    int typ,x,y;
};
pl q[pp];
struct rol{
    int u,p,s,cc;
};
vector <rol> rb;
int find(int u){
    if(par[u]==u) return u;
    return find(par[u]);
}
int cnt;
void add(int u, int v){
    u=find(u);
    v=find(v);
    if(u==v) return;
    if(sz[u]>sz[v]) swap(u,v);
    rb.push_back({u,par[u],sz[u],cnt});
    rb.push_back({v,par[v],sz[v],cnt});
    sz[v]+=sz[u];
    par[u]=v;
    cnt--;
}
int ans[pp];
vector <pair <int, int > > st[4*pp];
void rollback(int ss){
    while(rb.size()>ss){
        auto x=rb.back();
        rb.pop_back();
        par[x.u]=x.p;
        sz[x.u]=x.s;
        cnt=x.cc;
    }
}
void dnc(int id, int l, int r){
    
    for(auto i:st[id])  add(i.first,i.second);
    if(l==r) {
        ans[l]=cnt;
        return;
    }
    int check=rb.size();
    int mid=(l+r)/2;
    dnc(id*2,l,mid);
    rollback(check);
    dnc(id*2+1,mid+1,r);
    rollback(check);
}
void update(int id,int l, int r, int lf, int rt, int u, int v){
    if(lf>r||rt<l) return;
    if(lf<=l&&rt>=r){
        st[id].push_back({u,v});
        return;
    }
    int mid=(l+r)/2;
    update(id*2,l,mid,lf,rt,u,v);
    update(id*2+1,mid+1,r,lf,rt,u,v);
    // dnc(id,l,r);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("connect.in","r",stdin);
    freopen("connect.out","w",stdout);
    int n,m; cin >> n >> m;
    if(m==0) return 0;
    cnt=n;
    for(int i=1;i<=n;i++) {
        par[i]=i;
        sz[i]=1;
    }
    
    map<pair <int, int > ,int> mp;
    for(int i=1;i<=m;i++) {
        char c; cin >> c;
        if(c=='+') {
            q[i].typ=1;
            cin >> q[i].x >> q[i].y;
            if(q[i].x>q[i].y) swap(q[i].x,q[i].y);
            mp[{q[i].x,q[i].y}]=i;
        }
        else if(c=='-') {
            q[i].typ=2;
            cin >> q[i].x >> q[i].y;
            if(q[i].x>q[i].y) swap(q[i].x,q[i].y);
            update(1,1,m,mp[{q[i].x,q[i].y}],i-1,q[i].x,q[i].y);
            mp.erase({q[i].x,q[i].y});

        }
        else q[i].typ=3;
    }
   
    for (auto &it:mp) {
        auto e=it.first;
        int start=it.second;
        update(1, 1, m, start, m,e.first,e.second);
    }
     
    dnc(1,1,m);
    // cout << "ngu";
    // return 0;
    for(int i=1;i<=m;i++) if(q[i].typ==3) cout << ans[i] << "\n";
    return 0;
}