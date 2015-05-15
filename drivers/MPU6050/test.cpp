#include "SimpleDMP.h"
#include <stdio.h>
#include <unistd.h>
int main()
{
  DMPInit();
  while(1) sleep(1);
}
