#include <stdio.h>

typedef struct C {
    int x;
} C;

void C_increment(C* self) {
    self->x++;
}

int C_get(const C* self) {
    return self->x;
}

void C_init(C* self) {
    self->x = 0;
}

int main() {
    C c;
    C_init(&c);
    for (int i = 0; i < 10; ++i) {
        C_increment(&c);
        printf("%d\n", C_get(&c));
    }

    int size = sizeof(c);
    printf("sizeof(C) = %d\n", size);
};
