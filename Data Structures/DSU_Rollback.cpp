#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
#define F first
#define S second

struct dsu_save{
    int x,y,sizx,sizy;

    dsu_save(int _x, int _y, int _sizx, int _sizy)
        : x(_x), y(_y), sizx(_sizx), sizy(_sizy) {}
};

struct DSU{
    vector<int> par,siz;
    stack<dsu_save> memo;
    int cnt;

    void init(int n){
        par.assign(n+1,0);
        siz.assign(n+1,1);
        while(!memo.empty())memo.pop();

        iota(par.begin(),par.end(),0);
        cnt = n;
    }

    int find(int x){
        return (par[x] == x) ? x : find(par[x]);
    }

    bool join(int x, int y){
        x = find(x);
        y = find(y);
        if(x==y)return false;
        if(siz[x]<siz[y])swap(x,y);

        memo.push(dsu_save(x,y,siz[x],siz[y]));
        par[y] = x;
        siz[x] += siz[y];
        cnt--;
        return true;
    }

    void rollback(){
        if(memo.empty())return;
        dsu_save temp = memo.top();
        memo.pop();

        cnt++;
        par[temp.x] = temp.x;
        par[temp.y] = temp.y;
        siz[temp.x] = temp.sizx;
        siz[temp.y] = temp.sizy;
    }

};

struct query{
    int x,y;
    bool joined;

    query(int _x, int _y) : x(_x), y(_y) {}
};

struct tree{
    vector<vector<query> > seg;
    DSU dsu;
    int N;

    void init(int n, int q){
        dsu.init(n);
        seg.assign(q*4+4,vector<query>());
        N = q;
    }

    void add_seg(int s, int e, int idx, int qs, int qe, query &q){
        if(qs<=s && e<=qe){
            seg[idx].push_back(q);
            return;
        }
        if(s>qe || e<qs)return;

        int mid = (s+e)/2;
        add_seg(s,mid,idx*2,qs,qe,q);
        add_seg(mid+1,e,idx*2+1,qs,qe,q);
    }

    void add_seg(int l, int r, query q){
        add_seg(1,N,1,l,r,q);
    }

    void dfs(int s, int e, int idx, vector<int> &ans){
        for(auto &q : seg[idx]){
            q.joined = dsu.join(q.x,q.y);
        }

        if(s==e){
            ans[s] = dsu.cnt;
        }
        else{
            int mid = (s+e)/2;
            dfs(s,mid,idx*2,ans);
            dfs(mid+1,e,idx*2+1,ans);
        }

        for(auto q : seg[idx]){
            if(q.joined)dsu.rollback();
        }
    }

    vector<int> solve(){
        if(N==0)return {};
        vector<int> ans(N+1);
        dfs(1,N,1,ans);
        return ans;
    }

};

int main (){
    int n,q;
    cin>>n>>q;

    int i;

    vector<int> ans;

    // each edge is alive for some segments of time - added as queries
    tree fatality;
    fatality.init(n,q);

    map<pi,int> alive;

    // queries -> + add edge (x,y) , - remove edge (x,y), ? output components
    for(i=1;i<=q;i++){
        char op;
        cin>>op;
        if(op=='+'){
            int x,y;
            cin>>x>>y;
            if(x>y)swap(x,y);

            alive[{x,y}] = i;
        }
        else if(op=='-'){
            int x,y;
            cin>>x>>y;
            if(x>y)swap(x,y);

            fatality.add_seg(alive[{x,y}],i-1,query(x,y));
            alive[{x,y}] = 0;
        }
        else{
            ans.push_back(i);
        }
    }

    for(auto x : alive){
        if(!x.S)continue;
        fatality.add_seg(x.S,q,query(x.F.F,x.F.S));
    }

    vector<int> solved = fatality.solve();

    for(auto x : ans){
        cout<<solved[x]<<endl;
    }

}
