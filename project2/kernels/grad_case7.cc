#include "../run2.h"

void grad_case7(float (&dB)[16][32], float (&dA)[32][16]) {
  for (int i = 0; i < 16; i++) {
    if (i >= 0 && i < 16) {
      for (int j = 0; j < 32; j++) {
        if (j >= 0 && j < 32) {
          dA[j][i] = dA[j][i] + dB[i][j];
        }
      }
    }
  }
}

