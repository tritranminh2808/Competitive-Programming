#include <bits/stdc++.h>
#define int long
using namespace std;
using ll=long long;
int st[200005],n,q,s,t,a[200005];
void update(int i, int v){
    for(;i<=n;i+=i&-i) st[i]+=v;
}
int find(int i){
    long long s=0;
    for(;i>0;i-=i&-i)  s+=st[i];
    return s;
}
int cal(int u, int v){
    if(v>u) return -(v-u)*s;
    return (u-v)*t;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q >> s >> t;
    for(int i=0;i<=n;i++) cin >> a[i];
    int res=0;
    for(int i=1;i<=n;i++) res+=cal(a[i-1],a[i]);
    while(q--){
        int l,r,x; cin >>  l >> r>> x;
        if(l>0) res-=cal(a[l-1]+find(l-1),a[l]+find(l));
        if(r<n) res-=cal(a[r]+find(r),a[r+1]+find(r+1));
        update(l,x);
        update(r+1,-x);
        if(l>0) res+=cal(a[l-1]+find(l-1),a[l]+find(l));
        if(r<n) res+=cal(a[r]+find(r),a[r+1]+find(r+1));
        cout << res << "\n";
    }
    return 0;
}