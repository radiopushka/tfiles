/*
 *author: Evan Nikitin 2025 Jan17th
 * */
#include "pngicon.c"

int draw_full_image(char* file){

  unsigned char* matrix;
  unsigned char* matrix_end;
  unsigned int width,height;
  int bytes;
  int status=read_png_file(file,&width,&height,&bytes,&matrix,&matrix_end);

  if(status==-1){
    return -1;
  }

  



  int twidth,theight;
  
  term_size(&twidth,&theight);

  theight=theight-2;

  unsigned int aw=twidth-2;
  unsigned int ah=theight-2;

  unsigned int wmult1=width*bytes;
  unsigned int dwmult1=aw*3;
  unsigned int dhmult1=ah*dwmult1;
        
  unsigned int R,G,B,R1,G1,B1;

  
  if(aw==width && ah==height){
    unsigned int y=2;
    mvmove(1,1);
    unsigned int rowcount=0;
    for(unsigned char* hajii=matrix; hajii<matrix_end;hajii=hajii+bytes){
      R=*hajii;
      G=*(hajii+1);
      B=*(hajii+2);
      fpixel(R,G,B);
      
      rowcount++;
      if(rowcount>width){
        y++;
        mvmove(1,y);
        rowcount=0;
      }

    }
  }else if( (width<aw && height==ah) || (width==aw && height<ah) || (width<aw && height<ah)){
    for(unsigned int y=0;y<ah;y++){
      if(y>=height)
        break;
      for(unsigned int x=0;x<aw;x++){
        if(x>=width)
          break;

  

        unsigned char* sptr=matrix+y*(wmult1)+x*bytes;
        mvmove(x+1,y+2);
        fpixel(*sptr,*(sptr+1),*(sptr+2));

      }
    }
  }else{
    int output_matrix[aw*ah*3];
    memset(output_matrix,0,sizeof(int)*(aw*ah*3));
    int* met=output_matrix+(aw*ah*3);
    //image must be larger at this point
    unsigned int scalex=width/aw+1;
    unsigned int scaley=height/ah+1;

    unsigned int ys=0;
    unsigned int xs=0;
    for(unsigned int y=0;y<dhmult1;y=y+dwmult1){
      xs=0;
      if(ys>=height)
        break;

      for(unsigned int x=0;x<dwmult1;x=x+3){
        if(xs>=width)
          break;

  

        int* dptr=output_matrix+y+x;
        avg_fx(matrix,matrix_end,xs,ys,scalex,wmult1,bytes,&R, &G, &B);
        avg_fy(matrix,matrix_end,xs,ys,scaley,wmult1,bytes,&R1, &G1, &B1);
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

    brightener(output_matrix,aw*ah*3);
    
    xs=0;
    ys=2;
    mvmove(1,ys);
    for(int* trace=output_matrix;trace<met;trace=trace+3){

    
      fpixel(*trace,*(trace+1),*(trace+2));
      xs++;
      if(xs>=aw){
        ys++;
        mvmove(1,ys);
        xs=0;
      }
    }
  }
 

 

 
  free(matrix);
  fclear();
  mvmove(1,theight+1);
  printf("\n");
  printf("%d pixels %dx%d terminal:%dx%d\n",width*height*3,width,height,twidth,theight);

  

  return 0;
  

}
