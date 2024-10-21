#include <stdio.h>

int get_rx() {
    int value;
    printf("length: ");
    scanf("%d", &value);
    return value;
} 

int get_ry() {
    int value;
    printf("height: ");
    scanf("%d", &value);
    return value;
}

void star(int x, int y) {
    int i, j;
    for(i = 0; i < y; i++) {
        for(j = 0; j < x; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void draw_rect_xy(int x, int y) {
    int i, j, s;
    for(i = 0; i < x; i++) {
        printf("*");
    }
    printf("\n");
    for(j = 0; j < y - 2; j++) {
        printf("*");
        for(s = 0; s < x - 2; s++) {
            printf(" ");
        }
        printf("*");
        printf("\n");
    }
    for(i = 0; i < x; i++) {
        printf("*");
    }
    printf("\n");
}

void draw_triangle(int h) {
    int i, j;
    for(i = 1; i < h + 1; i++) {
        for(j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

int select_menu() {
    int i;
    do {
        printf("==========================\n");
        printf("*로 도형 그리기 메뉴\n");
        printf("1---줄\n");
        printf("2---사각형\n");
        printf("3---삼각형\n");
        printf("==========================\n");
        printf("사용할 그리기 메뉴 번호: ");
        scanf("%d", &i);
    } while(i < 1 || i > 3);
    switch(i) {
        case 1: {
            int x = get_rx();
            int y = get_ry();
            star(x, y);
        } break;
        case 2: {
            int x = get_rx();
            int y = get_ry();
            draw_rect_xy(x, y);
        } break;
        case 3: {
            int h = get_ry();
            draw_triangle(h);
        } break;
        default: {
            ;
        } break;
    }
}

int main(void) {
    select_menu();
    return 0;
}
