#include "../run2.h"

void grad_case4(float (&B)[16][32], float (&C)[32][32], float (&dA)[16][32], float (&dB)[16][32], float (&dC)[32][32]) {
  for (int i = 0; i < 16; i++) {
    if (i >= 0 && i < 16) {
      for (int j = 0; j < 32; j++) {
        if (j >= 0 && j < 32) {
          for (int k = 0; k < 32; k++) {
            if (k >= 0 && k < 32) {
              dB[i][k] = dB[i][k] + dA[i][j] * C[k][j];
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
          for (int k = 0; k < 32; k++) {
            if (k >= 0 && k < 32) {
              dC[k][j] = dC[k][j] + dA[i][j] * B[i][k];
            }
          }
        }
      }
    }
  }
}

