#include "../run2.h"

void grad_case5(float (&C)[32][32], float (&D)[4][32], float (&dA)[16][32], float (&dB)[16][32][4]) {
  for (int i = 0; i < 16; i++) {
    if (i >= 0 && i < 16) {
      for (int j = 0; j < 32; j++) {
        if (j >= 0 && j < 32) {
          for (int k = 0; k < 32; k++) {
            if (k >= 0 && k < 32) {
              for (int l = 0; l < 4; l++) {
                if (l >= 0 && l < 4) {
                  dB[i][k][l] = dB[i][k][l] + dA[i][j] * C[k][j] * D[l][j];
                }
              }
            }
          }
        }
      }
    }
  }
}

