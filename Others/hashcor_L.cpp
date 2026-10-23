#include <bits/stdc++.h>
#define int long long
using namespace std;
struct pl{
    int l,r,id;
};
pl query[200005],q2[200005];
int n,q;
int a[200005],b[200005];
// bool ans[200005];
bool cmp(pl a, pl b){
    return a.l < b.l;
}
mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
long long ran(int l, int r){
    return l+rng()%(r-l+1);
}
unordered_map<int, long long > newv;
unordered_map<long long,bool> se;
vector <int> c;
int st[200005];
unordered_map<int,int > cur,nxt;
void update(int i, int v){
    for(;i<=200000;i+=i&-i) st[i]^=v;
}
int find(int i){
    int re=0;
    for(;i>0;i-=i&-i) re^=st[i];
    return re;
}
int res[200005],ans[200005];
signed main(){
    freopen("input.inp","r",stdin);
    freopen("output.out","w",stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    for(int i=1;i<=400000;i++){
        long long cc=ran(1,1e15);
        while(se[cc]==1)    cc=ran(1,1e15);
        newv[i]=cc;
        se[cc]=1;
    }
    cin >> n>> q;
    for(int i=1;i<=n;i++) {
        cin >> a[i];
        c.push_back(a[i]);
    }
    for(int i=1;i<=n;i++) {
        cin >> b[i];
        c.push_back(b[i]);
    }
    sort(c.begin(),c.end());
    c.erase(unique(c.begin(),c.end()),c.end());
    for(int i=1;i<=n;i++){
        a[i]=newv[lower_bound(c.begin(),c.end(),a[i])-c.begin()+1];
        b[i]=newv[lower_bound(c.begin(),c.end(),b[i])-c.begin()+1];
    }
    for(int i=n;i>=1;i--){
        nxt[i]=cur[a[i]];
        cur[a[i]]=i;
    }

    for(int i=1;i<=q;i++){
        int l,r,u,v; cin >> l >> r >> u >> v;
        query[i]={l,r,i};
        q2[i]={u,v,i};
    }
    sort(query+1,query+q+1,cmp);
    sort(q2+1,q2+q+1,cmp);
    cur.clear();
    for(int i=query[1].l;i<=n;i++){
        if(cur[a[i]]==0) update(i,a[i]);
        cur[a[i]]=1;
    }
    res[query[1].id]=find(query[1].r)^find(query[1].l-1);
    for(int i=2;i<=q;i++) {
        for(int j=query[i-1].l;j<query[i].l;j++){
            if(nxt[j])update(nxt[j],a[j]);
            update(j,a[j]);
        }
        res[query[i].id]=find(query[i].r)^find(query[i].l-1);
    }
    memset(st,0,sizeof(st));
    cur.clear();
    for(int i=n;i>=1;i--){
        nxt[i]=cur[b[i]];
        cur[b[i]]=i;
    }
    cur.clear();
    for(int i=q2[1].l;i<=n;i++){
        if(cur[b[i]]==0) update(i,b[i]);
        cur[b[i]]=1;
    }
    ans[q2[1].id]=find(q2[1].r)^find(q2[1].l-1);
    for(int i=2;i<=q;i++) {
        for(int j=q2[i-1].l;j<q2[i].l;j++){
            if(nxt[j])update(nxt[j],b[j]);
            update(j,b[j]);
        }
        ans[q2[i].id]=find(q2[i].r)^find(q2[i].l-1);
    }
    for(int i=1;i<=q;i++) {
        if(res[i]==ans[i]) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
