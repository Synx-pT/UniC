// Copyright (C) Paul Tröster - All Rights Reserved

#include "./Gcd.h"

#include <cstdio>
#include <cstdlib>

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    printf("Usage: ./Gcd <integer> <integer>\n");
    return 1;
  }

  int x = atoi(argv[1]);
  int y = atoi(argv[2]);

  int result = calc_gcd(x, y, true);

  printf("gcd(%d, %d) = %d\n", y, x, result);
  return 0;
}
