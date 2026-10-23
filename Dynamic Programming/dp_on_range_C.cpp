#include <bits/stdc++.h>
using namespace std;
int dp[350][350];
char a[350];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    int n=s.length();
    int sol=0;
    for(int i=1;i<=n;i++) {
        a[i]=s[i-1];
    }
    for(int i=1;i<=n;i++) dp[i][i]=1;
    for(int len=2;len<=n;len++){
        for(int l=1;l<=n-len+1;l++){
            int r=l+len-1;
            dp[l][r]=1+dp[l+1][r];
            if(a[l]=='('||a[l]=='{'||a[l]=='['){
                for(int k=l+1;k<=r;k++) {
                    if((a[l]=='('&&a[k]==')') ||(a[l]=='{'&&a[k]=='}')||(a[l]=='['&&a[k]==']')){
                        dp[l][r]=min(dp[l][r],dp[l+1][k-1]+dp[k+1][r]);
                    }
                }
            }
        }
    }
    cout << dp[1][n];
    return 0;
}