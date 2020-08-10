#include <stdio.h>

typedef struct {
    int x;
} C;

//void C::init();
void C_init(C* self) {
    self->x = 0;
}

// void C::increment();
void C_increment(C* self) {
    self->x++;
}

int C_get(const C* self) {
    return self->x;
}

int main() {
    C c;
    C_init(&c);

    for (int i = 0; i < 10; ++i) {
        C_increment(&c);
        printf("%d\n", C_get(&c));
    }
};
