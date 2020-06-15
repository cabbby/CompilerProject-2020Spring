#include "../run2.h"

void grad_case10(float (&dA)[8][8], float (&dB)[10][8]) {
  for (int i = 0; i < 8; i++) {
    if (i >= 0 && i < 8 && i < 10 && i + 1 >= 0 && i + 1 < 10 && i + 2 >= 0 && i + 2 < 10) {
      for (int j = 0; j < 8; j++) {
        if (j >= 0 && j < 8) {
          dB[i][j] = dB[i][j] + dA[i][j] * ((float) 1) / ((float) 3);
        }
      }
    }
  }
  for (int i0 = 0; i0 < 10; i0++) {
    if (i0 - 1 >= 0 && i0 - 1 < 8 && i0 - 1 < 10 && i0 >= 0 && i0 < 10 && (i0 - 1) + 2 >= 0 && (i0 - 1) + 2 < 10) {
      for (int j = 0; j < 8; j++) {
        if (j >= 0 && j < 8) {
          dB[i0][j] = dB[i0][j] + dA[i0 - 1][j] * ((float) 1) / ((float) 3);
        }
      }
    }
  }
  for (int i0 = 0; i0 < 10; i0++) {
    if (i0 - 2 >= 0 && i0 - 2 < 8 && i0 - 2 < 10 && (i0 - 2) + 1 >= 0 && (i0 - 2) + 1 < 10 && i0 >= 0 && i0 < 10) {
      for (int j = 0; j < 8; j++) {
        if (j >= 0 && j < 8) {
          dB[i0][j] = dB[i0][j] + dA[i0 - 2][j] * ((float) 1) / ((float) 3);
        }
      }
    }
  }
}

