#include "../run2.h"

void grad_case8(float (&dB)[32], float (&dA)[2][16]) {
  for (int i0 = 0; i0 < 2; i0++) {
    for (int i1 = 0; i1 < 16; i1++) {
      if (i0 * 16 + i1 >= 0 && i0 * 16 + i1 < 32 && i0 >= 0 && i0 < 2 && i1 >= 0 && i1 < 16) {
        dA[i0][i1] = dA[i0][i1] + dB[i0 * 16 + i1];
      }
    }
  }
}

