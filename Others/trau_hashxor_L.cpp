#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("input.inp","r",stdin);
    freopen("output.ans","w",stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,t; cin >> n >> t;
    vector <int> a(n+1),b(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> b[i];
    while(t--){
        int l,r,u,v; cin >> l >> r >> u >> v;
        vector <int> t1,t2;
        for(int i=l;i<=r;i++) t1.push_back(a[i]);
        for(int i=u;i<=v;i++) t2.push_back(b[i]);
        sort(t1.begin(),t1.end());
        t1.erase(unique(t1.begin(),t1.end()),t1.end());
        sort(t2.begin(),t2.end());
        t2.erase(unique(t2.begin(),t2.end()),t2.end());
        if(t1.size()!=t2.size()) cout << "NO\n";
        else{
                bool ch=1;
            for(int i=0;i<t1.size();i++){
                if(t1[i]!=t2[i]){
                    ch=0;
                    cout << "NO\n";
                    break;
                }

            }
            if(ch) cout << "YES\n";
        }
    }
}

