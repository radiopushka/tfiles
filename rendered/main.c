/*
 *author: Evan Nikitin 2025 Jan17th
 * */
#include "icons.h"
#include "rendered.h"
#include <sys/stat.h>
#include <ctype.h>
#include "KEYS.h"
#include <dirent.h>



char* file_last_prefix(char* path,char ident){
  char* name=malloc(sizeof(char)*256);
  memset(name,0,sizeof(char)*256);
  char* fslash=path;
  char* opath;
  int len=strlen(path)+1;
  if(len>255){
    len=255;
  }
  char* end=path+len;
  char* end2=end-1;


  for(opath=end2; opath>=path; opath--){
    if(*opath==ident && opath < end2){
      fslash=opath+1;
      break;
    }
  }

 
  memcpy(name,fslash,sizeof(char)*(end-fslash));
  name[255]=0;
  return name;
  
}

void process_file_name(char* name,char* ext){
  int extname=strlen(ext);
  int nlen=strlen(name);
  int stepback=(B_WIDTH-2)<<1;
  if(nlen > stepback && extname <= 6){
    memcpy(name+(stepback-extname),ext,sizeof(char)*extname);
    *(name+(stepback-1-extname))='.';
  }

}

char* str_append(char* before,char* after){
  int bl=strlen(before);
  int al=strlen(after);
  char* out=malloc(sizeof(char)*(bl+al+1));
  memcpy(out,before,sizeof(char)*(bl+1));
  memcpy(out+bl,after,sizeof(char)*(al+1));
  return out;
}

void str_lower(char* input){
  for(char* tr=input;*tr!=0;tr++){
      *tr=tolower(*tr);
  }
}

char* get_default_cmd(struct FileInfo* ff){
  char** ending=m_endings;
  int count=0;
  while(**ending!='.'){
    if(strcmp(*ending,ff->extension)==0){
      return m_cmd[count];
    }
    ending++;
    count++;
  }
  return NULL;
}

int image_icon_helper(char* path,int* icon){
  #ifndef NO_IMAGE_SUPPORT
  
    return get_image_icon(path,icon);
  #endif /* ifndef NO_IMAGE_SUPPORT */
  return -1;
}

void load_file(struct FileInfo* ff,char* dirpath){
  if(ff->loaded==1)
    return;

  char* fp=str_append(dirpath,"/");
  char* fpf=str_append(fp,ff->name);
  free(fp);

  char linkread[4098];

  if(ff->is_dir==DIR_T){
    memcpy(ff->icon,IFOLDER,sizeof(int)*ICONSIZE);
  }else if( ff->is_dir == FILE_T ){
    if(image_icon_helper(fpf,ff->icon) != -1){
      ff->is_image=1;
    }else{
  
      char** ending_m=ics_endings;

      int counter=0;
      while(**ending_m!='.'){
        if(strcmp(*ending_m,ff->extension)==0){
          memcpy(ff->icon,ics_iconptr[counter],sizeof(int)*ICONSIZE);
          ff->loaded=1;
          free(fpf);
          return;
        }
        ending_m++;
        counter++;
      }
      memcpy(ff->icon,IFILE,sizeof(int)*ICONSIZE);
    }
  }else if( ff->is_dir == LINK_T ){

      
      ssize_t linkread_s=readlink(fpf,linkread,sizeof(linkread));

      if(linkread_s != -1 && ff->link == NULL){
        ff->link=malloc(linkread_s+(sizeof(char)));
        memcpy(ff->link,linkread,linkread_s);
        *(ff->link + linkread_s)=0;
      }

      DIR* tmp;
      if((tmp=opendir(fpf))!=NULL){
        closedir(tmp);
        ff->is_dir=DIR_T;
      }else{
        ff->is_dir=FILE_T;
      }
      memcpy(ff->icon,LINK,sizeof(int)*ICONSIZE);
  }else{

      memcpy(ff->icon,WAKARANAI,sizeof(int)*ICONSIZE);
  }
  ff->loaded=1;
  free(fpf);


}

void sort_file_structure(int start,int end,struct FileInfo* ff[]){
  
  struct FileInfo** ptrstrt=ff+start;
  struct FileInfo** ptrend=ff+end;

  for(struct FileInfo** tpass=ptrstrt; tpass < ptrend;tpass++){
    time_t highest_date=0;
    struct FileInfo** replaceptr=NULL;
    for(struct FileInfo** bpass=tpass; bpass < ptrend; bpass++){
      time_t extrime=(*bpass)->mtime;
      if(extrime > highest_date){
        highest_date=extrime;
        replaceptr=bpass;
      }

    }
    if(replaceptr!=NULL){
      struct FileInfo* tmp=*replaceptr;
      *replaceptr=*tpass;
      *tpass=tmp;
    }
  }

}

void init_file(struct FileInfo** ff,char* name,int is_dir,char* path){
  char* dname=file_last_prefix(name,'/');
  size_t cpsize=sizeof(char)*(strlen(dname)+1);
  char* fname=malloc(cpsize);
  memcpy(fname,dname,cpsize);
  char* ext=file_last_prefix(name,'.');
  process_file_name(dname,ext);

  str_lower(ext);

  int extp=strlen(path);
  int nml=strlen(name);
  char* full_path=malloc(sizeof(char)*(extp+nml+2));
  memcpy(full_path,path,sizeof(char)*extp);
  char* loc1=full_path+extp;
  *(loc1)='/';
  char* loc1p=loc1+1;
  memcpy(loc1p,name,sizeof(char)*nml);
  *(loc1p+nml)=0;

  struct stat dtm;
  int statusst=stat(full_path, &dtm);

  free(full_path);

  *ff=malloc(sizeof(struct FileInfo));
  (*ff)->name=fname;
  (*ff)->display=dname;
  (*ff)->extension=ext;
  (*ff)->is_dir=is_dir;
  (*ff)->loaded=-1;
  (*ff)->is_image=-1;
  (*ff)->link=NULL;

  if(statusst!=-1){
    (*ff)->mtime=dtm.st_mtime;
    (*ff)->fsize=dtm.st_size;
  }else{
    (*ff)->mtime=0;
    (*ff)->fsize=0;
  }

}

void display_file(struct FileInfo* ff,int x, int y, int selected){
  if(ff->loaded == -1)
    return;

  print_icon(x,y,ff->icon,selected,ff->display);


}

void free_file(struct FileInfo** ff){
  free((*ff)->extension);
  free((*ff)->display);
  free((*ff)->name);
  free((*ff)->link);
  free(*ff);
  *ff=NULL;
}

//testing method

/*

int main(int argn,char* argv[]){

  struct FileInfo* ff;

  init_file(&ff,argv[2],-1,argv[1]);
  load_file(ff,argv[1]);



  printf("\n");
  free_file(&ff);
   
  //draw_full_image(argv[1]);

  return 0;
}
*/
