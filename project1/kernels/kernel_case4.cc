#include "../run.h"

void kernel_case4(float (&B)[16][32], float (&C)[32][32], float (&A)[16][32]) {
  float temp2[16][32];
  for (int i = 0; i < 16; i++) {
    if (i >= 0 && i < 16) {
      for (int j = 0; j < 32; j++) {
        if (j >= 0 && j < 32) {
          temp2[i][j] = 0;
        }
      }
    }
  }
  for (int i = 0; i < 16; i++) {
    if (i >= 0 && i < 16) {
      for (int j = 0; j < 32; j++) {
        if (j >= 0 && j < 32) {
          temp2[i][j] = temp2[i][j] + A[i][j];
          for (int k = 0; k < 32; k++) {
            if (k >= 0 && k < 32) {
              temp2[i][j] = temp2[i][j] + B[i][k] * C[k][j];
            }
          }
        }
      }
    }
  }
  for (int i = 0; i < 16; i++) {
    if (i >= 0 && i < 16) {
      for (int j = 0; j < 32; j++) {
        if (j >= 0 && j < 32) {
          A[i][j] = temp2[i][j];
        }
      }
    }
  }
}

