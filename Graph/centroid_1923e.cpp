#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n;
int color[N], sz[N];
bool vst[N];
vector<int> adj[N];
long long ans=0;
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

int cnt[N], fr[N];

void dfs(int u,int p){
    sz[u]=1;
    for(auto v: adj[u]){
        if(v==p || vst[v]) continue;
        dfs(v,u);
        sz[u]+=sz[v];
    }
}
int find_cen(int u,int p,int tot){
    for(auto v: adj[u]){
        if(v==p || vst[v]) continue;
        if(sz[v]>tot/2) return find_cen(v,u,tot);
    }
    return u;
}

void collect(int u,int p,int cent, vector<int>& S){
    if(fr[color[u]]==0 && color[u]!=color[cent]) S.push_back(color[u]);
    fr[color[u]]++;
    for(auto v: adj[u]){
        if(v==p || vst[v]) continue;
        collect(v,u,cent,S);
    }
    fr[color[u]]--;
}

int count_end(int u,int p,int cent){
    int res=0;
    if(fr[color[u]]==0 && color[u]==color[cent]) res++;
    fr[color[u]]++;
    for(auto v: adj[u]){
        if(v==p || vst[v]) continue;
        res += count_end(v,u,cent);
    }
    fr[color[u]]--;
    return res;
}

void centroi(int s){
    dfs(s,0);
    int tot = sz[s];
    int tam = find_cen(s,0,tot);
    vst[tam]=1;

    vector<int> used;
    for(auto v: adj[tam]){
        if(vst[v]) continue;
        vector<int> S;
        collect(v,tam,tam,S);
        for(auto c: S) ans += cnt[c];
        for(auto c: S){
            if(cnt[c]==0) used.push_back(c);
            cnt[c]++;
        }
    }
    for(auto c: used) cnt[c]=0;

    for(auto v: adj[tam]){
        if(vst[v]) continue;
        ans += count_end(v,tam,tam);
    }

    for(auto v: adj[tam]){
        if(!vst[v]) centroi(v);
    }
}

void cok(){
    readInt(n);
    ans=0;
    for(int i=1;i<=n;i++){
        adj[i].clear();
        vst[i]=0;
    }
    memset(cnt,0,sizeof(int)*(n+5));
    memset(fr,0,sizeof(int)*(n+5));
    for(int i=1;i<=n;i++){
        int k; readInt(k); color[i]=k;
    }
    for(int i=1;i<n;i++){
        int u,v; readInt(u); readInt(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    centroi(1);
    cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; readInt(T);
    while(T--) cok();
    return 0;
}
