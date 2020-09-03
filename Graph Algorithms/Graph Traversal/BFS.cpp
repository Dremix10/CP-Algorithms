#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+1;

vector<vector<int> > adj(N);

void bfs(int start){
    bool v[N];
    v[start] = true;

    queue<int> q;
    q.push(start);

    while(!q.empty()){
        int curr = q.front();
        q.pop();
        cout<<curr<<" ";

        for(auto nxt : adj[curr])
            if(!v[nxt]){
                v[nxt] = true;
                q.push(nxt);
            }
    }
}

int main (){
    int n,m;
    cin>>n>>m;

    int i;
    for(i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    int root = 1;
    cout<<"Nodes in BFS order are:"<<endl;
    bfs(root);

}