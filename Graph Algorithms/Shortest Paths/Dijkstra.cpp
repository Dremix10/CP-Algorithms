#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+1;
const int INF = 1e9;

vector<vector<pair<int,int> > > adj(N);

vector<int> dijkstra(int n, int s){
    vector<int> dist(n+1,INF);
    dist[s] = 0;

    priority_queue<pair<int,int> > q;
    q.push(make_pair(0,s));

    while(!q.empty()){
        int curr = q.top().second;
        int w = -q.top().first;
        q.pop();
        if(dist[curr] < w)continue;

        for(auto nxt : adj[curr])
        if(dist[nxt.first] > dist[curr] + nxt.second){
            dist[nxt.first] = dist[curr] + nxt.second;
            q.push(make_pair(-dist[nxt.first],nxt.first));
        }
    }
    return dist;
}

int main (){
    int n,m;
    cin>>n>>m;

    int i;
    for(i=0;i<m;i++){
        int x,y,w;
        cin>>x>>y>>w;
        adj[x].push_back(make_pair(y,w));
        adj[y].push_back(make_pair(x,w));
    }
    vector<int> dist = dijkstra(n,0);
    for(i=1;i<n;i++)
        cout<<dist[i]<<" ";
    cout<<endl;
    
}