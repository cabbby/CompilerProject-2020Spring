#include "../run2.h"

void grad_case2(float (&A)[4][16], float (&dB)[4][16], float (&dA)[4][16]) {
  for (int i = 0; i < 4; i++) {
    if (i >= 0 && i < 4) {
      for (int j = 0; j < 16; j++) {
        if (j >= 0 && j < 16) {
          dA[i][j] = dA[i][j] + dB[i][j] * (A[i][j] + A[i][j]);
          dA[i][j] = dA[i][j];
        }
      }
    }
  }
}

