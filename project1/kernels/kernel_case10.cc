#include "../run.h"

void kernel_case10(float (&B)[10][10], float (&A)[8][8]) {
  float temp7[8][8];
  for (int i = 0; i < 8; i++) {
    if (i >= 0 && i < 8 && i < 10 && i + 1 >= 0 && i + 1 < 10 && i + 2 >= 0 && i + 2 < 10) {
      for (int j = 0; j < 8; j++) {
        if (j >= 0 && j < 8 && j < 10) {
          temp7[i][j] = 0;
        }
      }
    }
  }
  for (int i = 0; i < 8; i++) {
    if (i >= 0 && i < 8 && i < 10 && i + 1 >= 0 && i + 1 < 10 && i + 2 >= 0 && i + 2 < 10) {
      for (int j = 0; j < 8; j++) {
        if (j >= 0 && j < 8 && j < 10) {
          temp7[i][j] = temp7[i][j] + ((float) ((B[i][j] + B[i + 1][j]) + B[i + 2][j])) / ((float) 3);
        }
      }
    }
  }
  for (int i = 0; i < 8; i++) {
    if (i >= 0 && i < 8 && i < 10 && i + 1 >= 0 && i + 1 < 10 && i + 2 >= 0 && i + 2 < 10) {
      for (int j = 0; j < 8; j++) {
        if (j >= 0 && j < 8 && j < 10) {
          A[i][j] = temp7[i][j];
        }
      }
    }
  }
}

