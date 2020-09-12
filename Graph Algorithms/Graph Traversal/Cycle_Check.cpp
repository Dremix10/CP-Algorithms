#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+1;

vector<vector<int> > adj(N);
int v[N], par[N];
int cycStart = -1, cycEnd = -1;

void dfs(int curr, int prev){
    v[curr] = 1;
    par[curr] = prev;
    for(auto nxt : adj[curr])
        if(nxt!=prev){
            if(!v[nxt]){
                dfs(nxt,curr);
                if(cycStart!=-1)return;
            }
            else if(v[nxt]==1){
                cycStart = nxt;
                cycEnd = curr;
                return;
            }
        }
}

int main (){
    int n,m;
    cin>>n>>m;

    int i;
    // cycle check for directed and undirected graph, finds cycles with 3 or more nodes
    for(i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1,1);

    if(cycStart==-1){
        cout<<"Graph has no cycles"<<endl;
        return 0;
    }

    vector<int> cycle;
    int curr = cycEnd;

    while(curr!=cycStart){
        cycle.push_back(curr);
        curr = par[curr];
    }
    cycle.push_back(curr);
    
    cout<<"There is a cycle of "<<cycle.size()<<" nodes:"<<endl;
    for(auto x : cycle)
        cout<<x<<" ";
    cout<<endl;

}