#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,p,q;
int a[2005];
long long res=1000000005;
int dp[2205][2205];
bool check(int k){
    if(n==1&&p+q>0) return true;
    vector <int> nxts(n+105),nxtl(n+105);
    for(int i=1;i<=n;i++){
        nxts[i]=lower_bound(a+1,a+n+1,a[i]+k)-a;
        nxtl[i]=lower_bound(a+1,a+n+1,a[i]+2*k)-a;
    }
    nxts[n+1]=n+1;
    nxtl[n+1]=n+1;
    for(int i=1;i<=n+105;i++){
        for(int j=0;j<=p+105;j++) dp[i][j]=1e16;
    }
    dp[1][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=p;j++){
            if(dp[i][j]>=1e16) continue;
            if(nxtl[i]<=n+1) dp[nxtl[i]][j]=min(dp[nxtl[i]][j],dp[i][j]+1);
            if(j<p){
                if(nxts[i]<=n+1) dp[nxts[i]][j+1]=min(dp[nxts[i]][j+1],dp[i][j]);
            }
            
        }
    }
    for(int i=0;i<=p;i++){
        if(dp[n+1][i]<=q) return true;
    }
    return false;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> p >> q;
    if(p>n){
        cout << 1;
        return 0;
    }
    p=min(p,n);
    for(int i=1;i<=n;i++) cin >> a[i];
    sort(a+1,a+n+1);
    // a[0]=a[1];
    int l=1;
    long long r=1000000000;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)) {
            res=mid;
            r=mid-1;
        }
        else l=mid+1;
    }
    cout << res;
    return 0;
}