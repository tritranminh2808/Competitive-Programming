#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
int rnd(int l, int r){
    return l+rng()%(r-l+1);
}
int main(){
    freopen("input.inp","w",stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n=3000,t=3000;
    vector <int> a(5001),b(5001);
    for(int i=1;i<=n;i++) b[i]=rnd(1,10);
    for(int i=1;i<=n;i++) a[i]=rnd(1,10);
    cout << n << " " << t <<"\n";
    for(int i=1;i<=n;i++) cout << a[i] << " ";
    cout << "\n";
    for(int i=1;i<=n;i++) cout << b[i] << " ";
    cout << "\n";
    while(t--){
        int l=rnd(1,n);
        int r=rnd(l,n);
        int l2=rnd(1,n);
        int r2=rnd(1,n);
        cout << l << " "<< r << " " << l2 << " " << r2 << "\n";
    }
}
