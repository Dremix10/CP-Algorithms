#include <bits/stdc++.h>
#define N (int)(2e5+1)
#define maxPow (int)(22)
using namespace std;

vector<vector<int> > adj(N,vector<int>());
int binLift[N][maxPow];
int timeIn[N],timeOut[N];
int TIME = 1;

void dfs(int curr, int prev){
    timeIn[curr] = TIME++;
    binLift[curr][0] = prev;
    
    for(int i=1;i<maxPow;i++)
        binLift[curr][i] = binLift[binLift[curr][i-1]][i-1];

    for(auto nxt : adj[curr])
        if(nxt!=prev)
            dfs(nxt,curr);

    timeOut[curr] = TIME;
}

bool isAncestor(int x, int y){ // is x ancestor of y
    return timeIn[x] <= timeIn[y] && timeIn[y] < timeOut[x];
}

int lca(int x, int y){
    if(isAncestor(x,y))return x;

    for(int i = maxPow - 1; i >= 0; i--)
        if(!isAncestor(binLift[x][i],y)){
            x = binLift[x][i];
        }
    return binLift[x][0];
}

int main (){
    int n,q;
    cin>>n>>q;

    int i;
    int root = 1;

    for(i=0;i<n-1;i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(root,0);

    // 0 as ancestor of all for generalisation
    timeIn[0] = 0;
    timeOut[0] = TIME;

    // process lca queries
    while(q--){
        int x,y;
        cin>>x>>y;
        int u = lca(x,y);
        cout<<u<<endl;
    }

}