#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+1;

template<typename T> vector<int> compress(vector<T> in){
    vector<T> arr = in;
    sort(arr.begin(),arr.end());
    arr.erase(unique(arr.begin(),arr.end()),arr.end());
    for(int &x : in)
        x = int(lower_bound(arr.begin(),arr.end(),x)-arr.begin());
    return in;
}


int main (){
    int n;
    cin>>n;

    int i;
    vector<int> arr(n);
    for(i=0;i<n;i++)
        cin>>arr[i];
    // compress input
    vector<int> compressed = compress<int>(arr);
    for(auto x : compressed)
        cout<<x<<" ";

}