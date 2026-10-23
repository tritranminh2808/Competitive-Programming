#include <bits/stdc++.h>
using namespace std;
using ll=long long;
int n,Q,l[200005],r[200005];
vector <int> pos[100005],adj[100005];
struct pl{
    int lf, rt,maxx;  
};
pl st[400005];
pl merge(pl x, pl y,int l, int r){
    pl z;
    int mid=(l+r)/2;
    if(x.lf==mid-l+1) z.lf=x.lf+y.lf;
    else z.lf=x.lf;
    if(y.rt==r-mid) z.rt=y.rt+x.rt;
    else z.rt=y.rt;
    z.maxx=max({x.maxx,y.maxx,x.rt+y.lf});
    return z;
}
void update(int id,int l, int r, int u, int v){
    if(u<l||u>r) return;
    if(l==r){
        st[id].maxx=1;
        st[id].lf=1;
        st[id].rt=1;
        return;
    }
    int mid=(l+r)/2;
    update(id*2,l,mid,u,v);
    update(id*2+1,mid+1,r,u,v);
    st[id]=merge(st[id*2],st[id*2+1],l,r);
}
pl find(int id,int l,int r, int u, int v){
    if(u>r||v<l) return {0,0,0};
    if(u<=l&&v>=r) return st[id];
    int mid=(l+r)/2;
    return merge(find(id*2,l,mid,u,v),find(id*2+1,mid+1,r,u,v),l,r);
}
void reset(){
    for(int i=1;i<=4*n;i++){
        st[i].lf=0;
        st[i].rt=0;
        st[i].maxx=0;
    }
    for(int i=1;i<=100000;i++) adj[i].clear();
}
pl q[200005];
int sol[200005],a[200005];
unordered_map<ll,ll> oldv,newv;
void nen(){
    vector <int> b;
    for(int i=1;i<=n;i++) b.push_back(a[i]);
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    for(int i=0;i<b.size();i++) newv[b[i]]=i+1;
    for(int i=1;i<=n;i++){
        oldv[newv[a[i]]]=a[i];
        a[i]=newv[a[i]];
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>> n ;
    for(int i=1;i<=n;i++) cin>>a[i];
    nen();
    for(int i=1;i<=n;i++)pos[a[i]].push_back(i);
    cin >> Q;
    reset();
    int logm=32;
    for(int i=1;i<=Q;i++) cin >> q[i].lf >> q[i].rt>> q[i].maxx;
    for(int i=1;i<=Q;i++){
        l[i]=1;r[i]=100000;
        if(q[i].lf==q[i].rt) sol[i]=a[q[i].lf];
    }
    while(logm--){
        reset();
        for(int i=1;i<=Q;i++){
            if(l[i]>r[i]) continue;
            int mid=(l[i]+r[i])/2;
            adj[mid].push_back(i);
        }
        for(int med=100000;med>=1;med--){
            for(auto i:pos[med]) update(1,1,n,i,1);
            for(auto i:adj[med]){
                pl x=find(1,1,n,q[i].lf,q[i].rt);
                if(x.maxx>=q[i].maxx){
                    sol[i]=med;
                    l[i]=med+1;
                }
                else r[i]=med-1;
            }
        }
    }
    for(int i=1;i<=Q;i++) cout << oldv[sol[i]] << "\n";
    return 0;
}
