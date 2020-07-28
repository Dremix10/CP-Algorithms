#include<bits/stdc++.h>
#define N (int)(1e5+1)
using namespace std;

vector<vector<int> > adj(N,vector<int>());

void dfs(int cur, int par){
    cout<<cur<<" ";
    for(auto to : adj[cur])
        if(to!=par)
        dfs(to,cur);
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