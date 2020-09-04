#include <bits/stdc++.h>
using namespace std;

struct PT{
    int x,y;
    void show(){cerr<<"{"<<x<<","<<y<<"}"<<endl;}
};

// ax - by = c
struct LINE{
    int a,b,c;
    void show(){cerr<<a<<"x"<<" - "<<b<<"y"<<" = "<<c<<endl;}
};

LINE get_line(PT a, PT b){
    LINE res;
    res.a = a.y - b.y;
    res.b = a.x - b.x;
    // keep a standard way of representing fractions
    if(res.a<0 || (res.a==0 && res.b<0)){
        res.a *= -1;
        res.b *= -1;
    }
    int g = __gcd(res.a,res.b);
    res.a /= g;
    res.b /= g;
    res.c = res.a*a.x - res.b*a.y;
    return res;
}

// return true if point p is in the grid defined by corners (a,b)
bool in_grid(PT p, PT a, PT b){
    return min(a.x,b.x)<=p.x && p.x<=max(a.x,b.x) && min(a.y,b.y)<=p.y && p.y<=max(a.y,b.y);
}

int main (){
    // print YES if point p is on line segment with endpoints (a,b)
    PT p,a,b;
    cin>>p.x>>p.y>>a.x>>a.y>>b.x>>b.y;

    LINE line = get_line(a,b);

    // if equation holds for point on the line and is also in the segment then answer is YES
    if(in_grid(p,a,b) && line.a*p.x - line.b*p.y - line.c == 0)
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;

    line.show();
    p.show();

}