#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma,sse2")
using namespace std;
vector <int> chiacan[101][605];

void build(int n) {
    for (int i = 0; i < n; i++) {
    	int x; cin >> x;
        int nhom=i/600;
        chiacan[x][nhom].push_back(i);
    }
}

void update_chay(int l, int r, int x, int y) {
	int nhom=l/600;
	vector <int> c1=chiacan[x][nhom];
	chiacan[x][nhom].clear();
    for(auto i : c1){
   		if(i>=l&&i<=r) chiacan[y][nhom].push_back(i);
   		else chiacan[x][nhom].push_back(i);
	}
}
int res[200005];
void query(int l, int r, int x, int y) {
    if (l/600==r/600) {
    	 update_chay(l, r, x, y);
    	 return;
	}
    int n1=l/600,n2=r/600;
    vector <int> c1=chiacan[x][n1],c2=chiacan[x][n2];
    chiacan[x][n1].clear();
    chiacan[x][n2].clear();
   	for(auto i : c1){
   		if(i>=l&&i<=r) chiacan[y][n1].push_back(i);
   		else chiacan[x][n1].push_back(i);
	}
	for(auto i : c2){
   		if(i<=r&&i>=l) chiacan[y][n2].push_back(i);
   		else chiacan[x][n2].push_back(i);
	}
    for(int i=l/600+1;i<r/600;i++){
    	if(chiacan[x][i].size()>chiacan[y][i].size()) swap(chiacan[x][i],chiacan[y][i]);
        for(auto& z:chiacan[x][i]) chiacan[y][i].push_back(z);
        chiacan[x][i].clear();
	}
	
}
bool cmp(pair<int, int > a, pair <int, int > b){
	return a.first<b.first;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n;
    build(n);
    cin >> q;
    while (q--) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        if (x != y) query(l-1, r-1, x, y);
    }
    vector < pair <int, int > > v;
    for(int i=1;i<=100;i++){
    	for(int j=0;j<=600;j++) {
    		for(auto k:chiacan[i][j]) res[k]=i;
		}
	}
	for(int i=0;i<n;i++) cout << res[i] << " ";
    return 0;
}

