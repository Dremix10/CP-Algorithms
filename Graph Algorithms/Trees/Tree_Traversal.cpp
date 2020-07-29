#include <bits/stdc++.h>
#define N (int)(2e5+1)
using namespace std;

vector<vector<int> > adj(N,vector<int>());

void dfs(int curr, int prev){
    cout<<curr<<" ";
    
    for(auto nxt : adj[curr])
        if(nxt!=prev)
        dfs(nxt,curr);
}

int main (){
    int n;
    cin>>n;

    int i;
    int root=1;
    
    for(i=0;i<n-1;i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    cout<<"Nodes in DFS order are:"<<endl;
    dfs(root,root);
    
}