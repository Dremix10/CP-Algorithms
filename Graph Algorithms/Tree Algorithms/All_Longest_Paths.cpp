#include <bits/stdc++.h>
#define N (int)(2e5+1)
using namespace std;

vector<vector<int> > adj(N,vector<int>());
pair<int,int> bestLeaves[N];
int toLeaf[N], toParent[N];

void get_height(int curr, int prev){
    priority_queue < pair<int,int> > furthestLeaves;
    toLeaf[curr] = 0;

    for(auto nxt : adj[curr])
        if(nxt!=prev){
            get_height(nxt,curr);
            toLeaf[curr] = max(toLeaf[curr],toLeaf[nxt]+1);
            furthestLeaves.push(make_pair(toLeaf[nxt],nxt));
        }
    
    if(furthestLeaves.empty())
        bestLeaves[curr] = make_pair(-1,-1);

    else if(furthestLeaves.size()==1)
        bestLeaves[curr] = make_pair(furthestLeaves.top().second,-1);
    
    else{
        bestLeaves[curr].first = furthestLeaves.top().second;
        furthestLeaves.pop();
        bestLeaves[curr].second = furthestLeaves.top().second;
    }
}

void get_parent(int curr, int prev){
    toParent[curr] = 0;
    if(curr!=prev){
        toParent[curr] = toParent[prev] + 1;

        if(bestLeaves[prev].first!=curr && bestLeaves[prev].first!=-1)
            toParent[curr] = max(toParent[curr],toLeaf[bestLeaves[prev].first] + 2);
        
        else if(bestLeaves[prev].second !=-1)
            toParent[curr] = max(toParent[curr],toLeaf[bestLeaves[prev].second] + 2);
    }
    for(auto nxt : adj[curr])
        if(nxt!=prev)
            get_parent(nxt,curr);
}

vector<int> all_longest(int root, int n){
    get_height(root,root);
    get_parent(root,root);

    vector<int> longestPath(n+1);
    for(int i=1;i<=n;i++)
        longestPath[i] = max(toLeaf[i],toParent[i]);

    return longestPath;
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
    vector<int> longestPaths = all_longest(root,n);
    for(i=1;i<=n;i++)
        cout<<longestPaths[i]<<" ";

}