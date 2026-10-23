#include <bits/stdc++.h>
#define int long long 
using namespace std;
int n,k,a[100005],dp[200005],pre[200005];
const int mod=1e9+7;
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for(int i=1;i<=n;i++) cin >> a[i];
    unordered_map<long long,int > st;
    int sum=1;
    dp[0]=1;
    pre[0]=1;
    int id=1;
    for(int i=1;i<=n;i++){
        st[a[i]]++;
       
            while(st.size()>k){
                st[a[id]]--;
                if(st[a[id]]==0) st.erase(a[id]);
                id++;
            }
        int sech=0;
        if(id>=2) sech=pre[id-2];
        dp[i]=(pre[i-1]-sech+mod)%mod;
        pre[i]=(pre[i-1]+dp[i])%mod;
    }
    cout << dp[n];
    return 0;
}