#include <stdio.h>

int get() {
    int value;
    printf("피보나치 수열의 마지막 항의 번호 입력: ");
    scanf("%d", &value);
    return value;
}

int main(void) {
    int n = get();
    int f1 = 1;
    int f2 = 2;
    int f3;
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            printf("%d ", f1);
        }
        if(i == 1) {
            printf("%d ", f2);
        }
        if(i >= 1) {
            f3 = f1 + f2;
            printf("%d ", f3);
            f1 = f2;
            f2 = f3;
        }
    }
    return 0;
}
