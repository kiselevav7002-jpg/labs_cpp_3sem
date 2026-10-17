#include "sorts.h"

vector<int> generate(int n, int type) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rand_uns(0, 1000000);
    }
    if (type == 0) {
        sort(a.begin(), a.end());                       
    } else if (type == 2) {
        sort(a.rbegin(), a.rend());       
    }
    return a;
}

int main() {

    vector<int> sizes = {1000, 2000, 4000, 8000, 16000};
    int repeats = 3;

    ofstream fb("task4_bubble.csv");
    ofstream fi("task4_insertion.csv");
    ofstream fs("task4_selection.csv");
    ofstream fq("task4_quick.csv");
    ofstream fm("task4_merge.csv");
    ofstream fh("task4_heapq.csv");

    fb << "N,sorted,random,reversed\n";
    fi << "N,sorted,random,reversed\n";
    fs << "N,sorted,random,reversed\n";
    fq << "N,sorted,random,reversed\n";
    fm << "N,sorted,random,reversed\n";
    fh << "N,sorted,random,reversed\n";

    for (int n : sizes) {
        vector<int> base_sorted   = generate(n, 0);
        vector<int> base_random   = generate(n, 1);
        vector<int> base_reversed = generate(n, 2);

        // пузырьком
         double tb_s = 0, tb_r = 0, tb_v = 0;
        for (int r = 0; r < repeats; ++r) {
            vector<int> a = base_sorted;
            double ts = get_time(); bubble_sort(a); tb_s += get_time() - ts;

            vector<int> b = base_random;
            double us = get_time(); bubble_sort(b); tb_r += get_time() - us;

            vector<int> c = base_reversed;
            double vs = get_time(); bubble_sort(c); tb_v += get_time() - vs;
        }
        fb << n << "," << tb_s/repeats << "," << tb_r/repeats << "," << tb_v/repeats << "\n";
        // вставкой
         double ti_s = 0, ti_r = 0, ti_v = 0;
        for (int r = 0; r < repeats; ++r) {
            vector<int> a = base_sorted;
            double ts = get_time(); insertion_sort(a); ti_s += get_time() - ts;

            vector<int> b = base_random;
            double us = get_time(); insertion_sort(b); ti_r += get_time() - us;

            vector<int> c = base_reversed;
            double vs = get_time(); insertion_sort(c); ti_v += get_time() - vs;
        }
        fi << n << "," << ti_s/repeats << "," << ti_r/repeats << "," << ti_v/repeats << "\n";
        // выбором
         double ts_s = 0, ts_r = 0, ts_v = 0;
        for (int r = 0; r < repeats; ++r) {
            vector<int> a = base_sorted;
            double ts = get_time(); selection_sort(a); ts_s += get_time() - ts;

            vector<int> b = base_random;
            double us = get_time(); selection_sort(b); ts_r += get_time() - us;

            vector<int> c = base_reversed;
            double vs = get_time(); selection_sort(c); ts_v += get_time() - vs;
        }
        fs << n << "," << ts_s/repeats << "," << ts_r/repeats << "," << ts_v/repeats << "\n";
        // Хоара
         double tq_s = 0, tq_r = 0, tq_v = 0;
        for (int r = 0; r < repeats; ++r) {
            vector<int> a = base_sorted;
            double ts = get_time(); quick_sort(a); tq_s += get_time() - ts;

            vector<int> b = base_random;
            double us = get_time(); quick_sort(b); tq_r += get_time() - us;

            vector<int> c = base_reversed;
            double vs = get_time(); quick_sort(c); tq_v += get_time() - vs;
        }
        fq << n << "," << tq_s/repeats << "," << tq_r/repeats << "," << tq_v/repeats << "\n";
        // Слиянием
         double tm_s = 0, tm_r = 0, tm_v = 0;
        for (int r = 0; r < repeats; ++r) {
            vector<int> a = base_sorted;
            double ts = get_time(); merge_sort(a); tm_s += get_time() - ts;

            vector<int> b = base_random;
            double us = get_time(); merge_sort(b); tm_r += get_time() - us;

            vector<int> c = base_reversed;
            double vs = get_time(); merge_sort(c); tm_v += get_time() - vs;
        }
        fm << n << "," << tm_s/repeats << "," << tm_r/repeats << "," << tm_v/repeats << "\n";
        // куча
         double th_s = 0, th_r = 0, th_v = 0;
        for (int r = 0; r < repeats; ++r) {
            vector<int> a = base_sorted;
            double ts = get_time(); heapsort(a); th_s += get_time() - ts;

            vector<int> b = base_random;
            double us = get_time(); heapsort(b); th_r += get_time() - us;

            vector<int> c = base_reversed;
            double vs = get_time(); heapsort(c); th_v += get_time() - vs;
        }
        fh << n << "," << th_s/repeats << "," << th_r/repeats << "," << th_v/repeats << "\n";

        cout << "N=" << n << "\n";
    }

    fb.close(); fi.close(); fs.close();
    fq.close(); fm.close(); fh.close();
    return 0;
}