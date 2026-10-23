#include <bits/stdc++.h>
#define int long long
using namespace std;
int dp[5005][5005];
int a[5005],opt[5005][5005],pre[5005];
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; cin>> n;
    for(int i=1;i<=n;i++) cin>> a[i];
    for(int i=1;i<=n;i++){
        opt[i][i]=i;
        pre[i]=pre[i-1]+a[i];
    }
    for(int len=2;len<=n;len++){
        for(int l=1;l<=n-len+1;l++){
            int r=l+len-1;
            dp[l][r]=1e16;
            for(int j=opt[l][r-1];j<=opt[l+1][r];j++) {
                int cal=dp[l][j]+dp[j+1][r]+pre[r]-pre[l-1];
                if(dp[l][r]>cal){
                    opt[l][r]=j;
                    dp[l][r]=cal;
                }
            }
        }
    }
    cout << dp[1][n];
    return 0;
}