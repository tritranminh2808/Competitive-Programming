#include <bits/stdc++.h>
using namespace std;
string a;
struct pl{
    int sum,pre,suf,res;
};
pl st[2000005];
pl merge(pl a, pl b){
    pl c;
    c.sum=a.sum+b.sum;
    c.pre=max(a.pre,a.sum+b.pre);
    c.suf=max(b.suf,b.sum+a.suf);
    c.res=max({b.sum+a.res,a.sum+b.res,a.pre+b.suf});
    return c;
}
void build(int id, int l, int r){
    if(l==r){
        if(a[l]=='T') st[id]={1,1,1,1};
        else st[id]={-1,0,0,0};
        return;
    }
    int mid=(l+r)/2;
    build(id*2,l,mid);
    build(id*2+1,mid+1,r);
    st[id]=merge(st[id*2],st[id*2+1]);
}
pl find(int id, int l,int r,int lf,int rt){
    if(lf>r||rt<l) return {0,0,0,0};
    if(lf<=l&&rt>=r) return st[id];
    int mid=(l+r)/2;
    return merge(find(id*2,l,mid,lf,rt),find(id*2+1,mid+1,r,lf,rt));
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;  cin >> n;
    // sqr=sqrt(n);
    cin >> a;
    a='!'+a;
    build(1,1,n);
    cin >> m;
    while(m--){
        int l,r; cin >> l >> r;
         cout << find(1,1,n,l,r).res << "\n";
    }
    return 0;
}