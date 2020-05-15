#include "../run.h"

void kernel_example(float (&B)[32][16], float (&C)[32][16], float (&A)[32][16]) {
  float temp0[32][16];
  for (int i = 0; i < 32; i++) {
    if (i >= 0 && i < 32) {
      for (int j = 0; j < 16; j++) {
        if (j >= 0 && j < 16) {
          temp0[i][j] = 0;
        }
      }
    }
  }
  for (int i = 0; i < 32; i++) {
    if (i >= 0 && i < 32) {
      for (int j = 0; j < 16; j++) {
        if (j >= 0 && j < 16) {
          temp0[i][j] = temp0[i][j] + C[i][j] * B[i][j];
        }
      }
    }
  }
  for (int i = 0; i < 32; i++) {
    if (i >= 0 && i < 32) {
      for (int j = 0; j < 16; j++) {
        if (j >= 0 && j < 16) {
          A[i][j] = temp0[i][j];
        }
      }
    }
  }
}

