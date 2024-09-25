#include <stdio.h>
#define SIZE 10

int main(void) {
  int list[SIZE] = {3, 2, 9, 7, 1, 4, 8, 0, 6, 5};
  int temp = 0;
  int i, j;
  printf("랜덤하게 섞여있는 데이터 값 : ");
  for (int i = 0; i < SIZE; i++) {
    printf("%d ", list[i]);
  }
  for (i = 0; i < SIZE - 1; i++) {
    for (j = 0; j < SIZE - 1 - i; j++) {
      if (list[j] > list[j + 1]) {
        temp = list[j];
        list[j] = list[j + 1];
        list[j + 1] = temp;
      }
    }
  }
  printf("\n\n");
  printf("버블 정렬을 사용하여 오름차순한 결과 : ");
  for (i = 0; i < SIZE; i++) {
    printf("%d ", list[i]);
  }
  return 0;
}
