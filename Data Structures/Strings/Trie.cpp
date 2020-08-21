#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+1;

struct TRIE{
    struct node{
        int son[26];
        int cnt; // counts strings with current prefix
        bool word;

        node() : cnt(0), word(false){
            fill(son,son+26,0);
        }
    };
    vector<node> trie;

    TRIE() {
        trie.push_back(node());
    }

    int new_node(){
        trie.push_back(node());
        return trie.size()-1;
    }

    void add(string &s){
        int curr = 0;
        for(int i = 0;i < s.size();i ++){
            int nxt = trie[curr].son[s[i]-'a'];
            if(!nxt){
                nxt = new_node();
                trie[curr].son[s[i]-'a'] = nxt;
            }
            curr = nxt;
            trie[curr].cnt ++;
        }
        trie[curr].word = true;
    }

    void remove(string &s){
        int curr = 0;
        for(int i = 0;i < s.size();i++){
            curr = trie[curr].son[s[i]-'a'];
            trie[curr].cnt --;
        }
        trie[curr].word = false;
    }

    int prefix(string &s){
        int curr = 0;
        for(int i = 0;i < s.size();i++){
            curr = trie[curr].son[s[i]-'a'];
            if(!curr)return 0;
        }
        return trie[curr].cnt;
    }

    bool exists(string &s){
        int curr = 0;
        for(int i = 0;i < s.size();i++){
            curr = trie[curr].son[s[i]-'a'];
            if(!curr)return false;
        }
        return trie[curr].word;
    }

};

int main (){
    int q;
    cin>>q;

    TRIE trie;

    while(q--){
        string type,s;
        cin>>type>>s;
        if(type == "add")
            trie.add(s);
        else if(type == "rem")
            trie.remove(s);
        else if(type == "count")
            cout<<trie.prefix(s)<<endl;
        else if(type == "exists")
            cout<<(trie.exists(s) ? "yes" : "no")<<endl;
    }

}