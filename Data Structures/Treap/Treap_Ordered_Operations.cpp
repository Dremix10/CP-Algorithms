#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define pi pair<int,int>
typedef long long ll;
const int N = 2e5+1;
const ll INF = 1e18;

// randomization setup
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distribution;
ll rnd(ll l, ll r){return distribution(rng)%(r-l+1)+l;}

template<typename T>
struct TREAP{
    struct node{
        T key,sum;
        int l,r,cnt; // cnt = nodes in current subtree
        bool rev;
        ll y;

        node() : key(0), y(0), l(0), r(0), cnt(0), sum(0), rev(false) {}
        node(T _key) : key(_key), y(rnd(1,INF)), l(0), r(0), cnt(1), sum(_key), rev(false) {}
    };
    vector<node> treap;
    int mainRoot;

    TREAP() : mainRoot(0){
        treap.push_back(node());
    }
    
    // updates node data after changes
    void upd(int x){
        treap[x].cnt = treap[treap[x].l].cnt + treap[treap[x].r].cnt + 1;
        treap[x].sum = treap[treap[x].l].sum + treap[treap[x].r].sum + treap[x].key;
    }

    // push lazy propagation to children
    void push(int x){
        if(treap[x].rev){
            swap(treap[x].l,treap[x].r);
            treap[treap[x].l].rev ^= 1;
            treap[treap[x].r].rev ^= 1;
            treap[x].rev = false;
        }
    }
    
    // debugging tools
    void look_tree(int root){
        if(root == 0)
            return;
        push(root);
        look_tree(treap[root].l);
        cerr<<treap[root].key<<" ";
        look_tree(treap[root].r);
    }

    // debugging tools
    void debug_tree(int root){
        cerr<<"root of tree: "<<treap[root].key<<endl;
        look_tree(root);
        cerr<<endl;
    }

    // split subtree of root with first (cnt) elements to the left subtree and rest to the right 
    pi split_by_cnt(int root, int cnt){
        if(root == 0)
            return make_pair(0,0);
        
        push(root);
        if(treap[treap[root].l].cnt + 1 <= cnt){
            pi temp = split_by_cnt(treap[root].r,cnt - treap[treap[root].l].cnt - 1);
            treap[root].r = temp.F;
            upd(root);
            return make_pair(root,temp.S);
        }
        else{
            pi temp = split_by_cnt(treap[root].l,cnt);
            treap[root].l = temp.S;
            upd(root);
            return make_pair(temp.F,root);
        }
    }

    // merge 2 subtrees L and R according to y-coordinates
    int merge(int rootL, int rootR){
        if(rootL == 0)
            return rootR;
        if(rootR == 0)
            return rootL;

        push(rootL);
        push(rootR);
        if(treap[rootL].y >= treap[rootR].y){ // left root higher than right root
            treap[rootL].r = merge(treap[rootL].r,rootR);
            upd(rootL);
            return rootL;
        }
        else{ // right root higher than left root
            treap[rootR].l = merge(rootL,treap[rootR].l);
            upd(rootR);
            return rootR;
        }
    }

    // creates new node and returns index of it
    int new_node(T key){
        treap.push_back(node(key));
        return treap.size()-1;
    }

    // inserts new element at index (pos) with all elements at >=pos shifting to the right
    // pos is bounded to max(pos,1) and min(pos,treap_size)
    void insert(int pos, T key){
        pi temp = split_by_cnt(mainRoot,pos-1);
        temp.F = merge(temp.F,new_node(key));
        mainRoot = merge(temp.F,temp.S);        
    }

    // removes element at (pos) if it exists
    // pos is bounded to max(pos,1)
    void erase(int pos){
        pi temp = split_by_cnt(mainRoot,pos-1);
        temp.S = split_by_cnt(temp.S,1).S;
        mainRoot = merge(temp.F,temp.S);
    }

    // returns kth element if it exists otherwise boolean will be false (1-indexed)
    pair<T,bool> kth_element(int k){ // *! can be modified to return index of node for more data !*
        int curr = mainRoot;
        while(curr){
            if(treap[treap[curr].l].cnt + 1 == k)
                return make_pair(treap[curr].key,true);
            if(treap[treap[curr].l].cnt >= k)
                curr = treap[curr].l;
            else{
                k -= treap[treap[curr].l].cnt + 1;
                curr = treap[curr].r;
            }
        }
        return make_pair(0,false);
    }

    // reverse segment with indexes [l,r]
    void reverse(int l, int r){
        pi temp = split_by_cnt(mainRoot,l-1);
        int left = temp.F;
        
        temp = split_by_cnt(temp.S,r-l+1);
        treap[temp.F].rev ^= 1;

        int right = merge(temp.F,temp.S);
        mainRoot = merge(left,right);
    }

    // clears treap and re-initializes
    void clear(){
        treap.clear();
        treap.push_back(node());
        mainRoot = 0;
    }

    // initialization with array - sorting doesn't matter (ordered treap)
    void init_array(int n, T arr[]){
        for(int i = 0;i < n;i ++)
            mainRoot = merge(mainRoot,new_node(arr[i]));
    }

    // initialization with vector - sorting doesn't matter (ordered treap)
    void init_vector(int n, vector<T> &arr){
        for(auto key : arr)
            mainRoot = merge(mainRoot,new_node(key));
    }

};


int main (){
    int q;
    cin>>q;

    TREAP<int> treap;

    while(q--){
        string type;
        cin>>type;
        if(type == "insert"){
            int pos,x;
            cin>>pos>>x;
            treap.insert(pos,x);
        }
        else if(type == "erase"){
            int pos;
            cin>>pos;
            treap.erase(pos);
        }
        else if(type == "kth"){
            int k;
            cin>>k;
            pi temp = treap.kth_element(k);
            if(temp.S == false)cout<<"none"<<endl;
            else cout<<temp.F<<endl;
        }
        else if(type == "reverse"){
            int x,y;
            cin>>x>>y;
            treap.reverse(x,y);
        }
        treap.look_tree(treap.mainRoot);
    }

}