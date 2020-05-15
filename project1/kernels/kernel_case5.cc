#include "../run.h"

void kernel_case5(float (&B)[16][32], float (&C)[32][32], float (&D)[16][32], float &alpha, float &beta, float (&A)[16][32]) {
  float temp3[16][32];
  for (int i = 0; i < 16; i++) {
    if (i >= 0 && i < 16) {
      for (int j = 0; j < 32; j++) {
        if (j >= 0 && j < 32) {
          temp3[i][j] = 0;
        }
      }
    }
  }
  for (int i = 0; i < 16; i++) {
    if (i >= 0 && i < 16) {
      for (int j = 0; j < 32; j++) {
        if (j >= 0 && j < 32) {
          temp3[i][j] = temp3[i][j] + A[i][j];
          for (int k = 0; k < 32; k++) {
            if (k >= 0 && k < 32) {
              temp3[i][j] = temp3[i][j] + alpha * (B[i][k] * C[k][j]);
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
          A[i][j] = temp3[i][j];
        }
      }
    }
  }
  float temp4[16][32];
  for (int i = 0; i < 16; i++) {
    if (i >= 0 && i < 16) {
      for (int j = 0; j < 32; j++) {
        if (j >= 0 && j < 32) {
          temp4[i][j] = 0;
        }
      }
    }
  }
  for (int i = 0; i < 16; i++) {
    if (i >= 0 && i < 16) {
      for (int j = 0; j < 32; j++) {
        if (j >= 0 && j < 32) {
          temp4[i][j] = temp4[i][j] + A[i][j];
          temp4[i][j] = temp4[i][j] + beta * D[i][j];
        }
      }
    }
  }
  for (int i = 0; i < 16; i++) {
    if (i >= 0 && i < 16) {
      for (int j = 0; j < 32; j++) {
        if (j >= 0 && j < 32) {
          A[i][j] = temp4[i][j];
        }
      }
    }
  }
}

