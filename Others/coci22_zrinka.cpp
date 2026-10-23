#include <bits/stdc++.h>
using namespace std;
int f[5005][5005],a[5005],b[5005];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m; cin >> n;
    for(int i=1;i<=n;++i)cin >> a[i];
    cin >> m;
    for(int i=1;i<=m;i++) cin >> b[i];
    for(int i=1;i<=n;i++){
        if(!a[i]) {
            if(f[i-1][0]%2==1) f[i][0]=f[i-1][0]+1;
            else f[i][0]=f[i-1][0]+2;
        }
        else{
            if(f[i-1][0]%2==1) f[i][0]=f[i-1][0]+2;
            else f[i][0]=f[i-1][0]+1;
        }
    }
    for(int i=1;i<=m;i++){
        if(!b[i]) {
            if(f[0][i-1]%2==1) f[0][i]=f[0][i-1]+1;
            else f[0][i]=f[0][i-1]+2;
        }
        else{
            if(f[0][i-1]%2==1) f[0][i]=f[0][i-1]+2;
            else f[0][i]=f[0][i-1]+1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int x=0,y=0,z=0;
            if(a[i]!=b[j]) x=f[i-1][j-1]+2;
            else {
                if(f[i-1][j-1]%2==a[i]) x=f[i-1][j-1]+4;
                else x=f[i-1][j-1]+3;
            }
            if(b[j]){
                // cout << j;
                if(f[i][j-1]%2==0) y=f[i][j-1]+1;
                else y=f[i][j-1]+2;
            }
            else {
                if(f[i][j-1]%2==0) y=f[i][j-1]+2;
                else y=f[i][j-1]+1;
            }
            if(a[i]){
                if(f[i-1][j]%2==0) z=f[i-1][j]+1;
                else z=f[i-1][j]+2;
            }
            else{
                if(f[i-1][j]%2==0) z=f[i-1][j]+2;
                else z=f[i-1][j]+1;
            }
            // cout << i << " " << j << ": " << x << " " << y << " " << z << endl;
            f[i][j]=min({x,y,z});
        }
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++) cout << f[i][j] << " ";
    //     cout << "\n";
    // }
    cout << f[n][m];
}