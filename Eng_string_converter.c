#include <stdio.h>

// 대소문자 변환 함수
void caseconv(char in[], char out[]) {
    int i = 0;
    while (in[i] != '\0') {
        if (in[i] >= 'a' && in[i] <= 'z') {
            out[i] = in[i] - 32;
        } else if (in[i] >= 'A' && in[i] <= 'Z') {
            out[i] = in[i] + 32;
        } else {
            out[i] = in[i];
        }
        i++;
    }
    out[i] = '\0';
}

// 문자열 거꾸로 변환 함수
void backward(char in[], char out[]) {
    int i;
    int length = 0;
    while (in[length] != '\0') {
        length++;
    }
    for (i = 0; i < length; i++) {
        out[i] = in[length - i - 1];
    }
    out[length] = '\0';
}

int main(void) {
    char state[100];
    char caseconv_out[100];
    char backward_out[100];

    printf("문자열을 입력하시오: ");
    scanf("%s", &state);

    caseconv(state, caseconv_out);
    backward(caseconv_out, backward_out);

    printf("대소문자 변환 후: %s\n", caseconv_out);
    printf("거꾸로 변환 후: %s\n", backward_out);

    return 0;
}
