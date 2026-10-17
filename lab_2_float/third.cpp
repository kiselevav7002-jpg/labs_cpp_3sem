#include <iostream>
float pi_first(int n) {
    std::cout << std::fixed;
    std::cout.precision(10);
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
float pi_third(int n) {
    return pi_first(n) * 1.001;
}
int main(){
    std::cout << pi_third(318) << "\n";
}