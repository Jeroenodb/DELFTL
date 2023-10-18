#include "bits/stdc++.h"
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;

#include "../../content/geometry/OnSegment.h"


int main(){
    typedef Point<int> P;
    for (int i=0; i<100000; ++i){
        int a = rand()%100-50;
        int b = rand()%100-50;
        int c = rand()%100-50;
        int a2 = rand()%100-50;
        int b2 = rand()%100-50;
        int c2 = rand()%100-50;

        assert(onSegment(pt {a,a2}, pt {b,b2}, pt {c,c2}) == onSegment(P(a,a2), P(b,b2), P(c,c2)));
    }
    cout << "tests passed!\n";
}