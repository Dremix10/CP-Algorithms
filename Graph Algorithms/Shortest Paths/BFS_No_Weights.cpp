#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+1;

vector<int> bfs_dist(vector<vector<int> > &adj, int start, int n){
    vector<int> dist(n+1);
    dist[start] = 0;

    bool v[n+1] = {};
    queue<int> q;
    q.push(start);
    v[start] = true;

    while(!q.empty()){
        int curr = q.front();
        q.pop();
        
        cout<<curr<<" "<<dist[curr]<<endl;
        for(auto nxt : adj[curr]){
            if(!v[nxt]){
                v[nxt] = true;
                dist[nxt] = dist[curr] + 1;
                q.push(nxt);
            }
        }
    }
    return dist;
}

int main (){
    int n,m;
    cin>>n>>m;

    int i;
    vector<vector<int> > adj(n+1);
    for(i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<int> dist = bfs_dist(adj,1,n);

    for(i=1;i<=n;i++)
        cout<<dist[i]<<" ";
    cout<<endl;

}