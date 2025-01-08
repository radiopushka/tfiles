#include "png.c"

int main(int argn,char* argv[]){
  int width,height,bytes;
  unsigned char* bstart;
  unsigned char* bend;
  int status=read_png_file(argv[1],&width,&height,&bytes,&bstart,&bend); 
  if(status==-1){
    return -1;
  }
  unsigned char* tt=bstart;
  int cc=0;
  printf("{");
  for(;bstart<bend;bstart=bstart+bytes){
      unsigned char R,G,B;
      R=*bstart;
      G=*(bstart+1);
      B=*(bstart+2); 

      if(R==0&&G==0&&B==0){
        printf("-1,-1,-1,");
      }else{
        printf("%d,%d,%d,",R,G,B);
      }

      cc++;
  }

  printf("}\n");

  printf("size:%d\n",cc*3);

  free(tt);
}
