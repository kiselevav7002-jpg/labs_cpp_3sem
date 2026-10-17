#include "sorts.h"
int main() {
    vector<int> sizes = {1000, 2000, 4000, 8000, 16000, 32000};
    ofstream f("task1.csv");
    f << "N,insertion\n";

    for (int n : sizes) {
        vector<int> base(n);
        for (int i = 0; i < n; ++i) {
            base[i] = rand_uns(0, 1000000);
        }

        vector<int> a=base;
        double t_start = get_time();
        insertion_sort(a);
        double t = get_time() - t_start;
        volatile int d = a.empty() ? 0 : a[0];
        (void)d;

        f << n << "," << t << "\n";
    }

    f.close();
    return 0;
}

