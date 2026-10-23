#include <bits/stdc++.h>
using namespace std;
vector <int> adj[200005];
int sz[2000005];
bool vst[200005];
// int depg[200005];
int c[200005];
int k1,k2,n;
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
long long res[200005];
int centroid(int u, int v, int x){
    for(auto i:adj[u]){
        if(vst[i]||i==v) continue;
        if(sz[i]>x/2) return centroid(i,u,x);
    }
    return u;
}
// int maxx=0;
int st[400005],dep[200005];
vector<int> lit;
void update(int i, int v){
    for(;i<=n+5;i+=i&-i) st[i]+=v;
}
int find(int i){
    int res=0;
    for(;i>0;i-=i&-i) res+=st[i];
    return res;
}
void lay(int u, int v){
    // update(dep[u]+1,1);
    int dist=c[u]-dep[u];
    if (dist>=0) {     
        update(dist+1,1);
        lit.push_back(dist+1);
    }
    for(auto i:adj[u]){
        if(i==v||vst[i]) continue;
        dep[i]=dep[u]+1;
        lay(i,u);
    }
}
vector <int> se;
void xoa(int u, int v){
    int dist=c[u]-dep[u];
    if(dist>=0){
        update(dist+1,-1);
        se.push_back(dist+1);
    }
    for(auto i: adj[u]){
        if(i==v||vst[i]) continue;
        dep[i]=dep[u]+1;
        xoa(i,u);
    }
}
void cal(int u, int v){
    int rt=dep[u]+1;
    res[u]+=find(n+5)-find(dep[u]);
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
    dep[tam]=0;
    vst[tam]=1;
    // cout << tam << endl;
    lit.clear();
    // memset(cnt,0,sizeof(cnt));
    // memset(dep,0,sizeof(dep));
    update(c[tam]+1,1);
    lit.push_back(c[tam]+1);
    // res[tam] += find(min(c[tam], n) + 1) - find(0);
    for(auto i:adj[tam]){
        if(vst[i]) continue;
        dep[i]=1;
        lay(i,tam);   
    }
    
    for(auto i:adj[tam]){
        if(vst[i]) continue;
        dep[i]=1;
        xoa(i,tam);  
        dep[i]=1;
        cal(i,tam);
        for(auto j:se) update(j,1);
        se.clear(); 
    }
    update(c[tam]+1,-1);
    res[tam]+=find(n+5);
    for (int i:lit){
        while(i<=n+5 and st[i]!=0){
            st[i] = 0;
            i += (i & (-i));
        }
    }
    // for(int pos:lit) update(pos, -1);
// lit.clear();
    for(auto i:adj[tam]) if(!vst[i]) centroi(i,tam);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //cin >> n >> k;
    readInt(n);
    for(int i=1;i<=n;i++){
        int u; readInt(u);
        c[i]=u;
    }
    for(int i=1;i<n;i++){
        int u,v;// cin >> u >> v;
        readInt(u);
        readInt(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // txl(1,0);
    centroi(1,0);
    for(int i=1;i<=n;i++) cout << res[i] << " ";
    // cout << res;
    return 0;
}
