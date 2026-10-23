#include <bits/stdc++.h>
using namespace std;
int par[200005],sz[200005],n,m,Q,l[200005],r[200005];
vector <int> pos[100005],adj[100005];
int st[400005];
void reset(){
    for(int i=1;i<=n;i++){
        sz[i]=1;
        par[i]=i; 
        st[i]=0;
    }
    for(int i=1;i<=100000;i++) adj[i].clear();
}
pair <int, int> q[200005];

int sol[200005],a[200005];

void update (int i, int v){
    for(;i<=n;i+=i&-i) st[i]+=v;
}
int find(int i){
    int s=0;
    for(;i>0;i-=i&-i) s+=st[i];
    return s;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>> n >> Q;
    for(int i=1;i<=n;i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    reset();
    int logm=32;
    for(int i=1;i<=Q;i++) cin >> q[i].first >> q[i].second;
    for(int i=1;i<=Q;i++){
        l[i]=1;r[i]=100000;
        if(q[i].first==q[i].second) sol[i]=a[q[i].first];
    }
    while(logm--){
        reset();
        for(int i=1;i<=Q;i++){
            if(l[i]>r[i]) continue;
            int mid=(l[i]+r[i])/2;
            adj[mid].push_back(i);
        }
        for(int i=1;i<=n;i++) update(i,-1);
        for(int med=100000;med>=1;med--){
            for(auto i:pos[med]) update(i,2);
            for(auto i:adj[med]){
                int x=find(q[i].second)-find(q[i].first-1);
                if(x>0){
                    sol[i]=med;
                    l[i]=med+1;
                }
                else r[i]=med-1;
            }
        }
    }
    for(int i=1;i<=Q;i++) cout << sol[i] << "\n";
    return 0;
}
