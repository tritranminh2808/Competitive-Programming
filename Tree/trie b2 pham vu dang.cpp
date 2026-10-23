#include <bits/stdc++.h>
using namespace std;
struct node{
    node *child[26];
    int pos;
    vector <int> lit;
    node(){
        for(int i=0;i<26;i++) child[i]=NULL;
        pos=INT_MAX;
    }
};
node root;
void update(string &s, node &root, int vt){
    node *cur=&root;
    for(auto i:s){
        int c=i-'a';
        if(!cur->child[c]) cur->child[c]=new node();
        cur=cur->child[c];
        cur->lit.push_back(vt);
    }
    cur->pos=min(cur->pos,vt);
}
int posi=INT_MAX;
void find(string &s, node &root){
    node *cur=&root;
    for(auto i:s){
        int c=i-'a';
        if(!cur->child[c]){
            posi=INT_MAX;
            return;
        }
        cur=cur->child[c];
    }
    posi=cur->pos;
}
long long cnt=0;
void cok(string &s,node &root){
    node *cur=&root;
    for(auto i:s){
        int c=i-'a';
        if(!cur->child[c]) return;
        cur=cur->child[c];
        cnt+=upper_bound(cur->lit.begin(),cur->lit.end(),posi)-cur->lit.begin();
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    for(int i=1;i<=n;i++){
        string s; cin >> s;
        update(s,root,i);
    }
    int q; cin >> q;
    while(q--){
        string s; cin >> s;
        posi=INT_MAX;
        find(s,root);
        cnt=0;
        cok(s,root);
        if(posi==INT_MAX) posi=0;
        cout << cnt+posi << "\n";
        // cout << posi << "\n";
    }
    return 0;
}