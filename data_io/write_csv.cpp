#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
  FILE *fw = fopen("gz.csv","w");
  if(fw == NULL) return -1;
  for (int i = 0; i < size; i++)
  {
    fprintf(fw,"%f,%f\n",gz[i], gravity_z[i]);
  }
  fclose(fw);
}
