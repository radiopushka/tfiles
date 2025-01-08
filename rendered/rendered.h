#ifndef RENDER
#define RENDER



#include "image/ICONSIZE.h"
#include <time.h>

  struct FileInfo{
    int icon[ICONSIZE];
    char* display;
    char* extension;
    char* name;
    int loaded;
    int is_dir;
    int is_image;
    time_t mtime;
    size_t fsize;
  };


//file operations
char* str_append(char* before,char* after);
void load_file(struct FileInfo* ff,char* dirpath);
void init_file(struct FileInfo** ff,char* name,int is_dir,char* dir);
void display_file(struct FileInfo* ff,int x, int y, int selected);
void free_file(struct FileInfo** ff);
void sort_file_structure(int start,int end,struct FileInfo* ff[]);
char* get_default_cmd(struct FileInfo* ff);

char* file_last_prefix(char* path,char ident);
int draw_full_image(char* file);
void str_lower(char* input);


//curses_ operations


void mvmove(int x,int y);
void clear();
void refresh();
void nocurs();
void curs();
void cblink();
void fpixel(unsigned char r,unsigned char g,unsigned char b);
void fbg(unsigned char r,unsigned char g,unsigned char b);
void ffg(unsigned char r,unsigned char g,unsigned char b);
void fclear();
void term_size(int* width,int* height);
int wgetch();
void init_inputs();
void free_terminal();//allow other programs to use the current window



char* input_dialogue(char* title,char* precursor,int x,int y, int width);
void show_popup(char* text,int x,int y);
void show_large_popup(char* text,int x, int y);


#endif // !RENDER
