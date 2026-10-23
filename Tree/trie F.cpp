#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node{
    node *childe[2];
    int cnt,val;
    node(){
        cnt=0;
        childe[0]=NULL;
        childe[1]=NULL;
    }
};
node root;
void add(int &s, node &root){
    node *cur=&root;
    for(int i=30;i>=0;i--){
        bool g=(s>>i)&1;
        if(!(cur->childe[g])) cur->childe[g]=new node();
        cur=cur->childe[g];
        cur->cnt++;
    }
    
}
void remove(int &s, node &root){
    node *cur=&root;
    for(int i=30;i>=0;i--){
        bool g=(s>>i)&1;
        if(!(cur->childe[g])) return;        
        cur=cur->childe[g];
        cur->cnt--;
    }
    
}
int query(int &k, node &root){
    node *cur=&root;
    int sol=0;
    for(int i=30;i>=0;i--){
        if(cur->childe[0])   k-=cur->childe[0]->cnt;
        if(k<0) return sol;
        if(cur->childe[1]&& k>cur->childe[1]->cnt){
            sol|=(1<<i);
            k-=cur->childe[1]->cnt;
            cur=cur->childe[1];
        }
        else if(cur->childe[0]&&k<0) cur=cur->childe[0];
        else return -1;
    }
    return sol;
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >>n;
    while(n--){
        int u; cin >> u;
        add(u,root);
    }
    int q; cin >> q;
    int stt=0;
    add(stt,root);
    while(q--){
        int typ;int u;
        cin >> typ >> u;
        if(typ==3) add(u,root);
        else {
            
            int sol=query(u,root);
            if(typ==2) remove(sol,root);
            else cout << sol << "\n";
        }
    }
}