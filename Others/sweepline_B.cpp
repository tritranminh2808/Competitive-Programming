#include <bits/stdc++.h>
using namespace std;
using ldb=long double;
using ll=long long;
struct pl{
    ll x,y;
    int id;
    bool operator < (const pl &other){
        if(x!=other.x) return x<other.x;
        return y<other.y;
    }
};
pl a[500005];
bool cmp(pl u, pl v){
    return u.x<v.x;
}
ll cal(pl u, pl v){
    return (u.x-v.x)*(u.x-v.x)+(u.y-v.y)*(u.y-v.y);
}
struct cc{
    bool operator () (const pl &u,const pl &v) const{
        if(u.y!=v.y) return u.y<v.y;
        return u.x<v.x;
    }
};
set <pl,cc> st;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    for(int i=1;i<=n;i++) {
        cin >> a[i].x >> a[i].y;
        a[i].id=i;
    }
    ll dist=cal(a[1],a[2]);
    
    int r1=1,r2=2;
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        ll x=a[i].x,y=a[i].y;
        int id=a[i].id;
        ll d=sqrtl(dist);
        pl cur={-1000000,y-d,id};
        while(1){
            auto it=st.upper_bound(cur);
            if(it==st.end()) break;
            cur=*it;
            if(cur.y>y+d) break; 
            if(cur.x<x-d) {
                st.erase(it);
                continue;
            }
            if(cal(a[i],cur)<dist){
                dist=cal(a[i],cur);
                r1=id;r2=cur.id;
            }
        }
        st.insert(a[i]);   
    }
    if(r1>r2) swap(r1,r2);
    cout << r1 -1<< " " << r2-1 << " ";
    cout << fixed << setprecision(6) << sqrtl(dist);
    return 0;
}