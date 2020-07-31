#include <bits/stdc++.h>
#define N (int)(2e5+1)
#define maxPow (int)(22)
using namespace std;

vector<vector<int> > adj(N,vector<int>());
int binLift[N][maxPow];

void dfs(int curr, int prev){
    binLift[curr][0] = prev;
    
    for(int i=1;i<maxPow;i++)
        binLift[curr][i] = binLift[binLift[curr][i-1]][i-1];

    for(auto nxt : adj[curr])
        if(nxt!=prev)
            dfs(nxt,curr);
        
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

    // process kth ancestor queries
    while(q--){
        int node,k;
        cin>>node>>k;
        int kth = kth_ancestor(node,k);
        if(kth==0)
            kth--;
        cout<<kth<<endl;
    }


}