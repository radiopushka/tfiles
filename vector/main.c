/*
 *author: Evan Nikitin 2025 Jan17th
 this implementation of a vector tries to take advantage of spatial locality
 * */

#include <stdlib.h>
#include "vector.h"
#include<stdio.h>
#include<string.h>


Vector create_vector(){
  Vector vec=malloc(sizeof(struct Vector));
  vec->data=NULL;
  vec->locations=NULL;
  vec->sizes=NULL;
  vec->size=0;
  vec->mem=0;
  vec->locsize=0;
  return vec;
}

//size in bytes
void add_element(Vector vec,void* data,size_t size){

  size_t new_mem_size=vec->mem+size;
  char* nvec=malloc(new_mem_size);
  memcpy(nvec,vec->data,vec->mem);
  memcpy(nvec+vec->mem,data,size);

  size_t new_loc_size=vec->locsize+sizeof(size_t);
  size_t* newloc=malloc(new_loc_size);
  memcpy(newloc,vec->locations,vec->locsize);

  newloc[vec->size]=vec->mem;
  unsigned int nsize=vec->size+1;

  size_t* nsizes=malloc(new_loc_size);
  memcpy(nsizes,vec->sizes,vec->locsize);
  nsizes[vec->size]=size;

  free(vec->sizes);
  vec->sizes=nsizes;

  vec->size=nsize;
  vec->mem=new_mem_size;
  vec->locsize=new_loc_size;

  free(vec->locations);
  vec->locations=newloc;

  free(vec->data);
  vec->data=nvec;
  

}

void* element_at(Vector vec,int index){
  size_t pseudo=vec->locations[index];
  return (vec->data)+pseudo;
}

size_t size_at(Vector vec, int index){
  return vec->sizes[index];
}

unsigned int get_vec_size(Vector vec){
  return vec->size;
}


void print_vector(Vector vec){
  char* data=vec->data;

  for(unsigned int i=0;i<vec->mem;i++){
    if(data[i]==0){
      printf("0");
    }else{
      printf("%c",data[i]);
    }
  }
  printf("\n");
}

void free_vector(Vector vec){

  free(vec->locations);
  free(vec->data);
  free(vec->sizes);
  free(vec);
}

char* vector_as_string(Vector vec){
  char* dstr=malloc(vec->mem+1);
  memcpy(dstr,vec->data,vec->mem);
  char* dstrend=dstr+vec->mem;
  char* tt;
  for(tt=dstr;tt<dstrend;tt++){
    if(*tt==0){
      *tt='\n';
    }
  }
  *tt=0;
  return dstr;
}

void delete_element(Vector vec, int index){

  size_t sizev=size_at(vec,index);
  printf("%lu\n",sizev);
  size_t newmemsize=vec->mem-sizev;
  
  char* start=vec->data;
  char* nvec = malloc(newmemsize);
  size_t pseudo=vec->locations[index];
  
  memcpy(nvec,start,pseudo);

  size_t tail=newmemsize-pseudo;
  memcpy(nvec+pseudo,start+pseudo+sizev,tail);
  //now all the data has been inserted
  //
  size_t fsize=index*sizeof(size_t);
  
  size_t new_loc_size=vec->locsize-sizeof(size_t);
  size_t fcpy=vec->locsize-sizeof(size_t)-fsize;
  size_t* newloc=malloc(new_loc_size);
  memcpy(newloc,vec->locations,fsize);
  //memcpy(newloc+fsize,vec->locations+fsize+sizeof(size_t),fcpy);

  size_t* hajime_2=newloc+index;
  size_t* hajime=vec->locations+index+1;
  size_t* kure=vec->locations+vec->size;
  for(size_t* it=hajime;it<kure;it++){
    *hajime_2=*it-sizev;
    hajime_2++;
  }

  size_t* nsizes=malloc(new_loc_size);
  memcpy(nsizes,vec->sizes,fsize);
  memcpy(nsizes+index,vec->sizes+index+1,fcpy);

 
  free(vec->sizes);
  vec->sizes=nsizes;

  free(vec->locations);
  vec->locations=newloc;

  free(vec->data);
  vec->data=nvec;

  vec->mem=newmemsize;
  vec->size=vec->size-1;
  vec->locsize=new_loc_size;





}
/*
int main(){
  Vector vec=create_vector();
  char* str1="apples";
  char* str2="oranges";
  char* str3="grapes";
  add_element(vec,str1,strlen(str1)+1);
  add_element(vec,str2,strlen(str2)+1);
  add_element(vec,str3,strlen(str3)+1);

  
  printf("%s\n",(char*)element_at(vec,0));
  printf("%s\n",(char*)element_at(vec,1));
  printf("%s\n\n",(char*)element_at(vec,2));
  
  delete_element(vec,2);
  printf("%s\n",(char*)element_at(vec,0));
  printf("%s\n\n",(char*)element_at(vec,1));
  delete_element(vec,1);
  printf("%s\n",(char*)element_at(vec,0));
  delete_element(vec,0);

  free_vector(vec);

}
*/
