#include "sorts.h"
int main() {
vector<int> sizes;
    for (int n=10000; n<=300000; n+=5000) { 
        sizes.push_back(n);
    }
int repeats=10;
    ofstream f("task2.csv");    
    f << "N,quick,merge,heapq\n";

    for (int n : sizes) {
        vector<int> base(n);
        for (int i = 0; i < n; ++i) {
            base[i] = rand_uns(0, 1000000);
        }
        double t1 = 0;
        for (int r = 0; r < repeats; ++r) {
            vector<int> aq = base;
            double tq = get_time();
            quick_sort(aq);
            t1 += get_time() - tq;
        }
       //vector<int> a1 = base;
        //double t1_start = get_time();
        //quick_sort(a1);
       // double t1 = get_time() - t1_start;
        double t2 = 0;
        for (int r = 0; r < repeats; ++r) {
            vector<int> a2 = base;
            double tm = get_time();
            merge_sort(a2);
            t2 += get_time() - tm;
        }


        double t3 = 0;
        for (int r = 0; r < repeats; ++r) {
            vector<int> a3 = base;
            double th = get_time();
            heapsort(a3);
            t3 += get_time() - th;
        }

        f << n << "," << t1/repeats << "," << t2/repeats << "," << t3/repeats << "\n";  
    }

    f.close();
    return 0;

}