#include <bits/stdc++.h>
using namespace std;
int d[100005],w[100005],n,s[100005],sumW[100005],sumSW[100005],opt[100005];
int res=INT_MAX;
int cost(int i, int j) {
    return s[i - 1] * sumW[i - 1] - sumSW[i - 1]
        +  s[j - 1] * (sumW[j - 1] - sumW[i]) - (sumSW[j - 1] - sumSW[i])
        + s[n] * (sumW[n] - sumW[j]) - (sumSW[n] - sumSW[j]);
}
void dnc(int l, int r, int optl,int optr){
    if(l>r) return;
    int mid=(l+r)/2;
    int ans=INT_MAX;
    for(int i=optl;i<=min(mid-1,optr);++i){
        if(ans>cost(i,mid)){
            ans=cost(i,mid);
            opt[mid]=i;
        }
    }
    res=min(res,ans);
    dnc(l,mid-1,optl,opt[mid]);
    dnc(mid+1,r,opt[mid],optr);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i=1;i<=n;i++) {
        cin >> w[i] >> d[i];
        s[i]=s[i-1]+d[i];
        sumW[i]=sumW[i-1]+w[i];
        sumSW[i] = sumSW[i - 1] + s[i - 1] * w[i];
    }
    dnc(1,n,1,n);
    cout << res;
    return 0;
}