/*
 *author: Evan Nikitin 2025 Jan17
*/
#include<stdlib.h>
#include<string.h>

char* unix_escaped(char* input){
  //not sure about this yet
  /*int len=(strlen(input)<<1)+1;
  char* ret=malloc(sizeof(char)*len);
  sprintf(ret,"%q",input);
  return ret;
  */
  return NULL;
}
char* char_escaped(char* input,char toesc){

  int len=0;
  for(char* cc=input;*cc!=0;cc++){
    if(*cc==toesc){
      len=len+2;
    }else{
      len++;
    }
  }
  char* nstring=malloc(sizeof(char)*(len+1));
  char* nstringptr=nstring;
  for(char* cc=input;*cc!=0;cc++){
    if(*cc==toesc){
      *nstringptr='\\';
      nstringptr++;
      *nstringptr=toesc;
      nstringptr++;
    }else{
      *nstringptr=*cc;
      nstringptr++;
    }
  }
  *nstringptr=0;
  return nstring;

}

void path_normalize(char* path){

  int len=strlen(path)-1;
  while(path[len]=='/'&&len>=0){
    path[len]=0;
    len--;
  }
 }


char* get_ps(char* input, char* with,char signal){
  int wlen=strlen(with);
  int nilen=0;

  int rep_count=0;

  char prev=0;
  for(char* ii=input;*ii!=0;ii++){
    if(prev=='%'&&*ii==signal){
      rep_count++;
    }else{
      nilen++;
    }
    prev=*ii;
  }

  nilen=nilen+wlen*rep_count;

  char* newdata=malloc(sizeof(char)*(nilen+2));

  char* ndp=newdata;

  prev=0;
  for(char* ii=input;*ii!=0;ii++){
    if(prev=='%'&&*ii==signal){
      *(ii-1)=' ';
      memcpy(ndp-1,with,sizeof(char)*(wlen));
      ndp=ndp+wlen-1;

    }else{
       *ndp=*ii;
        ndp++;
    }
    prev=*ii;
  }
  *ndp=0;
  return newdata;

}
