#include "../run.h"

void kernel_case1(float (&A)[32][16]) {
  float temp1[32][16];
  for (int i = 0; i < 32; i++) {
    if (i >= 0 && i < 32) {
      for (int j = 0; j < 16; j++) {
        if (j >= 0 && j < 16) {
          temp1[i][j] = 0;
        }
      }
    }
  }
  for (int i = 0; i < 32; i++) {
    if (i >= 0 && i < 32) {
      for (int j = 0; j < 16; j++) {
        if (j >= 0 && j < 16) {
          temp1[i][j] = temp1[i][j] + 2;
        }
      }
    }
  }
  for (int i = 0; i < 32; i++) {
    if (i >= 0 && i < 32) {
      for (int j = 0; j < 16; j++) {
        if (j >= 0 && j < 16) {
          A[i][j] = temp1[i][j];
        }
      }
    }
  }
}

