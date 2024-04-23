
#include "./Gcd.cpp"

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    printf("Usage: ./Gcd <integer> <integer>\n");
    return 1;
  }

  int x = atoi(argv[1]);
  int y = atoi(argv[2]);

  int result = calc_gcd(x, y, true);

  printf("gcd(%d, %d) = %d\n", x, y, result);
  return 0;
}
