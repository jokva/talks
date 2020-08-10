#include <iostream>

struct C {
    int x;
};

int main() {
    C c[3];
    std::cout << "sizeof = " << sizeof(c) << "\n";
}
