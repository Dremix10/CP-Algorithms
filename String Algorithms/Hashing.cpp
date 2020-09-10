#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
const int N = 2e6+1;

// randomization setup
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> distribution;
ll rnd(ll l, ll r){return distribution(rng)%(r-l+1)+l;}

const ll base = 31;

void slide(ll &hash, ll leftPow, char rem, char add, ll mod){
    hash = (hash - (rem-'a'+1)*leftPow + mod)%mod;
    hash = (hash*base + add-'a'+1)%mod;
}

bool comp(ll x[], ll y[], int n){
    for(int i = 0;i<n;i++){
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

    ll leftPow[3]={1,1,1},Htxt[3]={},Hpat[3]={};
    ll mod[3] = {(ll)1e9+7,998244353,rnd(1e8,1e9)};

    int i,j;

    for(i=0;i<m;i++){
        if(i){
            for(j=0;j<3;j++)
                leftPow[j] = (leftPow[j]*base)%mod[j];
        }
        for(j=0;j<3;j++){
            Hpat[j] = (Hpat[j] * base)%mod[j];
            Hpat[j] = (Hpat[j] + pat[i]-'a'+1)%mod[j];
            Htxt[j] = (Htxt[j] * base)%mod[j];
            Htxt[j] = (Htxt[j] + txt[i]-'a'+1)%mod[j];
        }
    }

    int ans = 0;
    if(comp(Htxt,Hpat,3))ans++;

    for(i=m;i<n;i++){
        for(j=0;j<3;j++)
            slide(Htxt[j],leftPow[j],txt[i-m],txt[i],mod[j]);
        if(comp(Htxt,Hpat,3))ans++;
    }
    cout<<ans<<endl;

}