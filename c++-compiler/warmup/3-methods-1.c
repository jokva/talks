#include <stdio.h>

typedef struct C {
    int x;
    void (*increment)(struct C*);
    int (*get)(const struct C*);
} C;

void f1(C* c) {
    c->x++;
}

int f2(const C* c) {
    return c->x;
}

void init(C* c) {
    c->x = 0;
    c->increment = &f1;
    c->get = &f2;
}

C constructor() {
    C c = {
        .x = 0,
        .increment = &f1,
        .get = &f2,
    };
    return c;
}

int main() {
    C c;
    init(&c);
    for (int i = 0; i < 10; ++i) {
        c.increment(&c);
        printf("%d\n", c.get(&c));
    }
    int size = sizeof(c);
    printf("sizeof(C) = %d\n", size);
};
