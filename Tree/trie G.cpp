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
void add(int s, node *root){
    node *cur=root;
    for(int i=30;i>=0;i--){
        bool g=(s>>i)&1;
        if(!(cur->childe[g])) cur->childe[g]=new node();
        cur=cur->childe[g];
        cur->cnt++;
    }
    
}

int query(int s, node *root){
    node *cur=root;
    int sol=0;
    for(int i=30;i>=0;i--){
        bool g=(s>>i)&1;
        if((cur->childe[1-g])&&cur->childe[1-g]->cnt>0){
            sol|=(1<<i);
            cur=cur->childe[1-g];
        }
        else if((cur->childe[g])&&cur->childe[g]->cnt>0) cur=cur->childe[g];
    }
    return sol;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int q; 
    cin >> q;
    while (q--){
        int n, x;
        cin >> n >> x;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        node *root = new node();
        int sol = 0;
        int pre= 0;
        add(0,root); 
        for (int v : a){ 
            pre ^= v;
            sol = max(sol, query(pre^x,root));
            add(pre,root);
        }
        cout << (sol^x) << "\n";
    }
    return 0;
}
