#include <bits/stdc++.h>
using namespace std;
int a[300005];
int ans=0;
void dnc(int l, int r){
    if(l>=r) return;
    // cout << l << " " << r << "\n";
    int mid=(l+r)/2;
    int ml=0,mr=0;
    for(int i=l;i<=mid;i++) ml=max(ml,a[i]);
    for(int i=mid+1;i<=r;i++) mr=max(mr,a[i]);
    if(ml>mr){
        ans++;
        for(int i=0;i<=mid-l;i++)swap(a[l+i],a[mid+1+i]);
    }
    dnc(l,mid);
    dnc(mid+1,r);
}
void cok(){
    int n; cin >> n;
    ans=0;
    for(int i=1;i<=n;i++) {
        cin >> a[i];
    }
    dnc(1,n);
    if(is_sorted(a+1,a+n+1)) cout << ans << "\n";
    else cout << "-1\n";
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    while(t--){
        cok();
    }
    return 0;
}