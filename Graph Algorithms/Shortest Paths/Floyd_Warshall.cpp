#include <bits/stdc++.h>
using namespace std;
const int N = 101;
const int INF = 1e9;

void floyd(int dist[N][N], vector<vector<pair<int,int> > > &adj, int n){
    int i,j,k;
    for(i=1;i<=n;i++)
    for(j=1;j<=n;j++){
        dist[i][j] = INF;
        if(i==j)dist[i][j] = 0;
    }

    for(i=1;i<=n;i++)
        for(auto x : adj[i])
        dist[i][x.first] = x.second;
    
    for(k=1;k<=n;k++)
    for(i=1;i<=n;i++)
    for(j=1;j<=n;j++){
        dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
    }
}

int main (){
    int n,m;
    cin>>n>>m;

    int i;
    vector<vector<pair<int,int> > > adj(n+1);
    
    for(i=0;i<m;i++){
        int x,y,w;
        cin>>x>>y>>w;
        adj[x].push_back(make_pair(y,w));
        adj[y].push_back(make_pair(x,w));
    }
    int dist[N][N];
    floyd(dist,adj,n);
    
    int q;
    cin>>q;

    while(q--){
        int x,y;
        cin>>x>>y;
        cout<<"Dist between "<<x<<" and "<<y<<" is "<<dist[x][y]<<endl;
    }

}