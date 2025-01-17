/*
 *author: Evan Nikitin 2025 Jan17th
 * */
#include <jpeglib.h>
#include <jerror.h>
#include<string.h>
#include<stdlib.h>
#include <setjmp.h>



//stuff written by the libjpeg people to deal with error handeling
struct local_jpeg_error_mgr {
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct local_jpeg_error_mgr *local_jpeg_error_ptr;

/*
 * Here's the routine that will replace the standard error_exit method:
 */

void jpeg_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  local_jpeg_error_ptr myerr = (local_jpeg_error_ptr) cinfo->err;

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}

//----


int read_jpg_file(char* file,unsigned int* width,unsigned int* height,int* bytes_per_pixel,unsigned char** buffer_pointer,unsigned char** buffer_end_pointer){
  //TODO
  FILE* f=fopen(file,"rb");
  
  struct jpeg_decompress_struct cinfo;
	struct local_jpeg_error_mgr jerr;

  //we already checked the file in the previous function and tested it for it to be a jpg
  //

  cinfo.err = jpeg_std_error( &jerr.pub );
  jerr.pub.error_exit = jpeg_error_exit;

  if (setjmp(jerr.setjmp_buffer)) {
    jpeg_destroy_decompress(&cinfo);
    fclose(f);
    return -1;
  }

	jpeg_create_decompress( &cinfo );

	jpeg_stdio_src( &cinfo, f);

	jpeg_read_header( &cinfo, TRUE );


	jpeg_start_decompress( &cinfo );

  *bytes_per_pixel=cinfo.num_components;
  *width=cinfo.output_width;
  *height=cinfo.output_height;

  //safety net for weird formats
  if(*bytes_per_pixel < 3){
    goto fail;
  }

  size_t msize=sizeof(char)*((*width)*(*height)*(*bytes_per_pixel));
  size_t lsize=sizeof(char)*((*width)*(*bytes_per_pixel));
  unsigned char* matrix=malloc(msize);
  unsigned char* matrix_end=matrix+msize;

  JSAMPROW row_pointer[1];
  row_pointer[0]=malloc(lsize);

  unsigned char* wrptr=matrix;
  for(int i=0;i<*height;i++){
    jpeg_read_scanlines(&cinfo,row_pointer,1);
    memcpy(wrptr,row_pointer[0],lsize);
    wrptr=wrptr+lsize;

  }

  jpeg_finish_decompress( &cinfo );
	jpeg_destroy_decompress( &cinfo );
	fclose( f);
  free(row_pointer[0]);

  *buffer_pointer=matrix;
  *buffer_end_pointer=matrix_end;

	return 1;

  fail:

  jpeg_finish_decompress( &cinfo );
	jpeg_destroy_decompress( &cinfo );
  fclose(f);

  return -1;
}
