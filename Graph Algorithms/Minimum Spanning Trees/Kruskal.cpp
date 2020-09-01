#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+1;

struct DSU{
    vector<int> par,siz;
    int cnt;
    
    void init(int n){
        cnt = n;
        par.assign(n+1,0);
        siz.assign(n+1,1);
        iota(par.begin(),par.end(),0);
    }

    int find(int x){
        return (par[x]==x) ? x : par[x] = find(par[x]);
    }

    bool merge(int x, int y){
        x = find(x);
        y = find(y);
        if(x==y)return false;
        if(siz[x]<siz[y])
            swap(x,y);
        
        siz[x] += siz[y];
        par[y] = x;
        cnt--;
        return true;
    }

};

struct edge{
    int x,y,w;
    bool operator<(const edge &a)const{
        return w<a.w;
    }
};

int main (){
    int n,m;
    cin>>n>>m;

    int i;
    edge edges[m];
    for(i=0;i<m;i++)
        cin>>edges[i].x>>edges[i].y>>edges[i].w;
    
    sort(edges,edges+m);
    DSU dsu;
    dsu.init(n);

    int mst = 0;
    cout<<"Edges of MST are:"<<endl;
    for(i=0;i<m;i++){
        if(dsu.merge(edges[i].x,edges[i].y)){
            cout<<edges[i].x<<"-"<<edges[i].y<<endl;
            mst += edges[i].w;
        }
    }
    cout<<"With total cost:";
    cout<<mst;
    
}