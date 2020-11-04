#include <bits/stdc++.h>
using namespace std;

struct DSU{
    struct dsu_save{
        int x,y,sizx,sizy;

        dsu_save(int _x, int _y, int _sizx, int _sizy) :
            x(_x), y(_y), sizx(_sizx), sizy(_sizy) {}
    };
    vector<int> par,siz;
    stack<dsu_save> operations;
    stack<int> saves;
    int cnt;

    void init(int n){
        par.assign(n+1,0);
        iota(par.begin(),par.end(),0);
        siz.assign(n+1,1);
        while(!operations.empty())operations.pop();
        while(!saves.empty());
        cnt = n;
    }

    int find(int x){
        return (par[x] == x) ? x : find(par[x]);
    }

    bool join(int x, int y){
        x = find(x);
        y = find(y);
        if(x==y)
            return false;
        if(siz[x] < siz[y])
            swap(x,y);
        operations.push(dsu_save(x,y,siz[x],siz[y]));
        cnt--;

        par[y] = x;
        siz[x] += siz[y];
        return true;
    }

    void rollback_util(){
        dsu_save temp = operations.top();
        operations.pop();

        cnt++;
        int x = temp.x;
        int y = temp.y;
        par[x] = x;
        par[y] = y;
        siz[x] = temp.sizx;
        siz[y] = temp.sizy;
    }

    // returns <bool> depending on if the rollback was successful
    bool rollback(){
        if(saves.empty())
            return false;
        int temp = saves.top();
        saves.pop();
        
        while(operations.size() > temp){
            rollback_util();
        }
        return true;
    }

    void save(){
        saves.push(operations.size());
    }

};


int main (){
    int n,q;
    cin>>n>>q;

    DSU dsu;
    dsu.init(n);

    while(q--){
        string s;
        cin>>s;
        if(s == "union"){
            int x,y;
            cin>>x>>y;
            dsu.join(x,y);
            cout<<dsu.cnt<<endl;
        }
        else if(s == "persist"){
            dsu.save();
        }
        else if(s == "rollback"){
            dsu.rollback();
            cout<<dsu.cnt<<endl;
        }
    }

}