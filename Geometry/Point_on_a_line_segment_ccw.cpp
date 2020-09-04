#include <bits/stdc++.h>
using namespace std;

struct PT{
    int x,y;
    void show(){cerr<<"{"<<x<<","<<y<<"}"<<endl;}
};

int vector_product(PT a, PT b){
    return a.x*b.y - a.y*b.x;
}

int ccw(PT a, PT b, PT c){
    return vector_product({b.x-a.x,b.y-a.y},{c.x-a.x,c.y-a.y});
}

// return true if point p is in the grid defined by corners (a,b)
bool in_grid(PT p, PT a, PT b){
    return min(a.x,b.x)<=p.x && p.x<=max(a.x,b.x) && min(a.y,b.y)<=p.y && p.y<=max(a.y,b.y);
}


int main (){
    PT p,a,b;
    cin>>p.x>>p.y>>a.x>>a.y>>b.x>>b.y;

    // if points are collinear (ccw==0) and point p is in the segment defined by the 2 points then output YES
    if(in_grid(p,a,b) && ccw(a,b,p)==0)
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;
    p.show();

}