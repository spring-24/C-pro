#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp;
    char fname[100];
    int number, count = 0;
    char name[20];
    float score, total = 0.0;
    printf("성적 파일 이름을 입력하시오:  ");
    scanf("%s", fname);    

    // 성적 파일을 쓰기 모드로 연다.
    if((fp = fopen(fname, "w")) == NULL) {
        fprintf(stderr,"성적 파일 %s을 열 수 없습니다.\n", fname);
        exit(1);
    }

    // 사용자로부터 학번, 이름, 성적을 입력받아서 파일에 저장한다.
    while(1) {
        printf("학번, 이름, 성적을 입력하시요: (음수이면 종료)");
        scanf("%d", &number);
        if( number < 0 ) {
            break;
        }
        scanf("%s %f", name, &score);
        fprintf(fp, " %d %s %f", number, name, score);
        fprintf(fp, "\n");
    }
    fclose(fp);
    // 성적 파일을 읽기 모드로 연다.
    if((fp = fopen(fname, "r")) == NULL) {
        fprintf(stderr,"성적 파일 %s을 열 수 없습니다.\n", fname);
        exit(1);
    }

    // 파일에서 성적을 읽어서 평균을 구한다.
    while(!feof(fp)) {
        fscanf(fp, "%d %s %f", &number, name, &score);
        total += score;
        count++;
    }
    printf("평균 = %f\n", total/count);
    fclose(fp);
    return 0;
}
