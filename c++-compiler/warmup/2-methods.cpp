#include <cstdio>

class C {
public:
    void increment() { ++x; };
    int get() const { return x; }

private:
    int x = 0;
};

int main() {
    C c;
    for (int i = 0; i < 10; ++i) {
        c.increment();
        std::printf("%d\n", c.get());
    }
}
