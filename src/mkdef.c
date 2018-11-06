#include<stdio.h>
#include<stdlib.h>

int main()
{
  int i,j;

  printf("#define D0 *p32data=v_dataLL; *p32data=v_dataHL;\n");
  printf("#define D1 *p32data=v_dataLH; *p32data=v_dataHH;\n");

  for(i=0;i<256;i++){
    printf("#define CS%02X case 0x%03X: ",i,i);// 0x%03x: \\\nbreak;",i);
    for(j=0;j<8;j++){
      if(i&(1<<j)) printf(" D1");
      else printf(" D0"); 
    }
    printf(" break;\n");
  }
  printf("#define CASE256 \\\n");
  for(i=0;i<16;i++){
    printf(" ");
    for(j=0;j<16;j++){
      printf(" CS%X%X",i,j);
    }
    printf(" \\\n");
  }
  printf(";\n");

  return 1;
}

