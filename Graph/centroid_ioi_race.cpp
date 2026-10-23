#include <bits/stdc++.h>
using namespace std;
vector <pair<int, int > > adj[200005];
int sz[2000005];
bool vst[200005];
// int depg[200005];
int k;
static const int IN_BUF = 1<<20;
static char ibuf[IN_BUF];
static int ipos = 0, ilen = 0;
inline int readChar() {
    if (ipos >= ilen) {
        ilen = (int)fread(ibuf,1,IN_BUF,stdin);
        ipos = 0;
        if (ilen == 0) return EOF;
    }
    return ibuf[ipos++];
}
template<typename T>
bool readInt(T &out) {
    int c;
    do {
        c = readChar();
        if (c == EOF) return false;
    } while (c!='-' && (c<'0' || c>'9'));
    int sign = 1;
    if (c == '-') {
        sign = -1;
        c = readChar();
    }
    long long val = 0;
    while (c >= '0' && c <= '9') {
        val = val*10 + (c - '0');
        c = readChar();
    }
    out = (T)(val * sign);
    return true;
}
string out;
void dfs(int u, int v){
    sz[u]=1;
    for(auto i:adj[u]){
        if(vst[i.first]||i.first==v) continue;
        dfs(i.first,u);
        sz[u]+=sz[i.first];
    }
}
// long long res=0;
int centroid(int u, int v, int x){
    for(auto i:adj[u]){
        if(vst[i.first]||i.first==v) continue;
        if(sz[i.first]>x/2) return centroid(i.first,u,x);
    }
    return u;
}
unordered_map<long long, int> cnt;int dep[200005];
long long dist[200005],res=1e16;
vector<int> lit;
vector <int> lt2;
void lay(int u, int v){
    if(cnt.find(dist[u])==cnt.end()) cnt[dist[u]]=dep[u];
    else cnt[dist[u]]=min(cnt[dist[u]],dep[u]);
    lit.push_back(dist[u]);
    lt2.push_back(u);
    for(auto i:adj[u]){
        if(i.first==v||vst[i.first]) continue;
        dep[i.first]=dep[u]+1;
        dist[i.first]=dist[u]+i.second;
        lay(i.first,u);
    }
}
void cal(int u, int v){
    auto it=cnt.find(k-dist[u]);
    if(it!=cnt.end()) res=min(res,(long long)it->second+dep[u]);
    for(auto i:adj[u]){
        if(i.first==v||vst[i.first]) continue;
        dep[i.first]=dep[u]+1;
        dist[i.first]=dist[u]+i.second;
        cal(i.first,u);
    }
}

void centroi(int u, int v){
    dfs(u,0);
    int x=sz[u];
    int tam=centroid(u,0,x);
    // dep[tam]=0;
    vst[tam]=1;
    lit.clear();
    lt2.clear();
    // memset(cnt,0,sizeof(cnt));
    // memset(dep,0,sizeof(dep));
    cnt[0]=0;   
    for(auto i:adj[tam]){
        if(vst[i.first]) continue;
        dep[i.first]=1;
        dist[i.first]=i.second;
        cal(i.first,tam);
        lay(i.first,tam);
    }
    for(auto i:lit)  cnt[i]=INT_MAX;
    for(auto i:lt2) dist[i]=0;
    for(auto i:adj[tam]) if(!vst[i.first]) centroi(i.first,tam);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; //cin >> n >> k;
    readInt(n);
    readInt(k);
    for(int i=1;i<n;i++){
        int u,v,w;// cin >> u >> v;
        readInt(u);
        readInt(v);
        readInt(w);
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    // for(int i=1;i<=n;i++) cnt[i]=INT_MAX;
    // txl(1,0);
    centroi(1,0);
    if(res>1000000) cout << -1;
    else{
        out+=to_string(res);
        fwrite(out.c_str(), 1, out.size(), stdout);
    }
    // else cout << res;
    return 0;
}