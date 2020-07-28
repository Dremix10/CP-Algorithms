#include <bits/stdc++.h>
#define N (int)(2e5+1)
using namespace std;

vector<vector<int> > adj(N,vector<int>());  
int depth[N];

void dfs(int cur, int par){

    for(auto to : adj[cur])
        if(to!=par){
            depth[to] = depth[cur] + 1;
            dfs(to,cur);
        }

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

    dfs(root,root);

    int furthest=root,dist=0;

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

    cout<<diameter<<endl;
}