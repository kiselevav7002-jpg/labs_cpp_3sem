#include "sorts.h"
#include <cstdint>

struct Light {
    int x;
    bool operator<(const Light& o) const { return x < o.x; }
    bool operator>(const Light& o) const { return x > o.x; }
};

struct Heavy {
    int a;
    double b;
    char c[32];
    int arr[16];

    bool operator<(const Heavy& o) const { return a < o.a; }
    bool operator>(const Heavy& o) const { return a > o.a; }
};

template<typename T, typename SortFn>
double measure(vector<T>& base, SortFn sort_fn, int repeats = 3) {//функция для усреднения
    double total = 0;
    for (int r = 0; r < repeats; ++r) {
        vector<T> a = base;
        double t0 = get_time();
        sort_fn(a);
        total += get_time() - t0;
    }
    return total/repeats;
}
//сортировки для структур
template<typename T>
void bubble_sort_t(vector<T>& a) {
    int n = a.size();
    for (int i = 0; i != n - 1; ++i) {
        for (int j = 0; j != n - i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

template<typename T>
void heapify_t(vector<T>& a, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && a[left] > a[largest]) largest = left;
    if (right < n && a[right] > a[largest]) largest = right;
    if (largest != i) {
        swap(a[i], a[largest]);
        heapify_t(a, n, largest);
    }
}

template<typename T>
void heap_sort_t(vector<T>& a) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; --i) heapify_t(a, n, i);
    for (int i = n - 1; i != 0; --i) {
        swap(a[0], a[i]);
        heapify_t(a, i, 0);
    }
}

int main() {
    vector<int> sizes = {1000, 2000, 4000, 8000, 16000};
    int repeats = 3;

    ofstream fb("task6_types_bubble.csv");
    ofstream fh("task6_types_heap.csv");

    fb << "N,char,short,int,longlong,Light,Heavy\n";
    fh << "N,char,short,int,longlong,Light,Heavy\n";

    for (int n : sizes) {
        vector<char> vc(n);
        vector<short> vs(n);
        vector<int> vi(n);
        vector<long long> vl(n);
        vector<Light> vli(n);
        vector<Heavy> vh(n);

        for (int i = 0; i < n; ++i) {
            vc[i]= rand_uns(0, 127);
            vs[i] = rand_uns(0, 32000);
            vi[i]= rand_uns(0, 1000000);
            vl[i]= rand_uns(0, 1000000);
            vli[i].x= rand_uns(0, 1000000);
            vh[i].a= rand_uns(0, 1000000);
            vh[i].b=0;
            for (int k=0; k<16; ++k) vh[i].arr[k] = rand_uns(0,100);
        }

        double bc  = measure(vc,  bubble_sort_t<char>,       repeats);
        double bs  = measure(vs,  bubble_sort_t<short>,      repeats);
        double bi  = measure(vi,  bubble_sort_t<int>,        repeats);
        double bl  = measure(vl,  bubble_sort_t<long long>,  repeats);
        double bli = measure(vli, bubble_sort_t<Light>,      repeats);
        double bh  = measure(vh,  bubble_sort_t<Heavy>,      repeats);

        fb << n << "," << bc << "," << bs << "," << bi << "," << bl << ","<< bli << "," << bh << "\n";
        double hc= measure(vc,  heap_sort_t<char>,       repeats);
        double hs= measure(vs,  heap_sort_t<short>,      repeats);
        double hi= measure(vi,  heap_sort_t<int>,        repeats);
        double hl = measure(vl,  heap_sort_t<long long>,  repeats);
        double hli= measure(vli, heap_sort_t<Light>,      repeats);
        double hh= measure(vh,  heap_sort_t<Heavy>,      repeats);

        fh << n << "," << hc << "," << hs << "," << hi << "," << hl << "," << hli << "," << hh << "\n";

        cout << "N=" << n << "\n";
    }

    fb.close();
    fh.close();
    return 0;
}