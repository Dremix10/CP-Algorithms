#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

    SEGTREE<ll> seg;
    seg.init(n);

    ll arr[n+1];
    for(int i = 1;i <= n;i ++)
        cin>>arr[i];
    
    seg.build(arr);

    while(q--){
        string type;
        cin>>type;
        if(type == "ADD"){
            int l,r;
            ll x;
            cin>>l>>r>>x;
            seg.update(l,r,x);
        }
        else if(type == "SUM"){
            int l,r;
            cin>>l>>r;
            cout<<seg.query(l,r)<<endl;
        }
    }

}