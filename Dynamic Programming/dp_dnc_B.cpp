#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[100005],w[100005],n,s[100005],opt[100005],k;
int dp[8005][805];
const long long inf=1000000000000000000LL;
// dp[i][j] : chi phi toi thieu de kiem soat i phong voi j quan nguc
// dp[i][j]=min(dp[t][j-1]+cost(t+1,i))
int cost(int i, int j) {
    return (s[j]-s[i-1])*(j-i+1);
}
void dnc(int l, int r, int optl,int optr,int x){
    if(l>r) return;
    int mid=(l+r)/2;
    dp[mid][x]=inf;
    opt[mid]=optl;
    for(int i=max(optl,x);i<=min(mid,optr);++i){
        if(dp[i-1][x-1]>=inf) continue;
        if(dp[mid][x]>dp[i-1][x-1]+cost(i,mid)){
            dp[mid][x]=dp[i-1][x-1]+cost(i,mid);
            opt[mid]=i;
        }
    }
    dnc(l,mid-1,optl,opt[mid],x);
    dnc(mid+1,r,opt[mid],optr,x);
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for(int i=0;i<=n;i++) for(int j=0;j<=k;j++)dp[i][j]=inf;
    dp[0][0]=0;
    for(int i=1;i<=n;i++) {
        cin >> a[i];
        s[i]=s[i-1]+a[i];
    }
    for(int i=1;i<=n;i++) dp[i][1] = (s[i]-s[0]) * i;   
    
    for(int i=2;i<=min(k,n);i++) dnc(i,n,1,n,i);
    cout << dp[n][min(n,k)];
    return 0;
}