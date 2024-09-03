#include <stdio.h>

int main(void) {

    char code; //문자형 변수 code 선언.

    printf("알파벳을 입력해주세요: ");
    scanf("%c", &code);

    if(code >= 'A' && code <= 'Z') {
        printf("%c", code+32); //대문자에서 소문자로 변환
    }
    else if(code >= 'a' && code <= 'z') {
        printf("%c", code-32); //소문자에서 대문자로 변환
    }
    else {
        printf("ERROR"); //알파벳 이외의 문자가 입력된 경우
    }

    return 0;

}