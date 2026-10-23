#include <bits/stdc++.h>
using namespace std;
int st[1000005];
void update(int i, int v){
	for(;i<=1000000;i+=i&-i) st[i]+=v;
}
int find(int x){
	int s=0;
	for(int i=x;i>0;i-=i&-i) s+=st[i];
	return s;
}
int a[100005],pre[100005];
const int hang=1e5+1;
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,x; cin >>n >> x ;
    for(int i=1;i<=n;i++){
        int u; cin >> u;
        if(u<x) a[i]=-1;
        else a[i]=1;
        pre[i]=pre[i-1]+a[i];
    }
    long long sol=0;
    update(0+hang,1);
    for(int i=1;i<=n;i++){
        sol+=find(pre[i]+hang);
        update(pre[i]+hang,1);
    }
    cout << sol;
    return 0;
	
}
