#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TAB 0xFFFF

int main(int argc, char **argv) {
  float sin_tab[MAX_TAB];
  printf("#pragma once\n\n");
  printf("#define MAX_TAB 0xFFFF\n\n");
  printf("float tab[MAX_TAB] = {\n");
  for (int x = 0; x < MAX_TAB; x++) {
    printf("  %f,\n", sinf(((float)x / (float)MAX_TAB) * M_PI * 2.0));
  }
  printf("};\n\n");

  printf("#define COS(x) tab[(x + 0x3FFF) & 0xFFFF]\n");
  printf("#define SIN(x) tab[(x & 0xFFFF)]\n");
  return 0;
}
