#include "../run.h"

void kernel_case7(float (&A)[32][16], float (&B)[16][32]) {
  float temp6[16][32];
  for (int i = 0; i < 16; i++) {
    if (i >= 0 && i < 16) {
      for (int j = 0; j < 32; j++) {
        if (j >= 0 && j < 32) {
          temp6[i][j] = 0;
        }
      }
    }
  }
  for (int i = 0; i < 16; i++) {
    if (i >= 0 && i < 16) {
      for (int j = 0; j < 32; j++) {
        if (j >= 0 && j < 32) {
          temp6[i][j] = temp6[i][j] + A[j][i];
        }
      }
    }
  }
  for (int i = 0; i < 16; i++) {
    if (i >= 0 && i < 16) {
      for (int j = 0; j < 32; j++) {
        if (j >= 0 && j < 32) {
          B[i][j] = temp6[i][j];
        }
      }
    }
  }
}

