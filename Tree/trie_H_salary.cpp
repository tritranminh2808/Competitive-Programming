#include <bits/stdc++.h>
using namespace std;
int n,q;
int salary[200005];
struct node{
    node *childe[2];
    int cnt;
    node(){
        childe[0]=NULL;
        childe[1]=NULL;
        cnt=0;
    }
};
node root;
void update(int &x,node &root,bool ch){
    node *cur=&root;
    for(int i=30;i>=0;--i){
        bool b=(x>>i)&1;
        if(!cur->childe[b]) cur->childe[b]=new node();
        cur=cur->childe[b];
        if(ch)cur->cnt++;
        else cur->cnt--;
    }
}
int find(int &x, node &root){
    if(x<0) return 0;
    node *cur=&root;
    int res=0;
    for(int i=30;i>=0;i--){
        bool b=(x>>i)&1;
        if(b&&cur->childe[0]) res+=cur->childe[0]->cnt;
        if(!cur->childe[b]) return res;
        cur=cur->childe[b];
    }
    return res+cur->cnt;
}
const int mod=1e9+1;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >>n;
    for(int i=0;i<n;i++) {
        int x; cin >> x;
        salary[i]=x;
        update(x,root,1);
    }
    cin >> q;
    int ans=0;
    while(q--){
        int ty; cin>> ty;
        if(ty==1){
            int x,y; cin >> x >> y;
            x=(x+ans)%n;
            y=(y+ans)%mod;
            // if(x==0) x=n;
            int p=salary[x];
            salary[x]=y;
            update(p,root,0);
            update(y,root,1);
        }
        else{
            int x,y; cin >> x >> y;
            // int p=salary[x];
            x--;
            ans=find(y,root) - find(x,root);
            // salary[x]=y;
            cout << ans << "\n";
        }
    }
    return 0;
}