#include "bits/stdc++.h"
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;

#include "../../content/geometry/lineIntersection.h"


int main(){
    typedef Point<double> P;
    for (int i=0; i<10000000; ++i){
        int a = rand()%100-50;
        int b = rand()%100-50;
        int c = rand()%100-50;
        int d = rand()%100-50;
        int a2 = rand()%100-50;
        int b2 = rand()%100-50;
        int c2 = rand()%100-50;
        int d2 = rand()%100-50;

        if ((a==b and a2==b2) or ( c==d and c2==d2)) continue;

        auto res1 = lineInter(pt {a,a2}, pt {b,b2}, pt {c,c2}, pt {d,d2});
        auto res2 = lineInter(P(a,a2), P(b,b2), P(c,c2), P(d,d2));
        if (!(res1.first == res2.first and abs(res1.second.X - res2.second.x) < 1e-12 and abs(res1.second.Y - res2.second.y) < 1e-12)){
            cout << i << endl;
        }
    }
    cout << "tests passed!\n";
}