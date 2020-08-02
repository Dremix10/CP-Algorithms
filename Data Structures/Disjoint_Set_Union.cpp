#include <bits/stdc++.h>
#define N (int)(2e5+1)
using namespace std;

struct DSU{
    int par[N];
    int siz[N];
    
    void init(int n){
        for(int i=1;i<=n;i++){
            par[i] = i;
            siz[i] = 1;
        }
    }

    int find(int x){
        return (par[x]==x) ? x : par[x] = find(par[x]);
    }

    void merge(int x, int y){
        x = find(x);
        y = find(y);
        if(x==y)return;
        if(siz[x]<siz[y])
            swap(x,y);
        
        siz[x] += siz[y];
        par[y] = x;
    }

};


int main (){
    int n;
    cin>>n;

    DSU dsu;
    dsu.init(n);

    int q;
    cin>>q;

    while(q--){
        int type;
        // 0 for find set of x
        // 1 for merge set of x and y
        cin>>type;

        if(type==0){
            int x;
            cin>>x;
            cout<<"parent of set of "<<x<<": "<<dsu.find(x)<<endl;
        }
        else{
            int x,y;
            cin>>x>>y;
            dsu.merge(x,y);
        }
    }

}