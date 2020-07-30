#include <bits/stdc++.h>
#define N (int)(2e5+1)
using namespace std;

vector<vector<int> > adj(N,vector<int>());
int toLeaf[N],maxDistThrough[N];

void dfs(int curr, int prev){
    priority_queue <int> furthestLeaves;

    for(auto nxt : adj[curr])
        if(nxt!=prev){
            dfs(nxt,curr);
            toLeaf[curr] = max(toLeaf[curr],toLeaf[nxt]);
            furthestLeaves.push(toLeaf[nxt]);
        }
    int get = 2;
    while(!furthestLeaves.empty() && get--){
        maxDistThrough[curr] += furthestLeaves.top();
        furthestLeaves.pop();
    }

    toLeaf[curr]++;
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

    int diameter = 0;
    for(i=1;i<=n;i++)
        diameter = max(diameter,maxDistThrough[i]);

    cout<<diameter<<endl;
    
}