#include <bits/stdc++.h>
using namespace std;
int a[10005];
int dep[10005];
void dnc(int l, int r, int cnt){
    if(l>r) return;
    // cout << l << " " << r << "\n";
    int val=0,pos=0;
    for(int i=l;i<=r;i++){
        if(a[i]>val){
            val=a[i];
            pos=i;
        }
    }
    dep[pos]=cnt;
    dnc(l,pos-1,cnt+1);
    dnc(pos+1,r,cnt+1);
}
void cok(){
    int n; cin >> n;
    for(int i=1;i<=n;i++) {
        cin >> a[i];
        dep[i]=0;
    }
    dnc(1,n,0);
    for(int i=1;i<=n;i++) cout << dep[i] << " ";
    cout << "\n";
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