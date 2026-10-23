#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[1000005],pre[100005],pre2[100005];
int cost(int i, int j){
    return pre2[j]-pre2[i-1]-(pre[j]-pre[i-1])*i;
}
int f[20][100005];
int q[100005];
long long cal(int& j, int& k, int t) {
    return (f[t][j]-f[t][k]+pre2[j]-pre2[k])/(k-j);
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,k; cin >> n >> k;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) {
        pre[i]=pre[i-1]+a[i];
        pre2[i]=pre2[i-1]+a[i]*i;
    }
    for(int i=1;i<=n;i++) f[0][i]=1e18;
    int l=0,r=0,cur=1,prev=0;
    for(int i=n;i;i--) for(int j=i-1;j;j--) cout << cal(j,i,0)  << "\n";
    for(int x=1;x<=k;x++){
        for(int i=n;i;--i){
            for(int j=n;j)
        }
    }
    cout << f[prev][1];
    return 0;
}