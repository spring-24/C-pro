#include <stdio.h>

void cirShift(int *sa, int *sb, int *sc, int *sd) {
    int temp;
    temp = *sa;
    *sa = *sd;
    *sd = *sc;
    *sc = *sb;
    *sb = temp;
}

int main(void) {
    int a = 3;
    int b = 5;
    int c = 7;
    int d = 9;
    printf("(swap 전) a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);
    cirShift(&a, &b, &c, &d);
    printf("(swap 후) a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);
    return 0;
}
