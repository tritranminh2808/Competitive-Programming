#include <bits/stdc++.h>
using namespace std;
string s;
int ans=0;
int dnc(int l, int r, int go){
    if(l==r) return s[l]-'a'!=go;
    int mid=(l+r)/2;
    int cl=0,cr=0;
    for(int i=l;i<=mid;i++) if(s[i]-'a'!=go) cl++;
    for(int i=mid+1;i<=r;i++) if(s[i]-'a'!=go) cr++;
    return min(dnc(mid+1,r,go+1)+cl,cr+dnc(l,mid,go+1));
}
void cok(){
    int n; cin >> n;
    cin >> s;
    s='!'+s;
    // ans=0;
    cout << dnc(1,n,0) << "\n";
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