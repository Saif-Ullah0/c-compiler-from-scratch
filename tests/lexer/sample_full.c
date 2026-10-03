#include <stdio.h>

#define MAX 100

/* This is a multi-line
   comment */
int main() {
    int x = 42;              // single-line comment
    int y = 0xFF;
    float pi = 3.14f;
    float e = 1.5e-3;
    char grade = 'A';
    char nl = '\n';
    char *msg = "Hello, \"World\"!\n";

    if (x > 0 && y <= 255) {
        x += y;
        x <<= 2;
        x++;
    }

    for (int i = 0; i < MAX; i++) {
        x -= i;
    }

    return 0;
}