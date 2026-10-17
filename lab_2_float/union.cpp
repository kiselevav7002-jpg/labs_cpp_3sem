#include <iostream>
using namespace std;

void binary(unsigned int x) {
    for (int i = 31; i >= 0; --i) {
        cout << ((x >> i) & 1u);
        if (i % 4 == 0 && i != 0) cout << ' '; 
    }
    cout << '\n';
}

//1
union FloatView{
    float f;
    unsigned int u;
};

int main() {
    FloatView value{};
    value.f = -0.0f;
    binary(value.u);
}