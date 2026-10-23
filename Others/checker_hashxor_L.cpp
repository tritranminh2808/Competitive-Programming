#include <bits/stdc++.h>
#include <fstream>

using namespace std;
fstream f;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    f.open("output.out",ios::in);
    vector <bool> ans,code;
    string s;
    //bool ch=0;
    while(f>>s){
        if(s=="YES") ans.push_back(1);
        else ans.push_back(0);
    }
    f.close();
    f.open("output.ans",ios::in);
     while(f>>s){
        if(s=="YES") code.push_back(1);
        else code.push_back(0);
    }
    f.close();
    for(int i=0;i<ans.size();i++){
        cout << "test" << i+1 << "::\n";
        if(ans[i]==code[i]) cout << "accepted\n";
        else {
            cout << "wrong answer\n";
            break;
        }
        cout << "--------------------------------------------------------------------------------------------------------\n";
    }
}
