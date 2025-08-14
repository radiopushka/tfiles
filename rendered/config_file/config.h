#ifndef CONFIG_FILE
#define CONFIG_FILE

struct configuration_raster{
  struct configuration_raster* next;
  char* section;
  char* key;
  char* value;
  int* extpt;
};

typedef struct configuration_raster* CfgRaster;

CfgRaster read_cfg_file(char* path);
int write_cfg_file(CfgRaster raster, char* path);

//do not free the pointer this returns, free mem will free it
char* get_value_by(CfgRaster raster, char* section, char* key);
CfgRaster get_raster_by(CfgRaster raster, char* section, char* key);
int put_value_by(CfgRaster* raster, char* section,char* key, char* value);

void free_cfg_mem(CfgRaster raster);
CfgRaster new_raster(void);

void debug_cfg_print(CfgRaster raster);

//string parsing
int* string_to_array(char* string,int* size_o);
char* array_to_string(int* array, int size);

#endif // !CONFIG_FILE
       //
/*
 * File syntax:
 * [section]
 * key=value
 * key=value
 * key=value
 * ...
 * [section]
 * key=value
 * ..
 */
