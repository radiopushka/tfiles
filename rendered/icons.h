/*
 *author: Evan Nikitin 2025 Jan17th
 * */
#include "curses/curses.c"
#include "../IMAGE_SUPPORT.h"


#ifndef NO_IMAGE_SUPPORT
  #include "image/fullscaled.c"
#endif // !NO_IMAGE_SUPPORT
#ifdef NO_IMAGE_SUPPORT
  #include "image/ICONSIZE.h"
#endif // DEBUG

#ifndef ICONS
#define ICONS

//default icon size: width:16, height:7 pixels
//
  int DOC[]={33,129,191,52,133,193,65,137,194,75,140,196,82,143,197,88,145,198,92,147,198,96,149,199,94,148,199,92,147,198,86,144,197,80,142,196,70,138,195,62,136,194,48,132,192,28,128,191,45,131,192,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,33,129,191,48,132,192,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,105,153,201,109,155,202,108,154,202,103,152,200,96,149,199,89,145,198,-1,-1,-1,-1,-1,-1,-1,-1,-1,39,130,192,48,132,192,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,39,130,192,45,131,192,-1,-1,-1,72,139,195,82,143,197,90,146,198,97,149,199,105,153,201,107,154,201,106,153,201,101,151,200,96,149,199,89,145,198,78,141,196,68,138,195,-1,-1,-1,39,130,192,45,131,192,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,33,129,191,35,129,191,52,133,193,65,137,194,72,139,195,82,143,197,89,145,198,92,147,198,94,148,199,92,147,198,90,146,198,84,144,197,78,141,196,70,138,195,59,135,194,48,132,192,28,128,191,};

  int ARCH[]={75,149,195,81,151,196,91,155,198,100,158,199,106,161,201,112,164,202,115,165,203,119,167,204,119,167,204,115,165,203,112,164,202,106,161,201,100,158,199,91,155,198,81,151,196,75,149,195,75,149,195,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,125,170,205,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,75,149,195,75,149,195,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,130,173,207,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,75,149,195,78,150,195,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,134,174,207,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,78,150,195,75,149,195,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,127,171,206,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,75,149,195,75,149,195,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,75,149,195,75,149,195,78,150,195,89,154,197,96,156,199,104,160,200,108,162,201,112,164,202,115,165,203,115,165,203,112,164,202,108,162,201,104,160,200,96,156,199,89,154,197,78,150,195,75,149,195,};

  int IMAGE[]={111,163,202,113,164,202,112,164,202,111,163,202,109,162,201,107,161,201,105,160,200,103,159,200,100,158,199,98,158,199,96,157,199,93,155,198,90,154,198,88,154,197,85,153,197,82,151,196,112,164,202,215,255,92,215,255,90,187,221,243,186,221,243,185,221,243,184,220,243,184,220,243,183,220,243,183,219,243,182,219,243,181,219,243,181,219,243,180,218,242,179,218,242,83,152,196,112,163,202,215,255,90,187,221,243,186,221,243,186,221,243,185,220,243,184,220,243,114,119,74,112,117,71,183,219,243,182,219,243,181,219,243,181,219,242,180,218,242,179,218,242,82,151,196,110,163,202,186,221,243,186,221,243,120,124,85,119,123,82,185,220,243,116,120,77,114,118,74,112,116,70,110,115,66,182,219,243,181,219,243,181,219,242,180,218,242,179,218,242,82,151,196,108,162,201,186,221,243,119,123,83,84,128,82,117,121,80,116,120,78,115,119,75,113,117,72,111,116,68,109,114,65,108,112,61,181,219,243,104,109,52,102,107,46,99,105,40,82,151,196,106,161,201,117,121,80,82,127,80,81,126,79,79,125,78,115,119,75,113,118,73,112,116,70,69,121,67,66,119,63,107,111,59,105,110,54,103,108,50,48,113,45,42,111,38,81,151,196,104,160,200,104,160,200,104,160,200,104,160,200,103,159,200,102,159,200,100,158,199,99,158,199,96,157,199,95,156,198,92,155,198,90,154,198,88,153,197,85,153,197,82,151,196,80,151,196,};

  int PDF[]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,81,151,196,91,155,198,101,159,200,-1,-1,-1,-1,-1,-1,120,168,204,124,169,205,125,170,205,122,168,204,-1,-1,-1,-1,-1,-1,105,160,200,96,157,199,86,153,197,-1,-1,-1,-1,-1,-1,84,152,196,-1,-1,-1,103,160,200,-1,-1,-1,-1,-1,-1,-1,-1,-1,130,173,207,-1,-1,-1,127,171,206,-1,-1,-1,-1,-1,-1,107,161,201,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,84,152,196,96,157,199,105,160,200,-1,-1,-1,-1,-1,-1,-1,-1,-1,133,174,207,-1,-1,-1,130,173,207,-1,-1,-1,-1,-1,-1,107,161,201,99,158,199,89,154,197,-1,-1,-1,-1,-1,-1,84,152,196,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,131,173,207,-1,-1,-1,127,171,206,-1,-1,-1,-1,-1,-1,107,161,201,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,81,151,196,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,120,168,204,124,169,205,126,170,205,122,169,204,-1,-1,-1,-1,-1,-1,105,160,200,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,};

  int VIDEO[]={-1,-1,-1,-1,-1,-1,80,151,196,89,154,197,95,156,198,101,158,199,104,159,199,106,160,200,106,160,199,103,159,199,99,157,198,93,155,197,87,153,197,80,151,196,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,85,152,196,-1,-1,-1,99,157,198,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,99,157,198,-1,-1,-1,82,151,196,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,87,153,196,96,156,198,103,159,199,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,101,158,199,93,155,197,85,152,196,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,89,154,197,-1,-1,-1,105,160,199,110,162,200,116,165,201,122,167,203,122,167,203,116,164,201,110,162,200,103,159,199,-1,-1,-1,87,153,197,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,87,153,197,96,156,198,103,159,199,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,101,158,199,93,155,197,84,152,196,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,85,152,196,-1,-1,-1,99,157,198,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,99,157,198,-1,-1,-1,83,151,196,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,80,151,196,89,154,197,95,156,198,101,158,199,105,160,199,106,160,200,106,160,200,103,159,199,99,157,198,93,155,197,87,153,197,80,151,196,-1,-1,-1,-1,-1,-1,};

  int AUDIO[]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,101,159,200,104,160,200,106,161,201,107,161,201,106,161,201,103,160,200,99,158,199,96,157,199,91,155,198,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,103,160,200,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,92,155,198,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,103,160,200,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,92,155,198,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,89,154,197,95,156,198,99,158,199,103,160,200,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,105,161,200,101,159,200,97,157,199,92,155,198,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,87,153,197,92,155,198,97,157,199,101,159,200,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,102,159,200,99,158,199,96,157,199,91,155,198,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,};

  int IFOLDER[]={-1,-1,-1,-1,-1,-1,0,98,142,0,121,167,1,123,167,1,123,167,1,118,167,1,114,166,0,89,141,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,71,143,184,73,147,185,76,152,186,80,156,188,83,162,189,85,166,189,87,168,190,89,170,191,89,170,191,87,168,190,85,164,190,82,160,189,80,157,187,76,151,186,74,147,185,70,142,183,72,144,184,75,150,186,77,153,187,80,158,188,84,163,188,87,168,190,90,171,191,92,175,192,92,175,192,90,171,191,87,168,190,84,163,189,81,158,188,77,153,186,74,149,186,71,144,184,71,145,185,74,149,186,78,154,187,81,160,188,85,164,189,88,169,190,91,174,192,95,179,193,94,179,193,91,174,192,88,169,190,85,164,189,81,159,188,77,153,187,74,149,185,71,143,184,72,144,184,75,150,186,79,154,186,81,159,188,85,164,190,87,169,191,90,173,191,93,176,192,93,176,192,91,172,191,87,168,190,84,163,189,80,158,187,78,153,186,74,148,186,71,143,184,71,143,184,74,148,185,77,153,186,81,158,188,83,162,188,86,166,190,89,171,191,89,171,191,90,172,191,88,169,191,86,165,189,83,162,188,79,157,187,76,152,186,73,147,185,70,143,184,70,142,184,74,146,185,76,151,186,79,155,187,82,159,188,84,163,189,85,166,190,87,167,190,86,166,190,85,165,190,83,163,189,81,159,188,78,154,187,75,151,186,72,146,185,69,141,183};


  int IFILE[]={161,161,161,170,170,170,182,181,182,190,190,190,200,199,199,208,208,208,214,214,214,217,217,217,217,217,217,211,211,211,205,205,205,193,193,193,163,163,164,111,111,111,-1,-1,-1,-1,-1,-1,164,164,164,176,176,175,188,188,187,196,196,197,191,191,191,199,199,199,206,206,206,210,210,209,229,229,229,223,223,223,214,214,214,202,203,202,194,194,194,182,182,182,128,128,128,-1,-1,-1,167,167,167,165,165,165,108,108,108,69,69,69,118,118,118,122,123,122,127,126,127,129,129,129,69,69,69,69,69,69,69,69,69,208,208,208,196,197,197,184,185,185,173,173,173,102,102,102,167,167,167,178,178,178,191,190,191,206,205,205,217,217,217,229,228,228,240,240,241,252,252,252,246,246,246,235,235,234,223,223,223,211,211,211,199,199,199,188,188,187,176,176,176,143,143,143,167,167,167,178,179,179,190,190,190,202,202,203,214,214,214,226,226,226,237,238,237,244,244,243,240,241,240,232,231,231,220,220,220,208,208,208,197,196,197,185,184,185,173,173,173,159,158,159,165,164,164,161,162,162,107,107,106,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,205,206,205,194,193,194,182,182,182,173,173,173,161,161,161,161,161,162,172,173,173,185,185,185,193,194,193,202,203,203,211,211,211,217,217,217,220,220,219,220,220,220,214,214,214,208,208,209,199,199,199,190,190,190,179,179,178,167,167,167,155,155,155};
  
  int WAKARANAI[]={161,161,161,170,170,170,182,181,182,190,190,190,200,199,199,208,208,208,214,214,214,217,217,217,217,217,217,211,211,211,205,205,205,193,193,193,163,163,164,111,111,111,-1,-1,-1,-1,-1,-1,164,164,164,176,176,175,188,188,187,196,196,197,191,191,191,199,199,199,206,206,206,210,210,209,229,229,229,223,223,223,214,214,214,202,203,202,194,194,194,182,182,182,128,128,128,-1,-1,-1,167,167,167,165,165,165,108,108,108,69,69,69,118,118,118,122,123,122,127,126,127,129,129,129,69,69,69,69,69,69,69,69,69,208,208,208,196,197,197,184,185,185,173,173,173,102,102,102,167,167,167,178,178,178,191,190,191,206,205,205,217,217,217,229,228,228,240,240,241,252,252,252,246,246,246,235,235,234,223,223,223,211,211,211,199,199,199,188,188,187,176,176,176,143,143,143,167,167,167,178,179,179,190,190,190,202,202,203,214,214,214,226,226,226,237,238,237,244,244,243,240,241,240,232,231,231,220,220,220,208,208,208,197,196,197,185,184,185,173,173,173,159,158,159,165,164,164,161,162,162,107,107,106,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,205,206,205,194,193,194,182,182,182,173,173,173,161,161,161,161,161,162,172,173,173,185,185,185,193,194,193,202,203,203,211,211,211,217,217,217,220,220,219,220,220,220,214,214,214,208,208,209,199,199,199,190,190,190,179,179,178,167,167,167,155,155,155};
  
  int LINK[]={-1,-1,-1,-1,-1,-1,85,165,216,85,165,216,85,165,216,85,165,216,85,165,216,85,165,216,85,165,216,28,128,191,28,128,191,28,128,191,28,128,191,28,128,191,-1,-1,-1,-1,-1,-1,-1,-1,-1,85,165,216,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,128,191,-1,-1,-1,-1,-1,-1,85,165,216,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,128,191,-1,-1,-1,85,165,216,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,128,191,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,85,165,216,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,128,191,85,165,216,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,128,191,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,85,165,216,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,128,191,85,165,216,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,128,191,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,85,165,216,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,128,191,-1,-1,-1,85,165,216,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,128,191,-1,-1,-1,-1,-1,-1,85,165,216,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,128,191,-1,-1,-1,-1,-1,-1,-1,-1,-1,85,165,216,85,165,216,85,165,216,85,165,216,28,128,191,28,128,191,28,128,191,28,128,191,28,128,191,28,128,191,28,128,191,28,128,191,-1,-1,-1,-1,-1,-1,};

 
  int EMPTY[ICONSIZE];



//mimetype map

char* ics_endings[]={
  "wav","ogg","mp3",
  "mp4","mkv","mov","av","webm",
  "jpg","jpeg","png","svg","webp","gif",
  "pdf",
  "tar","zip","gunzip","gzip","xz","gz",
  "doc","docx","odt"
    ,"."};
int* ics_iconptr[ICONSIZE]={
  AUDIO,AUDIO,AUDIO,
  VIDEO,VIDEO,VIDEO,VIDEO,VIDEO,
  IMAGE,IMAGE,IMAGE,IMAGE,IMAGE,IMAGE,
  PDF,
  ARCH,ARCH,ARCH,ARCH,ARCH,ARCH,
  DOC,DOC,DOC
};

//end mimetype map
//
//default command mimetype
char gazou[]="mpv \"%f\" --speed=0.01 --loop"; //picture
char gif[]="mpv \"%f\" --loop"; //gif
char douga[]="mpv \"%f\""; //video
char oto[]="mpv \"%f\" --no-video"; //sound
char pdf[]="xpdf \"%f\" &"; //pdf
char doc[]="libreoffice \"%f\" &"; //documents
char edit[]="nvim \"%f\""; //editor

char* m_endings[]={
  "jpg","jpeg","png","svg","webp",
  "gif",
  "mp4","mov","mkv","av","webm",
  "mp3","wav","ogg",
  "pdf",
  "odt","docx","doc","pptx","ppt","csv",
  "c","txt","h","cpp","hpp","c++","php","html","java","xml","json","config","conf",
  "."};
char* m_cmd[]={
  gazou,gazou,gazou,gazou,gazou,
  gif,
  douga,douga,douga,douga,douga,
  oto,oto,oto,
  pdf,
  doc,doc,doc,doc,doc,doc,
  edit,edit,edit,edit,edit,edit,edit,edit,edit,edit,edit,edit,edit
};




unsigned char BR=255;
unsigned char BG=255;
unsigned char BB=255;

unsigned char BRs=102;
unsigned char BGs=255;
unsigned char BBs=102;

void icon_set_border(unsigned char R,unsigned char G, unsigned char B){
  BR=R;
  BG=G;
  BB=B;
}




  void print_pad_n(int size){
      for(int i2=0; i2 < size;i2++){
        fputc(' ',stdout);
      }

  }

void set_colors(int inverse){
     if(inverse==0){
        fbg(~BR,~BG,~BB);
        ffg(BR,BG,BB);
      }else if(inverse>1){
        fbg(BRs,BGs,BBs);
        ffg(~BRs,~BGs,BBs);
      }else{
        fbg(BR,BG,BB);
        ffg(~BR,~BG,~BB);
      }

}

  void print_pad(int size,int inverse){
     
      set_colors(inverse);
      print_pad_n(size);
      fclear();

  }


  void print_icon(int x, int y, int* icon,int border,char* captioni){
    char* caption=(char*)captioni;
    fclear();
    int trk=0;

         

     mvmove(x,y);
     print_pad(B_WIDTH,border);
     y++;
    

    mvmove(x,y);
    print_pad(1,border);



      

    const int size=(B_WIDTH)-2;
    const int csize=size-1;


    for(int* i=icon; i < icon+ICONSIZE; i=i+3){


      if(*i != -1){
       fbg(*i,*(i+1),*(i+2));
      }else{
        set_colors(border);
      }
      fputc(' ',stdout);

      trk++;
      if(trk>csize){
        y++;
        trk=0;
        print_pad(1,border);
        mvmove(x,y);
        print_pad(1,border);

      }
    }

    if(caption!=NULL){
      char l1[size+1];
      char l2[size+1];
      memset(l1,0,sizeof(char)*(size+1));
      memset(l2,0,sizeof(char)*(size+1));

      int brk=0;
      for(int i=0;i<size;i++){
        if(captioni[i]==0){
          brk=1;
          break;
        }
        l1[i]=captioni[i];
      }
      if(brk==0){
        for(int i=0;i<size;i++){
          if(captioni[i+size]==0){
            break;
          }
          l2[i]=captioni[i+size];
        }

      }
      fclear();
      mvmove(x,y);
    
      set_colors(border);
      int xshift=1;

      print_pad_n(B_WIDTH);
      mvmove(x+xshift,y);
      fputs(l1,stdout);
      mvmove(x,y+1);
      print_pad_n(B_WIDTH);
      mvmove(x+xshift,y+1);
      fputs(l2,stdout);




    }

      /*print_pad(B_WIDTH,border);
      mvmove(x,y+1);
      print_pad(B_WIDTH,border);
      */
    


  }

//demo
void file_icon(int x, int y, char* file){
#ifndef NO_IMAGE_SUPPORT
   if(get_image_icon(file,EMPTY) != -1){
      print_icon(x,y,EMPTY,0,NULL);
      return;
   }

#endif // !NO_IMAGE_SUPPORT
  print_icon(x,y,IFILE,0,NULL);
}


#endif // !ICONS
