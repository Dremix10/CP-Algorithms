#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+1;
const long long INF = 1e18;

vector<vector<pair<int,int> > > adj(N);
vector<int> topo;
bool v[N];

void dfs(int curr){
    v[curr] = true;
    for(auto nxt : adj[curr])
        if(!v[nxt.first])
            dfs(nxt.first);
    topo.push_back(curr);
}

int main (){
    int n,m;
    cin>>n>>m;

    // !* current implementation works for acyclic graphs - scc algorithm can be added to support cyclic graphs too *!
    int i;
    for(i=0;i<m;i++){
        int x,y,w;
        cin>>x>>y>>w;
        adj[x].push_back(make_pair(y,w));
    }

    // add fake node to calculate longest path of whole graph
    for(i=1;i<=n;i++)
        adj[0].push_back(make_pair(i,0));

    for(i=1;i<=n;i++){
        if(v[i])continue;
        dfs(i);
    }
    topo.push_back(0);
    reverse(topo.begin(),topo.end());
    
    long long longest[n+1];
    for(i=1;i<=n;i++)
        longest[i] = -INF;
    longest[0] = 0;
    
    for(auto curr : topo){
        for(auto nxt : adj[curr]){
            longest[nxt.first] = max(longest[nxt.first],longest[curr]+nxt.second);
        }
    }
    long long ans = -INF;
    for(i=1;i<=n;i++)
        ans = max(ans,longest[i]);

    cout<<"Longest path in graph costs: "<<ans<<endl;

}