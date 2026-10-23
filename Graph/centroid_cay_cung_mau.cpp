#include <bits/stdc++.h>
using namespace std;
vector <int> adj[300005];
int sz[300005];
bool vst[300005];
// int depg[200005];
int k;
int color[300005];
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
long long cnt[300005],seen[300005];
long long sum[300005],dep[300005];
vector<int> lit;
void lay(int u, int v){
    // if(minn[color[u]]==0) minn[color[u]]=dep[u];
    sum[color[u]]+=dep[u];
    seen[color[u]]++;
    lit.push_back(color[u]);
    for(auto i:adj[u]){
        if(i==v||vst[i]) continue;
        dep[i]=dep[u]+1;
        lay(i,u);
    }
}
void cal(int u, int v){
    cnt[color[u]]+=seen[color[u]]*dep[u]+sum[color[u]];
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
    // cnt[0]=1; 
    // minn[color[tam]]=0;
    seen[color[tam]]=1;
    lit.push_back(color[tam]); 
    for(auto i:adj[tam]){
        if(vst[i]) continue;
        dep[i]=1;
        cal(i,tam);
        lay(i,tam);
    }
    for(auto i:lit){
         sum[i]=0;
         seen[i]=0;
    }
    for(auto i:adj[tam]) if(!vst[i]) centroi(i,tam);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; //cin >> n >> k;
    readInt(n);
    // readInt(k);
    set<int> color_list;
    
    for(int i=1;i<n;i++){
        int u,v;// cin >> u >> v;
        readInt(u);
        readInt(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i=1;i<=n;i++) {
        int u;readInt(u);
        color[i]=u;
        // readInt(color[i]);
        color_list.insert(color[i]);
        // cnt[color[i]]=INT_MAX;
        // minn[color[i]]=INT_MAX;
    }
    // txl(1,0);
    centroi(1,0);
    for(auto i:color_list) {
        res+=cnt[i];
        // cout << i << " "  << res << endl;
    }
    
    cout << res;
    return 0;
}