#include "config.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void str_mk(char** dest,char* input){
  int len = strlen(input);
  *dest = malloc(len+1);
  memcpy(*dest,input,len+1);
} 

char* char_append(char* before,char after){
  if(before == NULL){
    
    
  char* out=malloc(sizeof(char)*(2));
  out[0] = after;
  out[1] = 0;

    return out;
  }
  int bl=strlen(before);
  char* out=malloc(sizeof(char)*(bl+2));
  memcpy(out,before,sizeof(char)*(bl));
  out[bl]=after;
  out[bl+1]=0;
  return out;
}

int read_section(FILE* f, CfgRaster* rwappend){

  int val=0;
  int status = 0;
  char* section_name = NULL;
  char* key = NULL;
  char* value = NULL;
  while( (val = fgetc(f)) != EOF){
   if(val == '[' && status != 3){
      free(section_name);
      section_name = NULL;
      status = 1;
    }else if( val == ']' && status != 3){
    
      status = 2;  
    }else if( val == '='  && status != 3){
      status = 3;
    }else if( val == '\n' && status == 3){
      CfgRaster element = malloc(sizeof(struct configuration_raster));
      element -> extpt = NULL;
      element -> key = key;
      key = NULL;
      element -> value = value;
      value = NULL;
      str_mk(&element->section,section_name);
      element -> next = *rwappend;
      *rwappend = element;
      status = 2;
    }else if( status == 1 && val!='\n'){


        char* novo = char_append(section_name,val);
        free(section_name);
        section_name = novo;
    }else if(status == 2 && val != '\n'){

        char* novo = char_append(key,val);
        free(key);
        key = novo;
    }else if(status == 3 && val != '\n'){
        char* novo = char_append(value,val);
        free(value);
        value = novo;
        

    }


  }
  free(section_name);
  free(key);
  free(value);
  return 1;
}
CfgRaster read_cfg_file(char* file){
  FILE* f = fopen(file,"r");
  if(!f)
    return NULL;

  //begin reading file section by section
  CfgRaster head = NULL;

  read_section(f, &head);
  fclose(f);
  return head;

}

void debug_cfg_print(CfgRaster raster){

  while(raster !=NULL){


    printf("section: %s key: %s value: %s\n",raster->section,raster->key,raster->value);
    raster = raster -> next;
  }

}

void free_cfg_mem(CfgRaster raster){
  while(raster != NULL){

    free(raster->section);
    free(raster->key);
    free(raster->value);
    free(raster->extpt);
    CfgRaster tsugi = raster->next;
    free(raster);
    raster = tsugi;
  }
}

char* get_value_by(CfgRaster raster,char* section, char* key){
   while(raster !=NULL){

    if(strcmp(raster -> section,section)==0 && strcmp(raster -> key,key)==0){
      return raster->value;
    }


    raster = raster -> next;
  }
  return NULL;
}

CfgRaster get_raster_by(CfgRaster raster,char* section, char* key){
  while(raster !=NULL){


    if(strcmp(raster -> section,section)==0 && strcmp(raster -> key,key)==0){
      return raster;
    }

    raster = raster -> next;
  }
  return NULL;

}

int put_value_by(CfgRaster* rasteri,char* section, char* key,char* value){
    
CfgRaster raster = *rasteri;

   while(raster !=NULL){

    if(strcmp(raster -> section,section)==0 && strcmp(raster -> key,key)==0){
      free(raster -> value);
      str_mk(&raster->value,value);
      return 1;
    }


    raster = raster -> next;
  }

  CfgRaster element = malloc(sizeof(struct configuration_raster));
  str_mk(&element->value,value);
  str_mk(&element->key,key);
  str_mk(&element->section,section);
  element ->extpt = NULL;
  element->next = *rasteri;
  *rasteri=element;
  return 2;


}

CfgRaster new_raster(void){
  return NULL;
}

//writing to file
int write_cfg_file(CfgRaster raster, char* path){
  FILE* f = fopen(path,"w");
  if(!f)
    return -1;


  char* section=NULL;

  while(raster !=NULL){
    if(section == NULL || strcmp(section,raster -> section) != 0){
      section = raster -> section;
      fprintf(f,"[%s]\n",section);
    }
    fprintf(f,"%s=%s\n",raster->key,raster->value);
    raster = raster -> next;
  }
  fclose(f);
  return 1;
}


//array stuff
//
int* string_to_array(char* string, int* size_o){
  int* output_array = NULL;
  int size=0;
  char number[15];
  memset(number,0,15);
  int itt=0;
  while(1 == 1){
    
    if(*string == ' ' || *string == 0){
      if(itt != 0){
        int* narray = malloc(sizeof(int)*(size + 1));
        if(output_array != NULL){
          memcpy(narray,output_array,sizeof(int)*size);
          free(output_array);
        }
        narray[size] = atoi(number);
        output_array = narray;
        itt = 0;
        memset(number,0,15);
        size++;
      }
      if(*string == 0)
        break;
    }else{
      number[itt]=*string;
      itt++;
    }
    string++;
  }
  *size_o = size;
  return output_array;
}

char* array_to_string(int* array, int size){

  char* string = NULL;

  char number[15];
  int* endptr=array+size;
  for(;array<endptr;array++){
    sprintf(number,"%d ",*array);
    for(int i=0;i<strlen(number);i++){
      char* nst=char_append(string,number[i]);
      free(string);
      string = nst;
    }
  }
  return string;
}
