#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+1;

vector<vector<pair<int,int> > > adj(N);

struct edge{
    int x,y,w;
    bool operator<(const edge &a)const{
        return w>a.w;
    }
};

int MST(int start){
    bool v[N] = {};
    v[start] = true;

    priority_queue<edge> q;
    for(auto nxt : adj[start])
        q.push({start,nxt.first,nxt.second});

    int mst = 0;
    while(!q.empty()){
        int cost = q.top().w;
        int prev = q.top().x;
        int curr = q.top().y;
        q.pop();
        if(v[curr])continue;
        v[curr] = true;

        mst += cost;
        cout<<prev<<" "<<curr<<endl;

        for(auto nxt : adj[curr])
            q.push({curr,nxt.first,nxt.second});
    }
    return mst;
}

int main (){
    int n,m;
    cin>>n>>m;

    int i;
    int start = 1;
    for(i=0;i<m;i++){
        int x,y,w;
        cin>>x>>y>>w;
        adj[x].push_back(make_pair(y,w));
        adj[y].push_back(make_pair(x,w));
    }
    cout<<"Edges of MST are:"<<endl;
    int mst = MST(start);
    cout<<"With total cost: ";
    cout<<mst<<endl;

}