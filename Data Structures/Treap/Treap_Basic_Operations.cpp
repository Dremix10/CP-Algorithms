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
        ll y;

        node() : key(0), y(0), l(0), r(0), cnt(0), sum(0) {}
        node(T _key) : key(_key), y(rnd(1,INF)), l(0), r(0), cnt(1), sum(_key) {}
    };
    vector<node> treap;
    int mainRoot;
    bool key_exists;

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
        // add stuff on need
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

    // split subtree of root with elements <= key to the left subtree and rest to the right
    pi split(int root, T key){
        if(root == 0)
            return make_pair(0,0);
        if(treap[root].key == key)
            key_exists = true;
        
        push(root);
        if(treap[root].key <= key){ // left subtree of root including root remain unchanged
            pi temp = split(treap[root].r,key);
            treap[root].r = temp.F;
            upd(root);
            return make_pair(root,temp.S);
        }
        else{ // right subtree of root including root remain unchanged
            pi temp = split(treap[root].l,key);
            treap[root].l = temp.S;
            upd(root);
            return make_pair(temp.F,root);
        }
    }

    // split subtree of root with first (cnt) elements to the left subtree and rest to the right 
    pi split_by_cnt(int root, int cnt){
        if(root == 0)
            return make_pair(0,0);
        
        push(rootL);
        push(rootR);
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

    // inserts new element according to key ordering if it doesn't exist already
    void insert(T key){
        key_exists = false; // variable will be true after split if key already exists in treap
        pi temp = split(mainRoot,key);
        if(!key_exists)
            temp.F = merge(temp.F,new_node(key));
        mainRoot = merge(temp.F,temp.S);
    }

    // removes element if it exists
    void erase(T key){
        pi temp = split(mainRoot,key);
        temp.F = split(temp.F,key-1).F;
        mainRoot = merge(temp.F,temp.S);
    }
    
    // returns true if key exists
    bool exists(T key){
        int curr = mainRoot;
        while(curr){
            if(treap[curr].key == key)
                return true;
            if(treap[curr].key < key) // if key exists it should be in right subtree
                curr = treap[curr].r;
            else // otherwise it should be in left subtree
                curr = treap[curr].l;
        }
        return false;
    }

    // returns left_most key of subtree if it exists otherwise boolean will be false
    pair<T,bool> get_left(int root){
        if(root == 0)
            return make_pair(0,false);
        while(treap[root].l)
            root = treap[root].l;
        return make_pair(treap[root].key,true);
    }

    // returns right_most key of subtree if it exists otherwise boolean will be false
    pair<T,bool> get_right(int root){
        if(root == 0)
            return make_pair(0,false);
        while(treap[root].r)
            root = treap[root].r;
        return make_pair(treap[root].key,true);
    }

    // returns smallest element greater than key if it exists otherwise returns key
    T upper_bound(T key){
        pi temp = split(mainRoot,key);
        pair<T,bool> res = get_left(temp.S);
        mainRoot = merge(temp.F,temp.S);
        if(res.S == false)
            return key;
        return res.F;
    }

    // returns biggest element less than key if it exists otherwise returns key
    T previous(T key){
        pi temp = split(mainRoot,key-1);
        pair<T,bool> res = get_right(temp.F);
        mainRoot = merge(temp.F,temp.S);
        if(res.S == false)
            return key;
        return res.F;
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

    // clears treap and re-initializes
    void clear(){
        treap.clear();
        treap.push_back(node());
        mainRoot = 0;
    }

    // initialization with array - should be sorted otherwise treap will break
    void init_array(int n, T arr[]){
        for(int i = 0;i < n;i ++)
            mainRoot = merge(mainRoot,new_node(arr[i]));
    }

    // initialization with vector - should be sorted otherwise treap will break
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
        int x;
        cin>>type>>x;
        if(type == "insert")
            treap.insert(x);
        else if(type == "delete")
            treap.erase(x);
        else if(type == "exists")
            cout<<(treap.exists(x) ? "true" : "false")<<endl;
        else if(type == "next"){
            int ans = treap.upper_bound(x);
            if(ans == x)
                cout<<"none"<<endl;
            else
                cout<<ans<<endl;
        }
        else if(type == "prev"){
            int ans = treap.previous(x);
            if(ans == x)
                cout<<"none"<<endl;
            else
                cout<<ans<<endl;
        }
        else if(type == "kth"){
            pair<int,bool> ans = treap.kth_element(x);
            if(ans.S == false)
                cout<<"none"<<endl;
            else
                cout<<ans.F<<endl;
        }
    }

}