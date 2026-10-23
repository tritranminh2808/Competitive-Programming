#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,k,t;
int a[50005];
int maxx=1e5+5;
struct pl{
    int id, l, r;
};
pl q[50005];
int sqr;
bool cmp(pl x, pl y){
    if(x.l/sqr!=y.l/sqr)return x.l/sqr<y.l/sqr;
    return x.r>y.r;
}
int st[200005];
void update(int i, int v){
    for(;i<=maxx;i+=i&-i) st[i]+=v;
}
int find(int i){
    int res=0;
    if(i>maxx) i=maxx;
    for(;i>0;i-=i&-i) res+=st[i];
    return res;
}
int cal(int v){
    int l=v-k+1,r=v+k-1;
    if(l>r||r<1||l>maxx||k==0) return 0;
    // if(v+k-1<v-k) return 0;
    l=max((int)1,l);
    r=min(maxx,r);
    return find(r)-find(l-1);
}
long long ans[100005];
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> t >> k;
    sqr=sqrt(n);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=1;i<=t;i++){
        cin >> q[i].l >> q[i].r;
        q[i].l--;
        q[i].r--;
        q[i].id=i;
    }
    sort(q+1,q+t+1,cmp);
    long long cnt=0;
    for(int i=q[1].l;i<=q[1].r;i++){
        cnt+=cal(a[i]+1);
        update(a[i]+1,1);
    }
    int s=(q[1].r-q[1].l+1);
    if(k>0){
        ans[q[1].id]=s*(s-1)/2;
        ans[q[1].id]-=cnt;
    }
    else    ans[q[1].id]=s*(s+1)/2;
    
    for(int i=2;i<=t;i++){
        if(q[i].l>q[i-1].l){
            for(int j=q[i-1].l;j<q[i].l;j++){
                update(a[j]+1,-1);
                cnt-=cal(a[j]+1);
            }
        }
        else if(q[i].l<q[i-1].l){
            for(int j=q[i].l;j<q[i-1].l;j++){
                cnt+=cal(a[j]+1);
                update(a[j]+1,1);
            }
        }
        if(q[i].r>q[i-1].r){
            for(int j=q[i-1].r+1;j<=q[i].r;j++){
                cnt+=cal(a[j]+1);
                update(a[j]+1,1);
            }
        }
        else if(q[i].r<q[i-1].r){
            for(int j=q[i].r+1;j<=q[i-1].r;j++){
                update(a[j]+1,-1);
                cnt-=cal(a[j]+1);
            }
        }
        int m=q[i].r-q[i].l+1;
        if(k>0){
            ans[q[i].id]=m*(m-1)/2;
            ans[q[i].id]-=cnt;
        }
        else     ans[q[i].id]=m*(m+1)/2;
        
        
    }
    for(int i=1;i<=t;i++) cout << ans[i] << "\n";
    return 0;
}