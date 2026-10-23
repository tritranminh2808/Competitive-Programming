#include <bits/stdc++.h>
using namespace std;
vector <int> adj[200005];
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
        if(vst[i]||i==v) continue;
        dfs(i,u);
        sz[u]+=sz[i];
    }
}
long long res=0;
int centroid(int u, int v, int x){
    for(auto i:adj[u]){
        if(vst[i]||i==v) continue;
        if(sz[i]>x/2) return centroid(i,u,x);
    }
    return u;
}
int cnt[200005],dep[200005];
vector<int> lit;
void lay(int u, int v){
    cnt[dep[u]]++;
    lit.push_back(dep[u]);
    for(auto i:adj[u]){
        if(i==v||vst[i]) continue;
        dep[i]=dep[u]+1;
        lay(i,u);
    }
}
void cal(int u, int v){
    if(dep[u]<=k)res+=cnt[k-dep[u]];
    for(auto i:adj[u]){
        if(i==v||vst[i]) continue;
        dep[i]=dep[u]+1;
        cal(i,u);
    }
}

void centroi(int u, int v){
    dfs(u,0);
    int x=sz[u];
    int tam=centroid(u,0,x);
    // dep[tam]=0;
    vst[tam]=1;
    lit.clear();
    // memset(cnt,0,sizeof(cnt));
    // memset(dep,0,sizeof(dep));
    cnt[0]=1;   
    for(auto i:adj[tam]){
        if(vst[i]) continue;
        dep[i]=1;
        cal(i,tam);
        lay(i,tam);
    }
    for(auto i:lit) cnt[i]=0;
    for(auto i:adj[tam]) if(!vst[i]) centroi(i,tam);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; //cin >> n >> k;
    readInt(n);
    readInt(k);
    for(int i=1;i<n;i++){
        int u,v;// cin >> u >> v;
        readInt(u);
        readInt(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // txl(1,0);
    centroi(1,0);
    out+=to_string(res);
    fwrite(out.c_str(), 1, out.size(), stdout);
    // cout << res;
    return 0;
}