#include "timer.h"
#include "vector.h"
#include "studentClass.h"

int main(){
    int sz = 10000;
    while(sz <=100000000){
        cout << endl;
        cout << "Testuojamas dydis: " << sz << endl;

        Timer t;
        std::vector<int> v1;
        int resizeCount = 0;
        for (int i = 1; i <= sz; ++i) {
            v1.push_back(i);
            if (v1.size() == v1.capacity()){
                resizeCount++;
            }
            }
        cout << "std::vector: " << t.elapsed() << endl;
        cout << "Times resize() was used: " << resizeCount << endl;

        t.reset();
        Vector<int> v2;
        int resizeCount2 = 0;
        for (int i = 1; i <= sz; ++i){
            v2.push_back(i);
            if (v2.size() == v2.capacity()){
                resizeCount2++;
            }
        }
        cout << "Vector class: " << t.elapsed() << endl;
        cout << "Times resize() was used: " << resizeCount2 << endl;

        sz*=10;
    };
}
