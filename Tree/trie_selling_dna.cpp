#include <bits/stdc++.h>
using namespace std;
struct node1{
    node1 *child[4];
    int l,r;
    node1(){
        for(int i=0;i<4;i++) child[i]=NULL;
        l=INT_MAX,r=-1;
    }
};
struct node2{
    node2 *child[4];
    vector <int> pos;
    node2(){
        for(int i=0;i<4;i++) child[i]=NULL;
    }
};
node1 trie1;
node2 trie2;
int cha(char c){
    if(c=='A') return 0;
    if(c=='G') return 1;
    if(c=='C') return 2;
    return 3;
}
void update1(string &s, node1 &root,int id){
    node1 *cur=&root;
    for(auto i:s){
        int c=cha(i);
        if(!cur->child[c]) cur->child[c]=new node1();
        cur=cur->child[c];
        cur->l=min(cur->l,id);
        cur->r=max(cur->r,id);
    }
}   
void update2(string &s, node2 &root,int id){
    node2 *cur=&root;
    for(auto i:s){
        int c=cha(i);
        if(!cur->child[c]) cur->child[c]=new node2();
        cur=cur->child[c];
        cur->pos.push_back(id);
    }
}   
pair <int, int > find1(string &s, node1 &root){
    node1 *cur=&root;
    for(auto i:s){
        int c=cha(i);
        if(!cur->child[c]) return {-1,-1};
        cur=cur->child[c];
    }
    return {cur->l,cur->r};
}
vector <int>  find2(string &s, node2 &root){
    node2 *cur=&root;
    for(auto i:s){
        int c=cha(i);
        if(!cur->child[c]) return {};
        cur=cur->child[c];
    }
    return cur->pos;
}
string a[200005];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;cin>> n >> m;
    for(int i=1;i<=n;i++) cin >> a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++) update1(a[i],trie1,i);
    for(int i=1;i<=n;i++){
        string x=a[i];
        reverse(x.begin(),x.end());
        update2(x,trie2,i);
    }
    while(m--){
        string p,q; cin >> p >> q;
        auto x=find1(p,trie1);
        if(x.first==-1){
            cout << "0\n";
            continue;
        }
        reverse (q.begin(),q.end());
        vector <int> v=find2(q,trie2);
        if(v.empty()) {
            cout << "0\n";
            continue;
        }
        cout << upper_bound(v.begin(),v.end(),x.second)-lower_bound(v.begin(),v.end(),x.first) << "\n";
    }
    return 0;
}