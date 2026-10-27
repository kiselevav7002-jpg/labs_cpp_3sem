#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <cmath>
#include <cstdint>

using namespace std;

// 0 см 4 сем
void binary(unsigned int x) {
    for (int i = 31; i >= 0; --i) {
        cout << ((x >> i) & 1u);
        if (i % 4 == 0 && i != 0){ 
        cout << ' '; }
    }
    cout << '\n';
}

//1
union FloatView{
    float f;
    unsigned int u;
};

void FloatBits(float f){
    FloatView value{};
    value.f = f;
    binary(value.u);
}

// 2 см 5 сем
void mantissa() {
    cout << fixed;
    cout.precision(10);
    float x = 1.0f;
    int error = -1;
    unsigned long long pattern=1;
     for (int i = 0; i <= 15; ++i) {
        FloatView value; 
        value.f = x;
        bool match = ((unsigned long long)x == pattern);
         cout << "10^"  << i << " = " << x << " bits: ";
        binary(value.u);
        cout << "  " << (match ? "OK" : "ERR");

        if (!match && error == -1) {
            error = i;
            cout << "<- first wrong";}
        
        cout << '\n';
         x *= 10.0f;
        pattern *= 10ull;
    }
}

// 3
void infinitycycle() {   
    float x = 0.0f;
    float prev = x;
    const int end = 100000000;
    int step = 0;
    bool stop = false;

    for (int i = 1; i <= end; ++i) {
        prev = x;
        x += 1.0f; 
        step = i;

        if (x == prev) {  
            stop = true;
            break;
        }
    }

    if (stop) {
        FloatView value; value.f = x;
        cout << "Stop on" << step << '\n';
        cout << "Value: "<< x << '\n';
        cout << "Bits: "; binary(value.u); 
        cout << '\n';
    } else {
        cout << "Limit (" << end << ")"<<"\n";
        cout << "Current value: " <<x << "\n";
    }
}
//4
const double pi_ref = 3.141592653589793;

//pi/4=1-1/3+1/5-1/7...(б)
float pi_first(long long n) {
    float pi_4 = 1;
    for (long long i=1; i<n;++i){
        if(i%2 != 0){
            pi_4 -=1.f/(2*i +1);
        }
        if (i%2==0){
            pi_4 +=1.f/(2*i +1);
        }
    }
    return 4.f*pi_4;
}

// Нилакантха: 3+ 4*(1/2*3*4 -1/4*5*6 ...) (а)
float pi_second(long long n) {
    float pi_4=0;
     for (long long i=1; i<n;++i){
        if(i%2 != 0){
            pi_4 +=1.f/(2*i*(2*i+1)*(2*i+2));
        }
        if (i%2==0){
            pi_4 -=1.f/(2*i*(2*i+1)*(2*i+2));
        }
    }
    return 3.f+4.f*pi_4;
}

//сходится не к pi (в)
float pi_third(long long n) {
     float pi_4 = 1;
    for (long long i=1; i<n;++i){
        if(i%2 != 0){
            pi_4 -=1.f/(2*i +1);
        }
        if (i%2==0){
            pi_4 +=1.f/(2*i +1);
        }
    }
    return 1.001*4.f*pi_4;
}

// Бейли-Борвейна-Плюффа pi=sum(1/16^k ((4/8k+1)-(2/8k+4)-(1/8k+5)-(1/8k+6)) (г)
float pi_fourth(long long n) {
    float pi = 0;
    float koef = 1;
    for (long long i = 0; i < n; ++i) {
        float add = 4.0f / (8.0f*i + 1.0f)- 2.0f / (8.0f*i + 4.0f)
                   - 1.0f / (8.0f*i + 5.0f)- 1.0f / (8.0f*i + 6.0f);
        pi += add*koef;
        koef *= 0.0625f;
    }
    return pi;
}

//графики
float error_first(long long n){ return fabs((float)pi_first(n)-pi_ref); }
float error_second(long long n){ return fabs((float)pi_second(n)-pi_ref); }
float error_third(long long n){ return fabs((float)pi_third(n)-pi_ref); }
float error_fourth(long long n){ return fabs((float)pi_fourth(n)-pi_ref); }
void graphs_4(const string& filename) {
    ofstream f(filename);
    f<<fixed;
    f.precision(10);
    f << "N,err_first,err_second,err_third,err_fourth\n";
    for (long i = 1; i <= 10000000l; i *= 10) {
    for (long j = 2; (j <= 9 && i*j <= 10000000l); ++j) {
        long N =i*j;
        f << N << ','<< error_first(N) << ','<< error_second(N) << ','
              << error_third(N) << ','<< error_fourth(N) << '\n';
        }
    }
    f.close();
    cout << "Saved in " << filename << "\n";
}

//5

double get_time() {
    return chrono::duration_cast<chrono::microseconds>(
        chrono::steady_clock::now().time_since_epoch()
    ).count() / 1e6;
}

double measure_time(float (*f)(long long), long long n, int repeats) { //для всех подсчетов пи
    double total=0;
    for (int r = 0; r < repeats; ++r) {
        double t_start = get_time();
        volatile float res = f(n);
        double t_end = get_time();
        total+= (t_end - t_start);
    }
    return total/repeats;
}

void graphs_5(const string& filename) {
    ofstream file(filename);
    file<<fixed;
    file.precision(10);
    file << "d,formula,iterations,estimate,error,seconds\n";
    float (*funcs[])(long long) = {pi_first, pi_second, pi_third, pi_fourth};
    string names[]         = {"pi_first", "pi_second", "pi_third", "pi_fourth"};
    int max_limits[]       = {100000,1000000,10000,10000}; 
    int num_formulas = 4;
    int repeats = 100;
    double poww = 10; 

    for (int d = 1; d <= 7; ++d) {
        double target_error = 1.0 / poww;
        
        for (int i = 0; i < num_formulas; ++i) {
            float (*f)(long long) = funcs[i];
            string name = names[i];
            int limit = max_limits[i]; 

            long long amount = -1; // число итераций
            float res = 0.0f; // результат формулы

            // ищем минимальное N, при котором достигается точность
            for (long long n = 1; n <= limit; ++n) {
                res = f(n);
                if (fabs((double)res - pi_ref) < target_error) {
                    amount = n;
                    break;
                }
            }

            //нашли, замеряем время и пишем в файлик
            if (amount != -1) {
                double error = fabs((double)res - pi_ref);
                double avg_sec = measure_time(f, amount, repeats);
                file << d << "," << name << ","
                     << amount << "," << res << ","
                     << error << "," << avg_sec << "\n";
                
                cout << "d=" << d << " | " << name << " | N=" << amount << " | time=" << avg_sec << "s\n";
            } else {
                //не достигли за отведенный лимит
                file << d << "," << name << ",-1,-1,unreachable,-1\n";
                cout << "d= " << d  << name << " unreachable (limit " << limit << ")\n";
            }
        }
        poww *= 10;
    }
    file.close();
    cout << "Saved in " << filename << "\n";
}
int main(){
    cout << "0. unsigned int -> binary" << "\n";
    binary(10);
    binary(255);
    binary(0xDEADBEEF);
    cout << "\n";

    cout << "1. float -> binary" << "\n";
    FloatBits(1.0f);
    FloatBits(0.2f);
    FloatBits(-1.0f);
    cout << "\n";

    cout << "2. Mantissa" << "\n";
    mantissa();
    cout << "\n";

    cout << "3. Never stopped cycle" << "\n";
    infinitycycle();
    cout << "\n";

    cout << "4.Pi error(N)" << "\n";
    graphs_4("pi_graphs.csv");
    cout << "\n";

    cout << "5.Pi accuracy(t)" << "\n";
    graphs_5("time_results.csv");
    cout << "\n";

    cout << "That's all!!!!!!" << "\n";
    return 0;
}