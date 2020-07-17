#include<bits/stdc++.h>
#define N (int)(1e5+1)
using namespace std;

vector<vector<int> > adj(N,vector<int>());

void dfs(int s, int p){
    cout<<s<<" ";
    for(auto x : adj[s])
        if(x!=p)
        dfs(x,s);
}

int main (){
    int n;
    cin>>n;

    int i;
    int root;
    cin>>root;
    
    for(i=0;i<n-1;i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    cout<<"Nodes in DFS order are:"<<endl;
    dfs(root,root);
    
}