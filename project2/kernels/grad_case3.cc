#include "../run2.h"

void grad_case3(float (&B)[16][16], float (&dC)[4][16], float (&dA)[4][16]) {
  for (int i = 0; i < 4; i++) {
    if (i >= 0 && i < 4) {
      for (int j = 0; j < 16; j++) {
        if (j >= 0 && j < 16) {
          for (int k = 0; k < 16; k++) {
            if (k >= 0 && k < 16) {
              dA[i][k] = dA[i][k] + dC[i][j] * B[k][j];
            }
          }
        }
      }
    }
  }
}

