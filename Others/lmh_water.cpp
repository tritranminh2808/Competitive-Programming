#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[1005][1005];
bool vst[1005][1005];
int n,m;
int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
int cnt=0;
void dfs(int i, int j){
    cnt++;
    vst[i][j]=1;
    // cout << i << " " << j << "\n";
    for(int k=0;k<4;k++){
        int newx=i+dx[k],newy=j+dy[k];
        if(newx<n && newx>1 && newy<m && newy>1&&a[i][j]==a[newx][newy]&&!vst[newx][newy]) dfs(newx,newy); 
    }
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    if(n<=2||m<=2){
        cout << 0;
        return 0;
    }
    int maxH=1e6;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)cin>> a[i][j];
    }
    for(int i=1;i<=n;i++)maxH=min({maxH,a[i][1],a[i][m]});
    for(int i=1;i<=m;i++) maxH=min({maxH,a[1][i],a[n][i]});
    int S=maxH*(n-2)*(m-2);
    cout << maxH;
    // cout << S;
    for(int i=2;i<n;i++){
        for(int j=2;j<m;j++){
            if(!vst[i][j]){
                cnt=0;
                dfs(i,j);
                S-=cnt*min(a[i][j],maxH);
            }
        }
    }
    // cout << S;
    return 0;
}