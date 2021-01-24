#include <bits/stdc++.h>
using namespace std;


int main(){
    string s;
    cin>>s;

    int i,n = s.size();
    vector<int> kmp(n);
    kmp[0] = 0;

    /// prefix function (aka KMP) calculates an array kmp[] where kmp[i] denotes the length of the longest proper prefix of s[0...i]
    /// which is also a suffix of s[0...i], by definition kmp[0] = 0 (as s[0...0] has no proper prefix)

    for(i = 1;i < n;i ++){
        int j = kmp[i-1];
        while(j > 0 && s[i] != s[j])
            j = kmp[j-1];
        if(s[i] == s[j])
            j++;
        kmp[i] = j;
    }

    for(i = 0;i < n;i ++){
        cout<<kmp[i]<<" ";
    }

    /// can calculate occurrences of a pattern t in a string s by calculating kmp of string t + '#' + s and counting kmp[i] == t.size()

}