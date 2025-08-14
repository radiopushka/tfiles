
#include "./config.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argn,char* argv[]){

  CfgRaster cfg = read_cfg_file(argv[1]);

  debug_cfg_print(cfg);


  printf("value of cmd: %s\n",get_value_by(cfg,"my second section","test"));
  put_value_by(&cfg,"my second section","test","gcc -o file");
  put_value_by(&cfg,"my second section","compile","gcc ./thefile -o file");
  printf("value of cmd: %s\n",get_value_by(cfg,"my second section","test"));
  write_cfg_file(cfg,"output_cfg");
  free_cfg_mem(cfg);

  int size;
  int* tarray = string_to_array("1 -1 2 255 -255   ",&size);
  for(int i=0;i<size;i++){
    printf("%d\n",tarray[i]);
  }
  char* strn = array_to_string(tarray,size);
  printf("%s\n",strn);
  free(strn);
  free(tarray);
}
