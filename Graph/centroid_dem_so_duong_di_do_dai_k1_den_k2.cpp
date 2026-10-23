#include <bits/stdc++.h>
using namespace std;
vector <int> adj[200005];
int sz[2000005];
bool vst[200005];
// int depg[200005];
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
long long res=0;
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
    int j=dep[u]+1;
    for(;j<=n+5;j+=j&-j) st[j]++;
    // st[dep[u]]++;
    lit.push_back(dep[u]+1);
    for(auto i:adj[u]){
        if(i==v||vst[i]) continue;
        dep[i]=dep[u]+1;
        lay(i,u);
    }
}
void cal(int u, int v){
    int lf=max(0,k1-dep[u]);
    int rt=k2-dep[u];
    if(lf<=rt) res+=find(rt+1)-find(lf);
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
    update(1,1);  
    lit.push_back(1);
    for(auto i:adj[tam]){
        if(vst[i]) continue;
        dep[i]=1;
        cal(i,tam);
        lay(i,tam);
    }
    for (int i:lit){
        while(i<=n+5 and st[i]!=0){
            st[i] = 0;
            i += (i & (-i));
        }
    }
    for(auto i:adj[tam]) if(!vst[i]) centroi(i,tam);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //cin >> n >> k;
    readInt(n);
    readInt(k1);
    readInt(k2);
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
