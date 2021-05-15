#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e6+1;

// randomization setup
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distribution;
ll rnd(ll l, ll r){return distribution(rng)%(r-l+1)+l;}

const ll base = 256;
const int M = 3;

void slide(ll &hash, ll leftPow, ll rem, ll add, ll mod){
    hash = (hash + mod - ((rem*leftPow)%mod))%mod;
    hash = (hash*base + add)%mod;
}

bool comp(ll x[], ll y[]){
    for(int i = 0;i<M;i++){
        if(x[i]!=y[i])return false;
    }
    return true;
}

int main (){
    string txt,pat;
    cin>>txt>>pat;

    // find occurencies of pattern in text using hashing and sliding window technique

    int n = txt.size();
    int m = pat.size();

    // special case text smaller than pattern
    if(n < m){
        cout<<0<<endl;
        return 0;
    }

    ll leftPow[M]={1,1,1},Htxt[M]={},Hpat[M]={};
    ll mod[M] = {(ll)1e9+9,(ll)1e9+7,998244353};
    ull leftPowU = 1,HtxtU = 0,HpatU = 0;

    int i,j;

    for(i=0;i<m;i++){
        if(i){
            for(j=0;j<M;j++)
                leftPow[j] = (leftPow[j]*base)%mod[j];
            leftPowU = leftPowU*base;
        }
        for(j=0;j<M;j++){
            Hpat[j] = (Hpat[j] * base)%mod[j];
            Hpat[j] = (Hpat[j] + (int)(pat[i]))%mod[j];
            Htxt[j] = (Htxt[j] * base)%mod[j];
            Htxt[j] = (Htxt[j] + (int)(txt[i]))%mod[j];
        }
        HpatU = HpatU * base + (int)(pat[i]);
        HtxtU = HtxtU * base + (int)(txt[i]);
    }

    int ans = 0;
    if(comp(Htxt,Hpat) && HpatU == HtxtU)ans++;

    for(i=m;i<n;i++){
        for(j=0;j<M;j++){
            slide(Htxt[j],leftPow[j],txt[i-m],txt[i],mod[j]);
        }
        HtxtU = HtxtU - (int)(txt[i-m])*leftPowU;
        HtxtU = HtxtU * base + (int)(txt[i]);
        if(comp(Htxt,Hpat) && HpatU == HtxtU)ans++;
    }
    cout<<ans<<endl;

}
