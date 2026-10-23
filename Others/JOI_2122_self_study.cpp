#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int a[300005],b[300005];
bool check(int x){
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(a[i]<=b[i]) cnt+=(x+b[i]-1)/b[i];
        else{
            if(a[i]*m>=x) cnt+=(x+a[i]-1)/a[i];
            else{
                int k=x-a[i]*m;
                cnt+=m;
                cnt+=(k+b[i]-1)/b[i];
            }
        }
        if(cnt>n*m) return false;
    }
    return true;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> b[i];
    int l=0,r=1e18;
    int ans=0;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            l=mid+1;
        }
        else r=mid-1;
    }
    cout << ans;
    return 0;
}