int main(int, char **) {
  int a = 10;
  const int *p1 = &a;
  int *const p2 = &a;
  //   *p1 = 100;
  *p2 = 100;
}
