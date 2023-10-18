#include "../utilities/template.h"
#include "../../content/geometry/SegmentIntersection.h"
// change PT to double from int

int main(){
    typedef Point<double> P;
    for (int i=0; i<10000000; ++i){
        double a = rand()%100-50;
        double b = rand()%100-50;
        double c = rand()%100-50;
        double d = rand()%100-50;
        double a2 = rand()%100-50;
        double b2 = rand()%100-50;
        double c2 = rand()%100-50;
        double d2 = rand()%100-50;

        auto res1 = segInter(P(a,a2), P(b,b2), P(c,c2), P(d,d2));
        auto res2 = segInter(pt {a,a2}, pt {b,b2}, pt {c,c2}, pt {d,d2});
        assert(res1.size() == res2.size());

        rep(j,0,res1.size()){
            assert(abs(res1[j].x - res2[j].X) < 1e-9);
            assert(abs(res1[j].y - res2[j].Y) < 1e-9);
        }
    }
    cout << "tests passed!\n";
}