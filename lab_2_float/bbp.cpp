#include <iostream>
double pi_fourth(int n) {
   std::cout << std::fixed;
    std::cout.precision(10);
    double pi = 0;
    double koef = 1;
    for (int i = 0; i < n; ++i) {
        double add = 4.0/ (8.0*i + 1.0)- 2.0/ (8.0*i + 4.0)
                   - 1.0 / (8.0*i + 5.0)- 1.0 / (8.0*i + 6.0);
        pi += add*koef;
        koef *= 0.0625;
    }
    return pi;
}
int main(){
    std::cout << pi_fourth(10000) << "\n";
}