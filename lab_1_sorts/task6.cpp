#include "sorts.h"

int main() {
    vector<int> sizes;
    for (int n=1; n<=1000; n+=20) { 
        sizes.push_back(n);
    }

    int repeats=100; 
    ofstream f("task6_small.csv");
    f << "N,bubble,insertion,selection,quick,merge,heap\n";

    for (int n : sizes) {
        vector<vector<int>> dataa(repeats, vector<int>(n));
        for (int r = 0; r < repeats; ++r) {
            for (int i = 0; i < n; ++i) {
                dataa[r][i] = rand_uns(0, 1000000);
            }
        }//для повторов чтобы усреднить потом

        double tb = 0;
        for (int r=0; r<repeats; ++r) {
            vector<int> a = dataa[r];
            double ts = get_time();
            bubble_sort(a);
            tb += get_time() - ts;
        }
        double ti = 0;
        for (int r = 0; r < repeats; ++r) {
            vector<int> a = dataa[r];
            double ts = get_time();
            insertion_sort(a);
            ti += get_time() - ts;
        }
        double tss = 0;
        for (int r = 0; r < repeats; ++r) {
            vector<int> a = dataa[r];
            double tt = get_time();
            selection_sort(a);
            tss += get_time() - tt;
        }

        double tq = 0;
        for (int r = 0; r < repeats; ++r) {
            vector<int> a = dataa[r];
            double tt = get_time();
            quick_sort(a);
            tq += get_time() - tt;
        }
        double tm = 0;
        for (int r = 0; r < repeats; ++r) {
            vector<int> a=dataa[r];
            double tt = get_time();
            merge_sort(a);
            tm += get_time() - tt;
        }

        double th = 0;
        for (int r = 0; r < repeats; ++r) {
            vector<int> a=dataa[r];
            double tt = get_time();
            heapsort(a);
            th += get_time() - tt;
        }

        f << n << ","
          << tb/repeats << "," << ti/repeats << "," << tss/repeats << ","
          << tq/repeats << "," << tm/repeats << "," << th/repeats << "\n";
        cout << "N=" << n << "\n";
    }

    f.close();
    return 0;
}