#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+1;

int main (){
    int n,m;
    cin>>n>>m;

    vector<vector<int> > adj(n+1);
    int i,cnt[n+1]; // cnt in_degree of node
    memset(cnt,0,sizeof cnt);

    for(i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        cnt[y]++;
    }

    queue<int> q;
    for(i=1;i<=n;i++)
        if(!cnt[i])q.push(i);

    vector<int> topo;
    while(!q.empty()){
        int curr = q.front();
        q.pop();

        topo.push_back(curr);
        for(auto nxt : adj[curr]){
            cnt[nxt]--;
            if(!cnt[nxt])q.push(nxt);
        }
    }
    
    if(topo.size()!=n)
        cout<<"There exists a cycle in the graph"<<endl;
    else{
        cout<<"Topological sorting is:"<<endl;
        for(auto x : topo)
            cout<<x<<" ";
        cout<<endl;
    }

}