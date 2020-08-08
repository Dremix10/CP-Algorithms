#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+1;

template <typename T>
struct BIT{
    vector<T> bit;
    int N;

    void init(int n){
        N = n;
        bit.assign(n+1,0);
    }

    void update(int pos, T val){
        while(pos<=N){
            bit[pos] += val;
            pos += pos & -pos;
        }
    }

    T prefix(int pos){
        T sum = 0;
        while(pos>0){
            sum += bit[pos];
            pos -= pos & -pos;
        }
        return sum;
    }

    T query(int l, int r){
        return prefix(r) - prefix(l-1);
    }

};

int main (){
    int n,q;
    cin>>n>>q;

    BIT<ll> bit;
    bit.init(n);

    int i;
    for(i=1;i<=n;i++){
        int x;
        cin>>x;
        bit.update(i,x);
    }

    while(q--){
        int x,y;
        cin>>x>>y;
        cout<<bit.query(x,y)<<endl;
    }

}