#include <bits/stdc++.h>
using namespace std;
using ll=long long;
struct node{
    node *trai,*phai;
    ll val;
    int lazy;
    node(){
        trai=NULL;
        phai=NULL;
        val=0;
        lazy=0;
    }
};
void dat(node *&x,ll l, ll r){
    if(!x) x=new node();
    x->val=r-l+1;
    x->lazy=1;
}
void push(node *x,ll l, ll r){
    if(!x||!x->lazy) return;
    ll mid=(l+r)/2;
    dat(x->trai,l,mid);
    dat(x->phai,mid+1,r);
    x->lazy=0;
}
void update(node *&cur, ll l, ll r, ll lf, ll rt){
    if(lf>r||rt<l) return;
    if(!cur) cur=new node();
    if(lf<=l&&rt>=r){
        dat(cur,l,r);
        return;
    }
    push(cur,l,r);
    int mid=(l+r)/2;
    update(cur->trai,l,mid,lf,rt);
    update(cur->phai,mid+1,r,lf,rt);
    cur->val=0;
    if(cur->trai) cur->val+=cur->trai->val;
    if(cur->phai) cur->val+=cur->phai->val;
}
ll find(node *root, ll l, ll r, ll lf, ll rt){
    node *cur=root;
    if(!cur||lf>r||rt<l) return 0;
    if(lf<=l&&rt>=r)return cur->val;
    push(cur,l,r);
    int mid=(l+r)/2;
    return find(cur->trai,l,mid,lf,rt) + find(cur->phai,mid+1,r,lf,rt);
}
node* root=NULL;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int q;
    cin>> q;
    ll c=0;
    while(q--){
        int ty,l,r; cin>> ty >> l >> r;
        if(ty==2) update(root,1,1000000000,l+c,r+c);
        else{
            int x=find(root,1,1000000000,l+c,r+c);
            cout << x << "\n";
            c=x;
        }
    }
}