#include <bits/stdc++.h>
#define N (int)(2e5+1)
using namespace std;

vector<vector<int> > adj(N,vector<int>());  
int depth[N];

void dfs(int curr, int prev){

    for(auto nxt : adj[curr])
        if(nxt!=prev){
            depth[nxt] = depth[curr] + 1;
            dfs(nxt,curr);
        }
}

int get_diameter(int root, int n){
    dfs(root,root);

    int furthest = root,dist = 0,i;

    for(i=1;i<=n;i++)
        if(depth[i]>dist){
            dist = depth[i];
            furthest = i;
        }

    depth[furthest] = 0;
    dfs(furthest,furthest);

    int diameter = 0;
    for(i=1;i<=n;i++)
        diameter = max(diameter,depth[i]);

    return diameter;
}


int main (){
    int n;
    cin>>n;

    int i;
    int root = 1;
    
    for(i=0;i<n-1;i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    cout<<get_diameter(root,n)<<endl;
    
}