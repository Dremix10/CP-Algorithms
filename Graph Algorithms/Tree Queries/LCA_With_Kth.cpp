#include <bits/stdc++.h>
#define N (int)(2e5+1)
#define maxPow (int)(22)
using namespace std;

vector<vector<int> > adj(N,vector<int>());
int binLift[N][maxPow];
int depth[N];

void dfs(int curr, int prev){
    binLift[curr][0] = prev;

    for(int i=1;i<maxPow;i++)
        binLift[curr][i] = binLift[binLift[curr][i-1]][i-1];

    for(auto nxt : adj[curr])
        if(nxt!=prev){
            depth[nxt] = depth[curr] + 1;
            dfs(nxt,curr); 
        }
}

int kth_ancestor(int curr, int k){
    int currPow = 0;

    while(k>0){
        if(k&1)
            curr = binLift[curr][currPow];
        currPow++;
        k>>=1;
    }
    return curr;    
}

int lca(int x, int y){
    if(depth[x]>depth[y])
        swap(x,y);
    
    y = kth_ancestor(y,depth[y]-depth[x]);
    if(x==y)return x;

    for(int i=maxPow-1;i>=0;i--){
        if(binLift[x][i]==binLift[y][i])continue;
        x = binLift[x][i];
        y = binLift[y][i];
    }
    return binLift[x][0];
}

int main (){
    int n,q;
    cin>>n>>q;

    int i;
    int root = 1;
    
    for(i=2;i<=n;i++){
        int x;
        cin>>x;
        adj[x].push_back(i);
        adj[i].push_back(x);
    }
    dfs(root,0);

    // process lca queries
    while(q--){
        int x,y;
        cin>>x>>y;
        cout<<lca(x,y)<<endl;
    }

}
