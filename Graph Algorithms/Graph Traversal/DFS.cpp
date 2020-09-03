#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+1;

vector<vector<int> > adj(N);
bool v[N];

void dfs(int curr){
    cout<<curr<<" ";
    v[curr] = true;
    for(auto nxt : adj[curr])
        if(!v[nxt])
        dfs(nxt);
}

int main (){
    int n,m;
    cin>>n>>m;

    int i;
    for(i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    int root = 1;
    cout<<"Nodes in DFS order are:"<<endl;
    dfs(root);

}