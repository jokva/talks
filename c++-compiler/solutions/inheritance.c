#include <stdio.h>

typedef struct Parent {
    int x;
    double y;
} Parent;

/* parent as the first member */
typedef struct C1 {
    Parent parent;
    long z;
} C1;

/* parent members inlined */
typedef struct C2 {
    int x;
    double y;
    long z;
} C2;

void print_x(Parent* p) {
    printf("Parent.x = %d\n", p->x);
}

int main() {
    C1 c1;
    c1.parent.x = 2;
    c1.parent.y = 1.4;
    c1.z = -1;

    C2 c2;
    c2.x = 2;
    c2.y = 1.4;
    c2.z = -1;

    /* incompatible pointer type */
    print_x(&c1);

    /* undefined behaviour */
    print_x(&c2);

    /* this is ok */
    print_x((Parent*)&c);
}
