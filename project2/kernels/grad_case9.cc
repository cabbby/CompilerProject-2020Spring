#include "../run2.h"

void grad_case9(float (&dB)[4][6], float (&dA)[4]) {
  for (int i = 0; i < 4; i++) {
    if (i >= 0 && i < 4) {
      for (int j = 0; j < 6; j++) {
        if (j >= 0 && j < 6) {
          dA[i] = dA[i] + dB[i][j];
        }
      }
    }
  }
}

