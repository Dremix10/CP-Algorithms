#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+1;
const ll INF = 1e18;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distribution;
ll rnd(ll l, ll r){return distribution(rng)%(r-l+1)+l;}

const int HS = 3;
int mod[HS];

struct custom_hash{ // !* SOS should assign mod array values for functionality *!
    int val[HS];
    custom_hash(){ fill(val,val+HS,0); }
    custom_hash(ll x){
        for(int i=0;i<HS;i++) val[i] = (x%mod[i] + mod[i]) % mod[i];
    }
    custom_hash operator+(custom_hash x){
        custom_hash res;
        res.val[0] = (val[0]+x.val[0]) % mod[0];
        res.val[1] = (val[1]+x.val[1]) % mod[1];
        res.val[2] = (1LL * val[2] * x.val[2]) % mod[2];
        return res;
    }
    bool operator==(const custom_hash &x)const{
        for(int i=0;i<HS;i++) if(val[i]!=x.val[i])return false;
        return true;
    }
};

int main (){
    int n;
    cin>>n;

    int i;
    ll arr[n];
    for(i=0;i<n;i++){
        arr[i] = rnd(1,INF);
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    mod[0] = 1e9+7;
    mod[1] = 998244353;
    mod[2] = rnd(1e8,1e9);

    custom_hash val[n];
    for(i=0;i<n;i++){
        val[i] = custom_hash(arr[i]);
        cout<<val[i].val[0]<<" ";
    }
    cout<<endl;

    // can add two hashes and compare if they're equal normaly with + and == operators
}