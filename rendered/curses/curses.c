/*
 *author: Evan Nikitin 2025 Jan17th
 * */
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "terminal.c"


void mvprint(int x,int y,char* string){
  printf("\033[%d;%dH%s",x,y,string);
}
void mvmove(int x,int y){
  printf("\033[%d;%dH",y,x);
}
void clear(void){
  printf("\033c");
}
void refresh(void){
  fflush(stdout);
}

void nocurs(void){
  printf("\x1b[?25l");
}
void curs(void){
  printf("\x1b[?25h");
}
void fpixel(unsigned char r,unsigned char g,unsigned char b){
  printf("\x1b[48;2;%d;%d;%dm ",r,g,b);
}
void fbg(unsigned char r,unsigned char g,unsigned char b){
  printf("\x1b[48;2;%d;%d;%dm",r,g,b);
}
void ffg(unsigned char r,unsigned char g,unsigned char b){
  printf("\x1b[38;2;%d;%d;%dm",r,g,b);
}
void cblink(void){
  printf("\x1b[5m");
}

void fclear(void){
  printf("\x1b[0m");
}

void deguchi_nara(void){
  fclear();
  curs();
  clear();
  reset_terminal_mode();

}


void init_inputs(void){
  set_terminal_mode();
  atexit(deguchi_nara);
}
void free_terminal(void){
  reset_terminal_mode();
}

void term_size(int* width,int* height){
  struct winsize winf;
  int w;
  int h;
  ioctl(0, TIOCGWINSZ, &winf);
  h=winf.ws_row;
  w=winf.ws_col;
  if(h<1){
    h=30;
  }
  if(w<1){
    w=100;
  }
  *width=w;
  *height=h;
}

int wgetch(void)
{
  fflush(stdin);

  int ret=kbhit();

  if(ret!=1){
    return -1;
  }

  int output=0;
  int index=0;

  unsigned char buff;

  while(read(0,&buff,sizeof(char))!=-1){

    output|=buff<<index;
    index=index+8;
    //nonblocking
    if(kbhit_nb()!=1){
      return output;
    }
  }

  return -1;
}
