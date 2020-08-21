#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+1;

vector<vector<int> > adj(N);
vector<int> topo;
bool v[N];

void dfs(int curr){
    v[curr] = true;
    for(auto nxt : adj[curr])
        if(!v[nxt])
            dfs(nxt);
    topo.push_back(curr);
}

int main (){
    int n,m;
    cin>>n>>m;

    int i;
    for(i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
    }

    for(i=1;i<=n;i++){
        if(v[i])continue;
        dfs(i);
    }
    reverse(topo.begin(),topo.end());

    for(auto x : topo)
        cout<<x<<" ";
    cout<<endl;

}