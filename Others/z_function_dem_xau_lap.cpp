#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7,base=257;
int pw[100005],hs[100005];
int get(int l, int r){
    int h = (hs[r+1] - hs[l]*pw[r-l+1]) % mod;
    if(h < 0) h += mod;
    return h;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s; cin >> s;
    int n=s.length();
    pw[0] = 1;
    for(int i = 1; i <= n; i++) pw[i] = pw[i-1] * base % mod;
    hs[0] = 0;
    for(int i = 0; i < n; i++) hs[i+1] = (hs[i]*base + (s[i] + 1)) % mod;
    int ans = 0;
    for(int L = 1; L*2 <= n; L++){
        unordered_map<int,int> cnt;
        for(int j = L; j + L - 1 < n; j++) cnt[get(j, j+L-1)]++;
       
        for(int i = 0; i + 2*L - 1 < n; i++){
            ans += cnt[get(i, i+L-1)];
            cnt[get(i+L, i+2*L-1)]--;
        }
    }
    cout << ans ;

}