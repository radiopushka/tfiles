#include "png.c"
#include "ICONSIZE.h"



void avg_fx(unsigned char* matrix,unsigned char* matrix_bound,unsigned int x,unsigned int y,unsigned int spulge,unsigned int wmult1,int bytes,unsigned int* R, unsigned int* G, unsigned int* B){

  unsigned int xstart=x-(spulge>>1);
  unsigned int xend=x+(spulge>>1);

  *R=0;
  *G=0;
  *B=0;
  int hajimaru=1;

  unsigned char tr,tg,tb;


  for(unsigned int i =xstart;i<xend;i++){
    unsigned char* sptr=matrix+y*(wmult1)+i*bytes;
    if(sptr>=matrix){
      if(sptr>=matrix_bound)
        break;

      tr=*sptr;
      tg=*(sptr+1);
      tb=*(sptr+2);

      if(hajimaru==1){
        hajimaru=0;
        *R=tr;*G=tg;*B=tb;
      }else{

        *R=(*R+tr)>>1;*G=(*G+tg)>>1;*B=(*B+tb)>>1;
      }
    }
  }
     

}

void avg_fy(unsigned char* matrix,unsigned char* matrix_bound,unsigned int x,unsigned int y,unsigned int spulge,unsigned int wmult1,int bytes,unsigned int* R, unsigned int* G, unsigned int* B){

  unsigned int xstart=y-(spulge>>1);
  unsigned int xend=y+(spulge>>1);

  *R=0;
  *G=0;
  *B=0;

  unsigned char tr,tg,tb;
  int hajimaru=1;


  for(unsigned int i =xstart;i<xend;i++){
    unsigned char* sptr=matrix+i*(wmult1)+x*bytes;
    if(sptr>=matrix){
      if(sptr>=matrix_bound)
        break;

      tr=*sptr;
      tg=*(sptr+1);
      tb=*(sptr+2);

      if(hajimaru==1){
        hajimaru=0;
        *R=tr;*G=tg;*B=tb;
      }else{

        *R=(*R+tr)>>1;*G=(*G+tg)>>1;*B=(*B+tb)>>1;
      }
    }
  }
     

}

void brightener(int* icon,unsigned int size){
  
  int* ice=icon+size;
  int max_brightness=0;
  for(int* mi=icon;mi<ice;mi++){
    if(*mi>max_brightness){
      max_brightness=*mi;
    }
  }

  //if the image is all black just exit
  if(max_brightness==0)
    return;

  //image bright enough
  if(max_brightness>170){
    return;
  }

  int coeff=255/max_brightness;

  for(int* mi=icon;mi<ice;mi++){
    if(*mi!=0){
      *mi=(*mi)*coeff;
    }
  }

}


int get_image_icon(char* file,int* array_ptr){

  unsigned int width,height;
  int bytes;
  unsigned char* bstart;
  unsigned char* bend;
  int status=read_png_file(file,&width,&height,&bytes,&bstart,&bend); 
  if(status==-1){
    return -1;
  }

  for(int i=0;i<ICONSIZE;i++){
    array_ptr[i]=-1;
  }

  //pixel width: 7
  //pixel height: 4


  unsigned int aw=B_WIDTH-2;
  unsigned int ah=B_HEIGHT-2;

  unsigned int wmult1=width*bytes;
  unsigned int dwmult1=aw*3;
  unsigned int dhmult1=ah*dwmult1;

  
  if(aw==width && ah==height){
    int* aptr=array_ptr;
    for(unsigned char* hajii=bstart; hajii<bend;hajii=hajii+bytes){
        *aptr=*hajii;
        aptr++;
        *aptr=*(hajii+1);
        aptr++;
        *aptr=*(hajii+2);
        aptr++;


    }
  }else if( (width<aw && height==ah) || (width==aw && height<ah) || (width<aw && height<ah)){
    for(unsigned int y=0;y<ah;y++){
      if(y>=height)
        break;
      for(unsigned int x=0;x<aw;x++){
        if(x>=width)
          break;

        int* dptr=array_ptr+y*(dwmult1)+x*3;
  

        unsigned char* sptr=bstart+y*(wmult1)+x*bytes;

        *dptr=*sptr;
        *(dptr+1)=*(sptr+1);
        *(dptr+2)=*(sptr+2);
      }
    }
  }else{
    //image must be larger at this point
    unsigned int scalex=width/aw;
    unsigned int scaley=height/ah;

    unsigned int ys=0;
    for(unsigned int y=0;y<dhmult1;y=y+dwmult1){
      unsigned int xs=0;
      if(ys>=height)
        break;

      for(unsigned int x=0;x<dwmult1;x=x+3){
        if(xs>=width)
          break;

        int* dptr=array_ptr+y+x;
  
        unsigned int R,G,B,R1,G1,B1;

        avg_fx(bstart,bend,xs,ys,scalex,wmult1,bytes,&R, &G, &B);
        avg_fy(bstart,bend,xs,ys,scaley,wmult1,bytes,&R1, &G1, &B1);
        R=(R1+R)>>1;
        G=(G1+G)>>1;
        B=(B1+B)>>1;
        *dptr=R;
        *(dptr+1)=G;
        *(dptr+2)=B;
        xs=xs+scalex;
      }
      ys=ys+scaley;
    }
    brightener(array_ptr,ICONSIZE);
  }
 

 

  free(bstart);
  return 1;

}
