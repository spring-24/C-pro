#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void StrFile(char *fname) {
    FILE *fp;
    char line[100];
    int width, height, maxval;
    int *pixel_values;
    int start_range, end_range;
 
    // 파일 읽기
    if ((fp = fopen(fname, "r")) == NULL) {
        fprintf(stderr, "파일 %s을 열 수 없습니다.\n", fname);
        exit(1);
    }

    // 파일 유형 분석 및 출력
    fgets(line, sizeof(line), fp);

    // 주석을 건너뛰고, 다음 유효한 데이터를 찾음
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (line[0] != '#') {
            break;
        }
    }

    // 이미지의 크기(너비와 높이) 읽기
    sscanf(line, "%d %d", &width, &height);

    // 최대 그레이스케일 값 읽기
    fscanf(fp, "%d", &maxval);

    // 픽셀 값을 저장할 동적 메모리 할당
    pixel_values = (int*)malloc(width * height * sizeof(int));
    if (pixel_values == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }

    // 픽셀 값을 읽어와서 배열에 저장
    for (int i = 0; i < width * height; i++) {
        fscanf(fp, "%d", &pixel_values[i]);
    }

    // 출력할 범위 입력
    printf("출력할 범위 기점 (예: 2): ");
    scanf("%d", &start_range);
        printf("출력할 범위 종점 (예: 9): ");
    scanf("%d", &end_range);

    // 범위 유효성 검사
    if (start_range < 1 || end_range > width * height || start_range > end_range) {
        printf("잘못된 범위입니다. 1부터 %d 사이의 값을 입력하세요.\n", width * height);
        free(pixel_values);
        fclose(fp);
        return;
    }

    // 범위 내의 픽셀 값 출력
    printf("파일을 열었습니다.\n");
    for (int i = start_range; i <= end_range; i++) {
        printf("%d\n", pixel_values[i - 1]);  // 배열은 0부터 시작하므로 i-1
    }

    // 동적 메모리 해제 및 파일 닫기
    free(pixel_values);
    fclose(fp);
}

void select_menu() {
    char fname[100];
    int menu;
    do {
        printf("=====================\n");
        printf("1. 파일 읽기\n");
        printf("2. 종료하기\n");
        printf("=====================\n");
        printf("원하는 항목 입력: ");
        scanf("%d", &menu);
    } while(menu < 1 || menu > 2);

    switch(menu) {
        case 1: {
            printf("실행하려는 파일 이름 입력: ");
            scanf("%s", fname);
            StrFile(fname);
        } break;
        case 2: {
            printf("프로그램을 종료함.\n");
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
