#include "command_processor.c"
#include<stdio.h>


//debug file

int main(int argn,char* argv[]){

  goto test_esc;

  char* pstring=get_ps(argv[1],argv[2],'s');
  
  printf("%s\n",pstring);
  int len2=strlen(pstring);
  printf("last char: %d\n",*(pstring+len2));
  free(pstring);


  return 0;

  test_esc:

  char* cesc=char_escaped(argv[1],argv[2][0]);
  
  printf("%s\n",cesc);
  int len=strlen(cesc);
  printf("last char: %d\n",*(cesc+len));
  free(cesc);
  return 0;
}


