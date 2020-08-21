#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+1;

template<typename T>
struct SPARSE{
    vector<vector<T> > sparse;
    vector<int> log;
    const int maxPow = 22;
    int N;

    void init(int n){
        sparse.assign(n,vector<T>(maxPow));
        log.assign(n+1,0);
        N = n;

        for(int i = 2;i <= n;i++)
            log[i] = log[i/2] + 1;
    }

    // supports 0-indexing
    void build(T arr[]){
        int i,j;
        for(i = 0;i < N ;i++)
            sparse[i][0] = arr[i];

        for(j = 1;j < maxPow;j++)
            for(i = 0;i + (1<<j) <= N;i++)
                sparse[i][j] = min(sparse[i][j-1],sparse[i+(1<<(j-1))][j-1]);
    }

    T query(int l, int r){
        int k = log[r-l+1];
        return min(sparse[l][k],sparse[r-(1<<k)+1][k]);
    }

};

int main (){
    int n,q;
    cin>>n>>q;

    int i,arr[n];
    for(i=0;i<n;i++)
        cin>>arr[i];

    SPARSE<int> sparse;
    sparse.init(n);
    sparse.build(arr);

    while(q--){
        int x,y;
        cin>>x>>y;
        // 1-indexed queries
        cout<<sparse.query(x-1,y-1)<<endl;
    }

}