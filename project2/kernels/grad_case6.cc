#include "../run2.h"

void grad_case6(float (&C)[8][16][3][3], float (&dA)[2][8][5][5], float (&dB)[2][16][7][7]) {
  for (int n = 0; n < 2; n++) {
    if (n >= 0 && n < 2) {
      for (int k = 0; k < 8; k++) {
        if (k >= 0 && k < 8) {
          for (int p = 0; p < 5; p++) {
            if (p >= 0 && p < 5) {
              for (int q = 0; q < 5; q++) {
                if (q >= 0 && q < 5) {
                  for (int c = 0; c < 16; c++) {
                    if (c >= 0 && c < 16) {
                      for (int i0 = 0; i0 < 7; i0++) {
                        if (i0 >= 0 && i0 < 7 && i0 - p >= 0 && i0 - p < 3) {
                          for (int i1 = 0; i1 < 7; i1++) {
                            if (i1 >= 0 && i1 < 7 && i1 - q >= 0 && i1 - q < 3) {
                              dB[n][c][i0][i1] = dB[n][c][i0][i1] + dA[n][k][p][q] * C[k][c][i0 - p][i1 - q];
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

