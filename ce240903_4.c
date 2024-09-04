#include <stdio.h>

int get() {
    int value;
    printf("층을 입력하세요: ");
    scanf("%d", &value);
    return value;
}

int main(void) {
    int i, j;
    int s = get();
    for(int n = 0; n < s; n++) {
        for(i = n; i < s - 1; i++) {
            printf(" ");
        }
        for(j = s; j > i - n; j--) {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}