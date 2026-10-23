#include <bits/stdc++.h>
using namespace std;
using ll=long long;
struct pl{
    int u,v;
    long long w;
};
int n,m,s,t;
bool cmp(pl x, pl y){
    return x.w<y.w;
}
vector <pl> a,b;
struct rol{
    int u,p,s;
};
struct dsu{
    int par[50005];
    vector <pair <int, int >> rb;
    dsu(){
        for(int i=1;i<=50005;i++) {
            par[i]=-1;
        }
    }
    int find(int u){
        if(par[u]<0) return u;
        return find(par[u]);
    }
    void add(int u, int v){
        u=find(u);
        v=find(v);
        if(u==v) return;
        if(par[u]<par[v]) swap(u,v);
        // return ;
        rb.push_back({u,par[u]});
        // return;
        par[v]+=par[u];
        par[u]=v;
    }
    void rollback(int ss){
        while(rb.size()>ss){
            auto it=rb.back();
            rb.pop_back();
            par[find(it.first)]-=it.second;
            par[it.first]=it.second;
        }
    }
};
dsu ds[255];
int l[50005],r[50005];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> s >> t;
    b.push_back({1,1,0});
    int cntb=1,cnta=0;
    for(int i=0;i<m;++i) {
        int c; cin >> c;
        int x,y; ll z;
        if(c==1) {
            cin >> x >> y >> z;
            a.push_back({x,y,z});
            cnta++;
        }
        else {
            cin >> x >> y >> z;
            b.push_back({x,y,z});
            cntb++;
        }
    }
    // return 0;
    sort(a.begin(),a.end(),cmp);
    sort(b.begin(),b.end(),cmp);
    int num=0;
    for(int i=0;i<cnta;i+=250) {
        l[++num]=i;
        r[num]=min(i+249,cnta-1);
    }
    for(int i=1;i<=num;i++){
        for(int j=0;j<l[i];j++) ds[i].add(a[j].u,a[j].v);   
    }
    int cur=num;
    long long ans=1e16;
    // ds[0].add(3,4);
    // return 0;
    for(int e=0;e<cntb;e++){
        auto i=b[e];
        for(int j=1;j<=num;j++)ds[j].add(i.u,i.v);
        while(cur>0&&ds[cur].find(s)==ds[cur].find(t)) cur--;
        if(!cur){
            ans=min(ans,i.w);
            break;
        }
        int truoc=ds[cur].rb.size();
        for(int j=l[cur];j<=r[cur];j++){
            ds[cur].add(a[j].u,a[j].v);
            if(ds[cur].find(s)==ds[cur].find(t)){
                ans=min(ans,a[j].w+i.w);
                break;
            }
        }
        ds[cur].rollback(truoc);
    }
    cout << ans;
    return 0;
}