#include <bits/stdc++.h>
#define int long long
using namespace std;
int sz[100005],par[100005];
int find(int u){
    if(u==par[u]) return u;
    return par[u]=find(par[u]);
}
void add(int u, int v){
    if(sz[u]<sz[v]) swap(u,v);
    sz[u]+=sz[v];
    par[v]=u;
}
struct pl{
    int u,v;
    long double w;
};
int n;
long double w,c;
vector <pl> edge;
bool cmp(pl x, pl y){
    return x.w<y.w;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i=0;i<=n;i++){
        sz[i]=1;
        par[i]=i;
        // edge.push_back({0,})
    }
    vector <pair <int, int > > d(n+1);
    for(int i=1;i<=n;i++) cin >> d[i].first  >> d[i].second;
    cin >> w >> c;
    for(int i=1;i<=n;i++){
        // edge.push_back({0,i,w});    
        for(int j=i+1;j<=n;j++) {
            long double h1=d[i].first-d[j].first,h2=d[i].second-d[j].second;
            long double kc=sqrtl(h1*h1+h2*h2)*c;
            edge.push_back({i,j,kc});
        }
    }
    sort(edge.begin(),edge.end(),cmp);
    // int cnt=0;
    long double ans=0;
    for(auto i:edge){
        int u=i.u,v=i.v;
        // long double w=i.w;
        u=find(u);
        v=find(v);
        if(u==v) continue;
        // if(i.w==w) cnt++;
        ans+=i.w;
        add(u,v);
    }
    // cout << ans;
    set<int> st;
    for(int i=1;i<=n;i++) st.insert(find(i));
    if(st.size()>1) ans=1e18*1.0;
    for(int i=0;i<=n;i++){
        sz[i]=1;
        par[i]=i;
        // edge.push_back({0,})
    }
    for(int i=1;i<=n;i++)edge.push_back({0,i,w});  
    sort(edge.begin(),edge.end(),cmp);
    // int cnt=0;
    long double res=0;
    for(auto i:edge){
        int u=i.u,v=i.v;
        // long double w=i.w;
        u=find(u);
        v=find(v);
        if(u==v) continue;
        // if(i.w==w) cnt++;
        res+=i.w;
        add(u,v);
    }
    cout << fixed << setprecision(9) << min(ans,res);
}