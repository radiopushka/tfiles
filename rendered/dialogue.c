//#include "curses/curses.c"
#include "rendered.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "KEYS.h"

//text input dialogue

void dialogue_insert_char(char** mainbuff,char input,int index){
      
      char* oldinput=*mainbuff;

      int oldlen=strlen(oldinput);
      int ata_len=oldlen+2;
      
      char* atarashii=malloc(sizeof(char)*ata_len);
      memcpy(atarashii,oldinput,sizeof(char)*index);
      atarashii[index]=input;
      memcpy(atarashii+index+1,oldinput+index,sizeof(char)*(oldlen-index));
      atarashii[ata_len-1]=0;
      free(oldinput);
      *mainbuff=atarashii;

}
void dialogue_delete_char(char** mainbuff,char input,int index){
      
      char* oldinput=*mainbuff;

      int oldlen=strlen(oldinput);
      int ata_len=oldlen;
      
      char* atarashii=malloc(sizeof(char)*ata_len);
      memcpy(atarashii,oldinput,sizeof(char)*(index-1));
      memcpy(atarashii+index-1,oldinput+index,sizeof(char)*(oldlen-index));
      atarashii[ata_len-1]=0;
      free(oldinput);
      *mainbuff=atarashii;

}

char* input_dialogue(char* title,char* precursor,int x,int y, int width){
  int insert_index=0;

  char clrstring[width+4];
  memset(clrstring,' ',sizeof(char)*(width+3));
  clrstring[width+3]=0;

  char clrstring2[width+2];
  memset(clrstring2,' ',sizeof(char)*(width+1));
  clrstring2[width+1]=0;

  char* inist=NULL;
  if(precursor!=NULL){
    int len=strlen(precursor);
    inist=malloc(sizeof(char)*(len+1));
    memcpy(inist,precursor,sizeof(char)*(len+1));
  }

  int offset=0;
  if(inist!=NULL){
      offset=insert_index-width;
      if(offset<0)
        offset=0;
  }

  if(title!=NULL){
    if(strlen(title)>width){
      title[width]=0;
    }
  }


  int c=0;


  if(inist!=NULL){
    insert_index=strlen(inist);

  }

  while(c!=ENTER){

    fclear();
    mvmove(x,y);
    ffg(255,255,255);
    fbg(51,153,255);
    fputs(clrstring,stdout);
    mvmove(x,y);

    if(title!=NULL)
      fputs(title,stdout);

    mvmove(x,y+2);
    fputs(clrstring,stdout);
    mvmove(x,y+1);
    fputc(' ',stdout);
    fbg(230,230,230);
    fputs(clrstring2,stdout);
    fbg(51,153,255);
    fputc(' ',stdout);
    fbg(230,230,230);
    ffg(0,0,0);
    mvmove(x+1,y+1);

    int xcount=0;
    int strpos=offset;
    int print_at_end=1;
    if(inist!=NULL){
      for(char* nt=inist+offset;*nt!=0;nt++){
        if(xcount>width)
          break;

        if(strpos==insert_index){
          cblink();
          fbg(0,0,0);
          ffg(230,230,230);
          print_at_end=0;

        }else if(strpos==insert_index+1){
          fclear();
          fbg(230,230,230);
          ffg(0,0,0);

        }

        fputc(*nt,stdout);
        xcount++;
        strpos++;
      }
    }
    if(print_at_end==1){
          //blinking cursor no text
          cblink();
          fbg(230,230,230);
          ffg(0,0,0);
          fputc('|',stdout);

    }
  
    refresh();
  
    c=wgetch();

    if(c==K_ESC){
      free(inist);
      return NULL;
    }

    if((c>32 && c<127)||(c==' ')){
     
      if(inist==NULL){
        inist=malloc(sizeof(char)*2);
        inist[0]=c;
        inist[1]=0;
        insert_index++;
      }else{
        dialogue_insert_char(&inist,c,insert_index);
        insert_index++;
      }
      
    }else if(c==ARROW_LEFT){
      insert_index--;
      if(insert_index<0){
        insert_index=0;
      }
      
    }else if(c==ARROW_RIGHT && inist!=NULL ){
      insert_index++;
      int str_len=strlen(inist);
      if(insert_index>str_len){
        insert_index--;
      }
    }else if(c==K_BACK){
      if(inist!=NULL){
        //TODO
        /*
        int oldstr=strlen(inist);
        if(oldstr!=0){
          char* nptr=malloc(sizeof(char)*(oldstr));
          memcpy(nptr,inist,sizeof(char)*(oldstr-1));
          nptr[oldstr-1]=0;
          free(inist);
          inist=nptr;
        }
        */
        if(insert_index>0){
          dialogue_delete_char(&inist,c,insert_index);
          insert_index--;
        }
       
      }
     
    }
    offset=insert_index-width;
    if(offset<0)
          offset=0;

  }

  

  return inist;

}

//pop up dialogue

void show_popup(char* text,int x, int y){

  if(text==NULL)
    return; 

  mvmove(x-(strlen(text)>>1)-1,y);
  ffg(0,0,0);
  fbg(51,153,255);
  fputc(' ',stdout);
  fbg(230,230,230);
  fputs(text,stdout);
  fbg(51,153,255);
  fputc(' ',stdout);
  fclear();


}
//multi line popup

void show_large_popup(char* text,int x, int y){

  if(text==NULL)
    return; 

  //find the longest line in the string:
  int char_count=0;
  int char_count_max=0;
  for(char* c= text;*c!=0;c++){
      if(*c=='\n'){
        if(char_count>char_count_max){
          char_count_max=char_count;
        }
        char_count=0;
      }else{
        char_count++;
      }
  }
  if(char_count>char_count_max){
    char_count_max=char_count;
  }

  char filler[char_count_max+1];
  memset(filler,' ',sizeof(char)*(char_count_max));
  filler[char_count_max]=0;

  x=x-(char_count_max>>1);

  mvmove(x,y);
  ffg(0,0,0);
  fbg(51,153,255);
  fputs(filler,stdout);
  fbg(230,230,230);
  
  y++;
  mvmove(x,y);
  fputs(filler,stdout);
  mvmove(x,y);
  for(char* c=text;*c!=0;c++){
    if(*c=='\n'){
      y++;
      mvmove(x,y);
      fputs(filler,stdout);
      mvmove(x,y);
    }else{
      putc(*c,stdout);
    }
  }

  y++;
  mvmove(x,y);
  fbg(51,153,255);
  fputs(filler,stdout);
  fclear();


}


