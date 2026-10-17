#include "sorts.h"

int main() {
    vector<int> sizes = {1000, 2000, 4000, 8000, 16000};

    ofstream fb("task5_bubble.csv");
    ofstream fs("task5_selection.csv");

    fb << "N,bubble\n";
    fs << "N,selection\n";           

    for (int n : sizes) {
        vector<int> base(n);
        for (int i = 0; i < n; ++i) {
            base[i] = rand_uns(0, 1000000);
        }
        vector<int> a1 = base;
        double t0= get_time();
        bubble_sort(a1);
        double t1= get_time() - t0;
        
        fb << n << "," << t1 << "\n";

        vector<int> b1= base;
        double u0= get_time();
        selection_sort(b1);
        double u1= get_time()-u0;


        fs << n << "," << u1 <<  "\n";

        cout << "N=" << n << " \n";
    }

    fb.close();
    fs.close();
    return 0;
}