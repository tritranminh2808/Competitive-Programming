#include <bits/stdc++.h>
// #define int long long
using namespace std;
int n,m;
vector <pair <int, int > > adj[1000005];
int num[1000005],low[1000005],del[1000005],comp[1000005];
int cntc=0;
int timer=0;
stack <int> st;
void dfs(int u){
    num[u]=low[u]=++timer;
    st.push(u);
    for(auto i:adj[u]){
        if(del[i.first]) continue;
        if(num[i.first]) low[u]=min(low[u],num[i.first]);
        else{
            dfs(i.first);
            low[u]=min(low[u],low[i.first]);
        }
    }
    if(low[u]==num[u]){
        int v;
        ++cntc;
        do{
            v=st.top();
            st.pop();
            del[v]=1;
            
            comp[v]=cntc;
        }while(v!=u);
    }
}
int deg[1000005];
long long rau[1000005];
struct pl{
    int u,v;
    long long w;
};
vector <pl > edge;
long long gain(long long x){
    long long t= (sqrtl(x*8+1)+1)/2;
    while(t&&(long long)(t-1)*t/2>=x) --t;
    if(t==0) return 0;
    long long res=(long long)t*x-(long long)t*(t+1)*(t-1)/6;
    return (long long)res;
}
vector <pair <int ,int > > ascc[1000005];
vector <int> topo;
int vst[1000005];
bool lap=0;
void dfs2(int u){
    vst[u]=1;
    for(auto i:ascc[u]){
        if(vst[i.first]==0){
            dfs2(i.first);
            if(lap) return;
        }
        else if(vst[i.first]==1){
            lap=1;
            return;
        }
    }
    vst[u]=2;
    topo.push_back(u);
}
long long f[1000005];
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v,w; 
        cin >> u >> v >> w;
        edge.push_back({u,v,w});
        adj[u].push_back({v,w});
    }
    for(int i=1;i<=n;i++) if(!num[i]) dfs(i);
    int s; cin >> s;
    vector< tuple<int,int,long long> > cond;
    cond.reserve(edge.size());
    for(auto &e : edge){
        int cu = comp[e.u];
        int cv = comp[e.v];
        if(cu == cv){
            rau[cu] += gain(e.w);
        } else {
            cond.emplace_back(cu, cv, e.w);
        }
    }
    sort(cond.begin(), cond.end(), [](const auto &A, const auto &B){
        if(get<0>(A) != get<0>(B)) return get<0>(A) < get<0>(B);
        if(get<1>(A) != get<1>(B)) return get<1>(A) < get<1>(B);
        return get<2>(A) < get<2>(B);
    });

    for(size_t i=0; i<cond.size(); ){
        int cu = get<0>(cond[i]);
        int cv = get<1>(cond[i]);
        long long best = get<2>(cond[i]);
        size_t j = i + 1;
        while(j < cond.size() && get<0>(cond[j])==cu && get<1>(cond[j])==cv){
            best = max(best, get<2>(cond[j]));
            ++j;
        }
        ascc[cu].push_back({cv, best});
        i = j;
    }
    dfs2(comp[s]);
    for(int i=1;i<=cntc;i++) f[i]=-1e18;
    // reverse(topo.begin(),topo.end());
    for(auto u:topo){
        // int u=topo[i];
        f[u]=rau[u];
        for(auto j:ascc[u]) f[u]=max(f[u],rau[u]+j.second+f[j.first]);
    }
    cout << f[comp[s]];
}