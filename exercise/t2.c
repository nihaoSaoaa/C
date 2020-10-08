#include <stdio.h>
int main()
{
  int x, y, z;
  x = 3;
  y = 2;
  z = 1;
  z-= x<y?x++:++y;
  printf("%c", char('A' + 2));
}
