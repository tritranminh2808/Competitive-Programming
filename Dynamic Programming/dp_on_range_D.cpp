#include <bits/stdc++.h>
#define int long long
using namespace std;
int dp[305][305][155];
int a[305];
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,k; cin>> n>> k;
    int sol=0;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int len=1;len<=n;len++){
        for(int l=1;l<=n-len+1;l++){
            int r=l+len-1;
            if(len==2){
            	dp[l][r][1] = abs(a[l]-a[r]);
            	continue;
            }
            for(int p=1;p<=k;p++){
                
                //lay 2 thang o dau
                if(len>=2)dp[l][r][p]=max(dp[l][r][p],dp[l+2][r][p-1]+abs(a[l]-a[l+1]));
                //lay 2 thang o cuoi
                if(len>=2) dp[l][r][p]=max(dp[l][r][p],dp[l][r-2][p-1]+abs(a[r]-a[r-1]));
                // lay thang dau cuoi
                if(len>=2) dp[l][r][p]=max(dp[l][r][p],dp[l+1][r-1][p-1]+abs(a[r]-a[l]));
                //loai thang o dau
                dp[l][r][p]=max(dp[l][r][p],dp[l+1][r][p]);
                //loai thang o sau
                dp[l][r][p]=max(dp[l][r][p],dp[l][r-1][p]);
            }

        }
    }
    cout << dp[1][n][k];
    return 0;
}