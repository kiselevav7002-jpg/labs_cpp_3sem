#include "sorts.h"

int main() {
    vector<int> sizes = {1000, 2000, 4000, 8000, 16000, 20000, 32000};

    ofstream fs("task3_slow.csv");
    ofstream ff("task3_fast.csv");

    fs << "N,bubble,insertion,selection\n";
    ff << "N,quick,merge,heapq\n";    

    for (int n : sizes) {
        vector<int> base(n);
        for (int i = 0; i < n; ++i) {
            base[i] = rand_uns(0, 1000000);
        }

        vector<int> a1 = base;
        double t0= get_time();
        bubble_sort(a1);
        double t1 = get_time() - t0;

        vector<int> a2 = base;
        double t20= get_time();
        insertion_sort(a2);
        double t2 = get_time() - t20;

        vector<int> a3 = base;
        double t30= get_time();
        selection_sort(a3);
        double t3 = get_time() - t30;

        fs << n << "," << t1 << "," << t2 << "," << t3 << "\n";

        vector<int> b1 = base;
        double u10 = get_time();
        quick_sort(b1);
        double u1 = get_time() - u10;

        vector<int> b2 = base;
        double u20= get_time();
        merge_sort(b2);
        double u2 = get_time() - u20;

        vector<int> b3 = base;
        double u30 = get_time();
        heapsort(b3); 
        double u3 = get_time() - u30;

        ff << n << "," << u1 << "," << u2 << "," << u3 << "\n";

        cout << "N=" << n << "\n";
    }

    fs.close();
    ff.close();
    return 0;
}