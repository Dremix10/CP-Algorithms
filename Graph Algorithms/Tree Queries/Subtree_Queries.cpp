#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+1;

vector<vector<int> > adj(N);
int mapper[N],subtree[N],order = 1;

void dfs(int curr, int prev){
    // dfs order mapping
    mapper[curr] = order++;

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

        node() : val(0) {}
        node(T _val) : val(_val) {}
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

    void update(int s, int e, int idx, int k, T val){
        if(s==e && s==k){
            seg[idx].val = val;
            return;            
        }
        if(s>k || e<k)
            return;
        int mid = (s+e)/2;
        update(s,mid,idx*2,k,val);
        update(mid+1,e,idx*2+1,k,val);
        seg[idx] = merge(seg[idx*2],seg[idx*2+1]);
    }

    // arr[k] += val
    void update(int k, T val){
        update(1,N,1,k,val);
    }

    node query(int s, int e, int idx, int qs, int qe){
        if(qs<=s && e<=qe)
            return seg[idx];
        if(s>qe || e<qs)
            return node();
        int mid = (s+e)/2;
        return merge(query(s,mid,idx*2,qs,qe),query(mid+1,e,idx*2+1,qs,qe));
    }

    T query(int l, int r){
        return query(1,N,1,l,r).val;
    }

};

int main (){
    int n,q;
    cin>>n>>q;

    int arr[n+1];
    int i;
    // input node values
    for(i=1;i<=n;i++)
        cin>>arr[i];

    for(i=0;i<n-1;i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    int root = 1;
    dfs(root,root);

    // remapping values to match dfs order
    long long val[n+1];
    for(i=1;i<=n;i++)
        val[mapper[i]] = arr[i];

    SEGTREE<long long> seg;
    seg.init(n);
    seg.build(val);
    // answer subtree queries:
    // 1 x y -> change value of x to y
    // 2 x -> calculate sum of subtree of node x
    while(q--){
        int type;
        cin>>type;
        if(type==1){
            int x,y;
            cin>>x>>y;
            seg.update(mapper[x],y);
        }
        else{
            int x;
            cin>>x;
            cout<<seg.query(mapper[x],mapper[x]+subtree[x]-1)<<endl;
        }
    }

}