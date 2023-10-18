#include "bits/stdc++.h"
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;

#include "../../content/geometry/SegmentDistance.h"
// change PT to double, from int

int main(){
    for (int i=0; i<10000000; ++i){
        double a = rand()%100-50;
        double b = rand()%100-50;
        double c = rand()%100-50;
        double a2 = rand()%100-50;
        double b2 = rand()%100-50;
        double c2 = rand()%100-50;

        assert(abs(segDist(pt {a,a2}, pt {b,b2}, pt {c,c2}) - segDist(P(a,a2), P(b,b2), P(c,c2))) < 1e-9);
    }
    cout << "tests passed!\n";
}