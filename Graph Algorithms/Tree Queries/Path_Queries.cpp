#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+1;

vector<vector<int> > adj(N);
int subtree[N],mapper[N],order = 1,val[N];
ll path[N];

void dfs(int curr, int prev){
    // dfs ordering
    mapper[curr] = order++;
    
    path[curr] = path[prev] + val[curr];
    subtree[curr] = 1;
    for(auto nxt : adj[curr])
        if(nxt!=prev){
            dfs(nxt,curr);
            subtree[curr] += subtree[nxt];
        }
}

template<typename T>
struct SEGTREE{
    struct node{
        T val; // for adding more stuff
        T lazy; 

        node() : val(0), lazy(0) {}
        node(T _val) : val(_val), lazy(0) {}
    };
    vector<node> seg;
    int N;

    void init(int n){
        N = n;
        seg.assign(4*n,node());
    }

    node merge(node x, node y){
        node res;
        res.val = x.val + y.val;
        return res;
    }

    void push(node &par, node &x, node &y, int r1, int r2){
        x.val += par.lazy * r1;
        x.lazy += par.lazy;
        y.val += par.lazy * r2;
        y.lazy += par.lazy;
        par.lazy = 0;
    }

    void build(int s, int e, int idx, T arr[]){
        if(s == e){
            seg[idx] = node(arr[s]);
            return;
        }
        int mid = (s+e)/2;
        build(s,mid,idx*2,arr);
        build(mid+1,e,idx*2+1,arr);
        seg[idx] = merge(seg[idx*2],seg[idx*2+1]);
    }

    // supports 1-indexing
    void build(T arr[]){
        build(1,N,1,arr);
    }

    void update(int s, int e, int idx, int qs, int qe, T val){
        if(qs<=s && e<=qe){
            seg[idx].val += val * (e-s+1);
            seg[idx].lazy += val;
            return;            
        }
        if(s>qe || e<qs)
            return;
        int mid = (s+e)/2;
        push(seg[idx],seg[idx*2],seg[idx*2+1],mid-s+1,e-mid);
        update(s,mid,idx*2,qs,qe,val);
        update(mid+1,e,idx*2+1,qs,qe,val);
        seg[idx] = merge(seg[idx*2],seg[idx*2+1]);
    }

    // add to all i (l<=i && i<=r) += val
    void update(int l, int r, T val){
        update(1,N,1,l,r,val);
    }

    node query(int s, int e, int idx, int qs, int qe){
        if(qs<=s && e<=qe)
            return seg[idx];
        if(s>qe || e<qs)
            return node();
        int mid = (s+e)/2;
        push(seg[idx],seg[idx*2],seg[idx*2+1],mid-s+1,e-mid);
        return merge(query(s,mid,idx*2,qs,qe),query(mid+1,e,idx*2+1,qs,qe));
    }

    T query(int l, int r){
        return query(1,N,1,l,r).val;
    }

};

int main (){
    int n,q;
    cin>>n>>q;

    int i;
    for(i=1;i<=n;i++)
        cin>>val[i];

    for(i=0;i<n-1;i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    int root = 1;
    path[root] = 0;
    dfs(root,root);

    ll arr[N];
    for(i=1;i<=n;i++)
        arr[mapper[i]] = path[i];

    SEGTREE<ll> seg;
    seg.init(n);
    seg.build(arr);

    while(q--){
        int type;
        cin>>type;
        if(type==1){
            int k,x;
            cin>>k>>x;
            int diff = x - val[k];
            val[k] = x;
            seg.update(mapper[k],mapper[k]+subtree[k]-1,diff);
        }
        else{
            int k;
            cin>>k;
            cout<<seg.query(mapper[k],mapper[k])<<endl;
        }
    }

}