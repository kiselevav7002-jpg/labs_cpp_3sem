#include <iostream>
#include <chrono>
#include <cmath>
#include <xmmintrin.h> 

using namespace std;

void binary(unsigned int x) {
    for (int i = 31; i >= 0; --i) {
        cout << ((x >> i) & 1u);
    }
}

union FloatView {
    float f;
    unsigned int u;
};

double get_time() {
    return chrono::duration_cast<chrono::microseconds>(
        chrono::steady_clock::now().time_since_epoch()
    ).count() / 1e6;
}

const double pi_ref = 3.141592653589793;

//pi/4=1-1/3+1/5-1/7...(б)
float pi_first(int n) {
    float pi_4 = 1;
    for (int i=1; i<n;++i){
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
float pi_second(int n) {
    float pi_4=0;
     for (int i=1; i<n;++i){
        if(i%2 != 0){
            pi_4 +=1.f/(2*i*(2*i+1)*(2*i+2));
        }
        if (i%2==0){
            pi_4 -=1.f/(2*i*(2*i+1)*(2*i+2));
        }
    }
    return 3.f+4.f*pi_4;
}

// Бейли-Борвейна-Плюффа (г)
float pi_fourth(int n) {
    float pi = 0;
    float koef = 1;
    for (int i = 0; i < n; ++i) {
        float add = 4.0f / (8.0f*i + 1.0f)- 2.0f / (8.0f*i + 4.0f)
                   - 1.0f / (8.0f*i + 5.0f)- 1.0f / (8.0f*i + 6.0f);
        pi += add*koef;
        koef *= 0.0625f;
    }
    return pi;
}

//DAZ/FTZ
void enableDAZ_FTZ() {
    _mm_setcsr(_mm_getcsr() | 0x8040);
}

void disableDAZ_FTZ() {
    _mm_setcsr(_mm_getcsr() & ~0x8040);
}

double measure_math(float start_val, float multiplier_or_addend, bool is_multiply) {
    volatile float res = start_val;
    double t_start = get_time();
    
    for (int i = 0; i < 10000000; ++i) { 
        if (is_multiply) {
            res *= multiplier_or_addend;
        } else {
            res += multiplier_or_addend;
        }
        
       
        if (res == 0.0f || res > 1e10f || res < -1e10f) {
            res = start_val; 
        }
    }
    
    double t_end = get_time();
    return t_end - t_start;
}

double measure_avg(float start_val, float multiplier_or_addend, bool is_multiply, int repeats = 100) {
    double total=0.0;
    for (int r = 0; r < repeats; ++r) {
        total += measure_math(start_val, multiplier_or_addend, is_multiply);
    }
    return total/repeats;
}

int main() {
    cout<<fixed;
    cout.precision(10);
    cout << "6*. Underflow\n\n";

    cout << "1. Denorm in memory\n";
    float x = 1.0f;
    for (int i = 0; i < 127; ++i){x /= 2.0f;} 
    
    FloatView v;
    v.f = x;
    cout << "Number: " << x << "\n";
    cout << "Bits:  "; binary(v.u);
    cout << "\n\n";

    float normal_val = 1.0f;
    float denorm_val = x; //min denorm
    
    int repeats = 100; //больше не получается сделать


    disableDAZ_FTZ();
    cout << "[DAZ/FTZ OFF]\n";
    
    double time_add_norm = measure_avg(normal_val, 1e-30f, false, repeats);
    double time_add_denorm = measure_avg(denorm_val, 1e-30f, false, repeats);
    
    double time_mul_norm = measure_avg(normal_val, 1.000001f, true, repeats);
    double time_mul_denorm = measure_avg(denorm_val, 1.000001f, true, repeats);

    cout << " + norm:   " << time_add_norm << " s\n";
    cout << " + denorm: " << time_add_denorm << " s\n";
    cout << " * norm:   " << time_mul_norm << " s\n";
    cout << " * denorm: " << time_mul_denorm << " s\n\n";

    enableDAZ_FTZ();
    cout << "[DAZ/FTZ ON]\n";
    
    time_add_norm = measure_avg(normal_val, 1e-30f, false, repeats);
    time_add_denorm = measure_avg(denorm_val, 1e-30f, false, repeats);
    
    time_mul_norm = measure_avg(normal_val, 1.000001f, true, repeats);
    time_mul_denorm = measure_avg(denorm_val, 1.000001f, true, repeats);

    cout << " + norm:   " << time_add_norm << " s\n";
    cout << " + denorm: " << time_add_denorm << " s\n";
    cout << " * norm:   " << time_mul_norm << " s\n";
    cout << " * denorm: " << time_mul_denorm << " s\n\n";
    

    cout << "3. Influence on accuracy (N = 1000)\n";
    int N = 1000;

    disableDAZ_FTZ();
    cout << "[DAZ/FTZ OFF]\n";
    float res1_off = pi_first(N);
    float res2_off = pi_second(N);
    float res4_off = pi_fourth(N);
    cout << "1: " << res1_off << " (err: " << fabs(res1_off-pi_ref) << ")\n";
    cout << "2: " << res2_off << " (err: " << fabs(res2_off-pi_ref) << ")\n";
    cout << "4: " << res4_off << " (err: " << fabs(res4_off-pi_ref) << ")\n\n";

    enableDAZ_FTZ();
    cout << "[DAZ/FTZ ON]\n";
    float res1_on = pi_first(N);
    float res2_on = pi_second(N);
    float res4_on = pi_fourth(N);
    cout << "1: " << res1_on << " (err: " << fabs(res1_on-pi_ref) << ")\n";
    cout << "2: " << res2_on << " (err: " << fabs(res2_on-pi_ref) << ")\n";
    cout << "4: " << res4_on << " (err: " << fabs(res4_on-pi_ref) << ")\n";

    disableDAZ_FTZ();
    return 0;
}