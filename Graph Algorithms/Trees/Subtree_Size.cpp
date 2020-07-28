#include<bits/stdc++.h>
#define N (int)(1e5+1)
using namespace std;

vector<vector<int> > adj(N,vector<int>());
int subtree[N];

void dfs(int cur, int par){
    subtree[cur] = 1;

    for(auto to : adj[cur])
        if(to!=par){
            dfs(to,cur);
            subtree[cur] += subtree[to];
        }
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
    dfs(root,root);

    for(i=1;i<=n;i++)
        cout<<subtree[i]<<" ";
    
}