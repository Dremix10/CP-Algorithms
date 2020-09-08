#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 2e6+1;

ull HASH[N],POW[N];

// 0 - indexed
ull get_substr(int x, int y){
    ull res = HASH[y];
    if(!x)return res;
    res -= HASH[x-1]*POW[y-x+1];
    return res;
}

int main (){
    string s;
    cin>>s;

    /// find lexicographically minimal rotation of string problem solution demonstrates both substring HASHing in O(1)
    /// and using that with binary search to find longest common prefix of some substrings of the string in LogN

    int n = s.size();
    s += s;
    int i;

    ull base = 31;
    HASH[0] = s[0] - 'a';
    POW[0] = 1;

    for(i=1;i<n*2;i++){
        HASH[i] = HASH[i-1] * base + s[i] - 'a';
        POW[i] = POW[i-1] * base;
    }
    
    int bestIdx = 0;
    for(i=1;i<n;i++){
        int l = 0,r = n-1;
        while(l<=r){
            int mid = (l+r)/2;
            if(get_substr(i,i+mid)==get_substr(bestIdx,bestIdx+mid))
                l = mid+1;
            else
                r = mid-1;
        }
        if(l!=n && s[i+l]<s[bestIdx+l])bestIdx = i;
    }
    cout<<s.substr(bestIdx,n)<<endl;

}