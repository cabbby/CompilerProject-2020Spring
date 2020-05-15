#include "../run.h"

void kernel_case6(float (&B)[2][16][7][7], float (&C)[8][16][3][3], float (&A)[2][8][5][5]) {
  float temp5[2][8][5][5];
  for (int n = 0; n < 2; n++) {
    if (n >= 0 && n < 2) {
      for (int k = 0; k < 8; k++) {
        if (k >= 0 && k < 8) {
          for (int p = 0; p < 5; p++) {
            if (p >= 0 && p < 5) {
              for (int q = 0; q < 5; q++) {
                if (q >= 0 && q < 5) {
                  temp5[n][k][p][q] = 0;
                }
              }
            }
          }
        }
      }
    }
  }
  for (int n = 0; n < 2; n++) {
    if (n >= 0 && n < 2) {
      for (int k = 0; k < 8; k++) {
        if (k >= 0 && k < 8) {
          for (int p = 0; p < 5; p++) {
            if (p >= 0 && p < 5) {
              for (int q = 0; q < 5; q++) {
                if (q >= 0 && q < 5) {
                  temp5[n][k][p][q] = temp5[n][k][p][q] + A[n][k][p][q];
                  for (int c = 0; c < 16; c++) {
                    if (c >= 0 && c < 16) {
                      for (int r = 0; r < 3; r++) {
                        if (p + r >= 0 && p + r < 7 && r >= 0 && r < 3) {
                          for (int s = 0; s < 3; s++) {
                            if (q + s >= 0 && q + s < 7 && s >= 0 && s < 3) {
                              temp5[n][k][p][q] = temp5[n][k][p][q] + B[n][c][p + r][q + s] * C[k][c][r][s];
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
  for (int n = 0; n < 2; n++) {
    if (n >= 0 && n < 2) {
      for (int k = 0; k < 8; k++) {
        if (k >= 0 && k < 8) {
          for (int p = 0; p < 5; p++) {
            if (p >= 0 && p < 5) {
              for (int q = 0; q < 5; q++) {
                if (q >= 0 && q < 5) {
                  A[n][k][p][q] = temp5[n][k][p][q];
                }
              }
            }
          }
        }
      }
    }
  }
}

