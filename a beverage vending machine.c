#include <stdio.h>

int get() {  // 금액 투입에 따른 입력함수
    int value;
    printf("금액 투입: ");
    scanf("%d", &value);
    return value;
}


int exchange500(money, ask) {  // 잔돈 500원 정산 함수
    int result = (money - ask) / 500;
    return result;
}


int exchange100(money, ask, exch500) {  // 잔돈 100원 정산 함수
    int result = (money - ask - exch500 * 500) / 100;
    return result;
}


int select_menu() {  // 음료 메뉴 고르는 함수
    int i;
    do {
        printf("1--핫식스\n");
        printf("2--레스비\n");
        printf("3--애플망고\n");
        scanf("%d", &i);
        printf("선택한 메뉴: %d\n", i);
    } while (i < 1 || i > 3);
    return i;
}


int main(void) {
    int money = get();  // 투입한 금액
    int i = select_menu();  // 메뉴 고르기
    int hm = 1500;  // 핫식스 가격
    int rm = 800;  // 레스비 가격
    int am = 1200;  // 애플망고 가격

    switch (i) {
        case 1: {  // 핫식스를 선택한 경우
            printf("가격: %d\n", hm);
            printf("투입금액: %d\n", money);
            if (money > hm) {
                printf("정상처리\n");
                int exch500 = exchange500(money, hm);
                int exch100 = exchange100(money, hm, exch500);
                printf("잔금 500원 동전수: %d 개 \n", exch500);
                printf("잔금 100원 동전수: %d 개 \n", exch100);
            } 
            else if (money == hm) {
                printf("정상처리\n");
            } 
            else {
                printf("요금부족\n");
            }
        } break;
        
        case 2: {  // 레스비를 선택한 경우
            printf("가격: %d\n", rm);
            printf("투입금액: %d\n", money);
            if (money > rm) {
                printf("정상처리\n");
                int exch500 = exchange500(money, rm);
                int exch100 = exchange100(money, rm, exch500);
                printf("잔금 500원 동전수: %d 개 \n", exch500);
                printf("잔금 100원 동전수: %d 개 \n", exch100);
            } 
            else if (money == rm) {
                printf("정상처리\n");
            }
            else {
                printf("요금부족\n");
            }
        } break;

        case 3: {  // 애플망고를 선택한 경우
            printf("가격: %d\n", rm);
            printf("투입금액: %d\n", money);
            if (money > am) {
                printf("정상처리\n");
                int exch500 = exchange500(money, am);
                int exch100 = exchange100(money, am, exch500);
                printf("잔금 500원 동전수: %d 개 \n", exch500);
                printf("잔금 100원 동전수: %d 개 \n", exch100);
            } 
            else if (money == am) {
                printf("정상처리\n");
            } 
            else {
                printf("요금부족\n");
            }
        } break;
    }
    return 0;
}
