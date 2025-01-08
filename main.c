#include "rendered/rendered.h"
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "rendered/KEYS.h"
#include "command_processor.c"

#define VOFFSET 2

char* prev_cmd=NULL;
char* prev_cmd2=NULL;
char* prev_sagasu=NULL;
char* file_buffer=NULL;


struct dir_holder{
  struct FileInfo* ff;
  struct dir_holder* next;
};

//clean up UI so that the program runs smoothly
void padded_terminal_cmd(char* cmd,int tw,int th){
          fclear();
          clear();
          fflush(stdout);
          free_terminal();

          
          //get pwd to point to the correct directory
          int cmdlen=strlen(cmd);
          //cd \"$CDDIR\";
          int extlen=12;
          char ncmd[cmdlen+extlen+1];
          memcpy(ncmd,"cd \"$CDDIR\";",sizeof(char)*extlen);
          memcpy(ncmd+extlen,cmd,sizeof(char)*(cmdlen+1));

          int retval=system(ncmd);
          init_inputs();

          if(retval <0 || retval >1){
            char error_msg[44];
            sprintf(error_msg,"child process exited with code %d",retval);
            show_popup(error_msg,tw>>1,th>>1);
            fflush(stdout);
            wgetch();
          }

}

void str_cpy(char* src,char** dest){
          int len=strlen(src)+1;
          free(*dest);
          *dest=malloc(sizeof(char)*len);
          memcpy(*dest,src,sizeof(char)*len);

}

int dir_exists(char* path){
  DIR* d= opendir(path);
  if(d==NULL)
    return -1;

  closedir(d);
  return 1;
}

void pre_process_cmd_data(char** cmd,char* path, struct FileInfo* ff){
          char* tmp=str_append(path,"/");
          char* loc=str_append(tmp,ff->name);
          free(tmp);

          char* file_no_appo=char_escaped(loc,'"');
          char* dir_no_appo=char_escaped(path,'"');
          free(loc);


          char* escaped=get_ps(*cmd,dir_no_appo,'d');
          free(dir_no_appo);

          char* escaped2=escaped;
          if(file_buffer!=NULL){
            char* cp_no_appo=char_escaped(file_buffer,'"');
            escaped2=get_ps(escaped,cp_no_appo,'b');
            free(cp_no_appo);
            free(escaped);
            
          }

          char* escaped3=get_ps(escaped2,file_no_appo,'f');
          free(file_no_appo);

          free(escaped2);

          free(*cmd);
          *cmd=escaped3;

}

void confirm_enter(char* command,char* path,struct FileInfo* ff,int th,int tw){
       char* cmd=input_dialogue("confirm?",command,tw/3,th>>1,tw/3);
        

        if(cmd!=NULL){
          str_cpy(cmd,&prev_cmd);

          pre_process_cmd_data(&cmd,path,ff);  

         
          padded_terminal_cmd(cmd,tw,th);

          free(cmd);
        }

}


int display_directory(char* path,char** ndirptr){
  DIR* d= opendir(path);

  struct dirent* dinf;

  if(d==NULL)
    return -1;


  struct dir_holder* dh=NULL;

  int ret_val_futsu=1;

  int count=0;
  while((dinf=readdir(d))!=NULL){
    if(strcmp(dinf->d_name,".")!=0 && !(strcmp(dinf->d_name,"..")==0&&strcmp(path,"/")==0)){
      struct dir_holder* dhi=malloc(sizeof(struct dir_holder));
      dhi->next=dh;
      dh=dhi;
      struct FileInfo* finf;
      int isdir=-1;
      if(dinf->d_type==4){
        isdir=1;
      }
      init_file(&finf,dinf->d_name,isdir,path);
      dh->ff=finf;
      count++;
    }

  }

  closedir(d);
  setenv("CDDIR",path,1);

  struct FileInfo* mfinf[count];
  int tsize=count;

  count=0;

  if(strcmp(path,"/")!=0){
    count=1;
  }

  if(dh!=NULL)
  while(dh->next!=NULL){
    
    mfinf[count]=dh->ff;
    count++;
    struct dir_holder* tsugi=dh->next;
    free(dh);
    dh=tsugi;
  }
 
  if(strcmp(path,"/")==0){
    mfinf[count]=dh->ff;
    sort_file_structure(0,count+1,mfinf);
  }else{
    mfinf[0]=dh->ff;
    sort_file_structure(1,count,mfinf);
  }
  free(dh);
  dh=NULL;



  
  //gui
  int c=-1;

  

  if(path[strlen(path)-1]=='/'){
    path[strlen(path)-1]=0;
  }
  int sel=0;

  while(c!=K_ESC){

   

    int tw,th;
    term_size(&tw,&th);

    th=th-VOFFSET;

    int yele=0;
    int xele=0;

    for(int y=1;y<th-B_HEIGHT-1;y=y+B_HEIGHT+1){
      yele++;
    }
    for(int x=1; x<tw-B_WIDTH; x=x+B_WIDTH){
        xele++;
    }

    if(c==ARROW_RIGHT){
      sel++;
      if(sel>=tsize){
        sel=tsize-1;
      }
    }else if(c==ARROW_LEFT){
      sel--;
      if(sel<0){
        sel=0;
      }
    }else if(c==ARROW_UP){
      int selp=sel;
      sel=sel-xele;
      if(sel<0){
        sel=selp;
      }
    }else if(c==ARROW_DOWN){
      int selp=sel;
      sel=sel+xele;
      if(sel>=tsize){
        sel=selp;
      }
    }else if(c==TAB && mfinf[sel]->is_image==1){
      clear();
      nocurs();

    
       char* tmp=str_append(path,"/");
       char* imloc=str_append(tmp,mfinf[sel]->name);
       free(tmp);

      int status=draw_full_image(imloc);
      if(status!=-1)
        wgetch();

      free(imloc);
    } else if(c==ENTER){
      char* exec_cmd;
      if(mfinf[sel]->is_dir==1){
        if(strcmp(mfinf[sel]->name,"..")!=0){
           char* tmp=str_append(path,"/");
          *ndirptr=str_append(tmp,mfinf[sel]->name);
          free(tmp);
          if(dir_exists(*ndirptr)==-1){
            free(*ndirptr);
            *ndirptr=NULL;

             show_popup("directory not available",tw>>1,th>>1);
             fflush(stdout);
             wgetch();

          }else{
            ret_val_futsu=2;
            goto futsu_deguchi;

          }
        }else{
          int pl=strlen(path);
          char* np=NULL;
          str_cpy(path,&np);
          *ndirptr=np;
          char* pend=np+pl;
          char* end=pend;
          for(;pend>=np;pend--){
              if(*pend=='/' && pend!=end){
                *(pend+1)=0;
                break;
              }
          }
          ret_val_futsu=2;
          goto futsu_deguchi;

        }

               
      }else if((exec_cmd=get_default_cmd(mfinf[sel]))!=NULL){
          int cmd_len=strlen(exec_cmd)+1;
          char* cmd_cpy=malloc(sizeof(char)*cmd_len);
          memcpy(cmd_cpy,exec_cmd,sizeof(char)*cmd_len);

          pre_process_cmd_data(&cmd_cpy,path,mfinf[sel]);  
          padded_terminal_cmd(cmd_cpy,tw,th);
          free(cmd_cpy);
          

      }else{
        char* cmd=input_dialogue("open cmd(%f,%d,%b)",prev_cmd,tw/3,th>>1,tw/3);
        

        if(cmd!=NULL){
          str_cpy(cmd,&prev_cmd);

          pre_process_cmd_data(&cmd,path,mfinf[sel]);  

         
          padded_terminal_cmd(cmd,tw,th);

          free(cmd);
        }
      }

    }else if( c == PG_UP){
      sel=0;
    }else if( c == PG_DN){
      sel=tsize-1;

    }else if( c == '/'){
        char* cmd=input_dialogue("search",prev_sagasu,tw/3,th>>1,tw/3);
        if(cmd!=NULL){
          str_cpy(cmd,&prev_sagasu);
          for(int i=sel+1;i<tsize;i++){
            if(strstr(mfinf[i]->name,cmd)!=NULL){
              sel=i;
              break;
            }
          }
          free(cmd);

        }

    }else if( c == ' '){
      show_large_popup("press any of:\nr - reload\nt - terminal command\np - show file's full path\nq - quit program\n/ - edit current path\nd - delete\nb - set buffer to path\nc - paste buffer here\nm - move buffer here",tw>>1,th>>1);
      fflush(stdout);
      int character=wgetch();

      switch(character){
        case 'r':
          goto f_refresh;
          break;
        case 't':
          char* cmd=input_dialogue("cmd(%d,%f,%b)",prev_cmd2,tw/3,th>>1,tw/3);
          if(cmd!=NULL){
              str_cpy(cmd,&prev_cmd2);
              pre_process_cmd_data(&cmd,path,mfinf[sel]);  

              padded_terminal_cmd(cmd,tw,th);
              free(cmd);
          }
          break;
         case 'p':
          char* tmp=str_append(path,"/");
          char* loc=str_append(tmp,mfinf[sel]->name);
          free(tmp);

          show_popup(loc,tw>>1,th>>1);
          free(loc);
          fflush(stdout);
          wgetch();
          break;
         case 'q':
          goto futsu_deguchi;
          break;
         case '/':
          char* npath=input_dialogue("edit path",path,tw/3,th>>1,tw/3);
          if(npath!=NULL){
            if(dir_exists(npath)!=-1){
              path_normalize(npath);
              *ndirptr=npath;
              ret_val_futsu=2;
              goto futsu_deguchi;
            }else{
              free(npath);
            }
          }
          break;
         case 'd':
          confirm_enter("rm -rf --verbose \"%f\"",path,mfinf[sel],th,tw);
          goto f_refresh;
          break;
         case 'b':
          free(file_buffer);
          char* tmp2=str_append(path,"/");
          char* loc2=str_append(tmp2,mfinf[sel]->name);
          free(tmp2);
          file_buffer=loc2;
          break;
        case 'c':
          if(file_buffer!=NULL){
            confirm_enter("cp -r --verbose \"%b\" \"%d\"",path,mfinf[sel],th,tw);
            goto f_refresh;
          }
          break;
        case 'm':
          if(file_buffer!=NULL){
            confirm_enter("mv --verbose \"%b\" \"%d\"",path,mfinf[sel],th,tw);
            goto f_refresh;

          }
          break;


      }

    }else if(c > 32 && c < 127){
      for(int i=sel+1;i<tsize;i++){
        if(mfinf[i]->name[0]==c){
          sel=i;
          break;
        }
      }
    }


    int frags=(yele*xele);



    

    clear();
    nocurs();
    int cp=(sel/frags)*frags;

    mvmove(0,0);
    printf("%s",path);
    mvmove(0,2);
    ffg(95,95,255);
    fbg(200,200,200);
    printf("%s",mfinf[sel]->name);
    int printsize=strlen(mfinf[sel]->name);
    for(int i=printsize;i<(tw<<1);i++){
      fputc(' ',stdout);
    }
    fclear();
    mvmove(0,3);
    for(int i=0;i<(tw);i++){
      fputc(' ',stdout);
    }


    for(int y=1;y<th-B_HEIGHT-1;y=y+B_HEIGHT+1){
      for(int x=1; x<tw-B_WIDTH; x=x+B_WIDTH){
        if(cp<tsize){
          load_file(mfinf[cp],path);
          int p=0;
          if(cp==sel){
            p=1;
          }
          display_file(mfinf[cp],x,y+VOFFSET,p);
          cp++;
        }
      }

    }

    mvmove(1,th);
    fclear();
    size_t filesize=mfinf[sel]->fsize;
    char print_type[3];
      print_type[0]=0;
      print_type[1]=0;
      print_type[2]=0;

    if(filesize>1000000000){
      //Giga Bytes
      filesize=filesize/1000000000;
      print_type[0]='G';
      print_type[1]='b';
      print_type[2]=0;
    }else if(filesize>1000000){
      //MegaBytes
      filesize=filesize/1000000; 
      print_type[0]='M';
      print_type[1]='b';
      print_type[2]=0;

      
    }else if(filesize>1000){
      //KBytes
      filesize=filesize/1000; 
      print_type[0]='K';
      print_type[1]='b';
      print_type[2]=0;

    }

    printf("%d/%d %lu%s buffer=%s",sel,tsize-1,filesize,print_type,file_buffer);
    refresh();
    c=wgetch();
  }

  futsu_deguchi:

  for(int i=0;i<tsize;i++){
    free_file(&mfinf[i]);
  }

  if(ret_val_futsu!=2)
    *ndirptr=NULL;

  return ret_val_futsu;

  f_refresh:
    ret_val_futsu=10;//just refresh
    goto futsu_deguchi;

}


int main(int argn,char* argv[]){

  char* inipath=getenv("PWD");
  char* slash="/";
  if(argn>1){
    inipath=argv[1];
    path_normalize(inipath);
  }
  if(inipath==NULL){
    inipath=slash;
  }

  char* dpath=malloc(sizeof(char)*(strlen(inipath)+1));
  memcpy(dpath,inipath,sizeof(char)*(1+strlen(inipath)));

  init_inputs();
  nocurs();
  setlocale(LC_ALL, "");

  int status=0;
  char* tpath;
  while(status!=1){
    if(status==-1){
      free(dpath); 
      dpath=malloc(sizeof(char)*(strlen(inipath)+1));

      memcpy(dpath,inipath,sizeof(char)*(1+strlen(inipath)));
    }
    if(status==2){
      int pl=strlen(tpath);
      free(dpath);
      dpath=malloc(sizeof(char)*(pl+1));
      memcpy(dpath,tpath,sizeof(char)*(pl+1));
      free(tpath);
      status=display_directory(dpath,&tpath);
    }else{

      status=display_directory(dpath,&tpath);
    }
  }
  
  free(prev_cmd);
  free(prev_cmd2);
  free(prev_sagasu);
  free(file_buffer);
  free(dpath);
  clear();
  curs();

  
  return 0;
}
