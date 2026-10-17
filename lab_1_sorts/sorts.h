#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//таймер
double get_time() {
    return chrono::duration_cast<chrono::microseconds>(
        chrono::steady_clock::now().time_since_epoch()
    ).count() / 1e6;
}

//случайное целое в диапазоне [min, max]
int rand_uns(int min, int max) {
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    static default_random_engine e(seed);
    uniform_int_distribution<int> d(min, max);
    return d(e);
}


//void swap(int &x, int&y){ 
  //  int z=x;
  //  x=y;
   // y=z;
//}
//глупые сортировки O(N^2)
//пузырьком
void bubble_sort(vector<int>& a) {
  int n = a.size();
  for(int i=0; i!=n-1; ++i){
    for(int j=0; j!=n-i-1; ++j){
      if (a[j] > a[j+1]){
        swap(a[j], a[j+1]);}}}}
//выбором
void selection_sort(vector<int>& a){
  int n = a.size();
  for(int i=0; i!=n-1; ++i){
    int k = i;
    for(int j=i+1; j!= n; ++j){
      if (a[j] < a[k]){
         k = j;
   }}
swap(a[k], a[i]);}}

//вставкой
void insertion_sort(vector<int>& a){
  int n = a.size();
  for(int i = 1; i!= n; ++i){
    for(int j=i; j!=0;--j){
      if (a[j] < a[j-1]){
        swap(a[j], a[j-1]);}}}}
// умные сортировки O(N log N) 
//Хоара
void qsort1(vector<int>& a, int left, int  right){
    if(left >= right){
        return;}

    int x = a[(left+ right)/2] ;
    int i=left;
    int j=right;
    while(i <= j){
        while (a[i] < x){
            ++i;}
        while (a[j] > x){
            --j;}
        if (i <= j){
            swap(a[i], a[j]);
            ++i;
            --j;}
    }
    qsort1(a, left, j);
    qsort1(a, i, right);
}
void quick_sort(vector<int>& a) {
    qsort1(a, 0, (int)a.size() - 1);
}
//слиянием
void merge(vector<int>& a, vector<int>& b, vector<int>& c){
    int i = 0;
    int j=0; 
    int n = a.size();
    int m = b.size();
    
    while (i < n && j < m){
        if (a[i] <= b[j]){
            c.push_back(a[i]);
            ++i;}
        else{
            c.push_back(b[j]);
            ++j;}}
    while (i < n){
        c.push_back(a[i]);
        ++i;}
    while (j < m){
        c.push_back(b[j]);
        ++j;}

}
void merge_sort(vector<int>& a){
   int n = a.size();
    if (n <= 1){
        return;}

    vector<int> left,right;
    for (int i=0; i!= n/2; ++i){
        left.push_back(a[i]);}

    
    for(int j=n/2; j!= n; ++j){
        right.push_back(a[j]);}

    merge_sort(left);
    merge_sort(right);
    vector<int> c;
    c.reserve(n);
    merge(left,right,c);
    a.swap(c);//было а=с но вроде так быстрее
    }
//куча
void heapify(vector<int>&a, int n, int i){
   int  largest = i;  // корень
    int left = 2*i + 1;
    int right = 2*i + 2;

    //сравниваем с левым потомком
    if (left < n && a[left] > a[largest]){
        largest = left;}

    //сравниваем с правым потомком
    if (right < n && a[right] > a[largest]){
        largest = right;}

    //если наибольший не корень
    if (largest != i){
        swap(a[i], a[largest]);
        heapify(a, n, largest); } }
void build_heap(vector<int>& a){
    int n = a.size();
    //проходим от последнего родителя к корню
    for(int i= n/2 - 1;i>= 0; --i){
        heapify(a, n, i);}}
void heapsort(vector<int>& a){
    int n=a.size();

    //построение максимальной кучи
    build_heap(a);
//извлекаем элементы, корень в конец
    for (int i=n-1; i!= 0; --i){
        swap(a[0], a[i]);  
        heapify(a, i, 0);}}