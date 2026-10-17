#include "sorts.h"
int main() {
 vector<int> sizes = {1000, 2000, 4000, 8000, 16000, 20000, 32000};

    ofstream f("task0.csv");    
    f << "N,bubble,insertion,selection\n";

    for (int n : sizes) {
        vector<int> base(n);
        for (int i = 0; i < n; ++i) {
            base[i] = rand_uns(0, 1000000);
        }

        vector<int> a1 = base;
        double t1_start = get_time();
        bubble_sort(a1);
        double t1 = get_time() - t1_start;

        vector<int> a2 = base;
        double t2_start = get_time();
        insertion_sort(a2);
        double t2 = get_time() - t2_start;

        vector<int> a3 = base;
        double t3_start = get_time();
        selection_sort(a3);
        double t3 = get_time() - t3_start;

        f << n << "," << t1 << "," << t2 << "," << t3 << "\n"; 
    }

    f.close();
    return 0;

}