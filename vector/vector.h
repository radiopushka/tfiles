/*
 *author: Evan Nikitin 2025 Jan17th
 * */
#ifndef VECTOR
#define VECTOR

struct Vector{
  char* data;
  size_t* locations;
  size_t* sizes;
  unsigned int size;
  size_t mem;
  size_t locsize;
};

//--
typedef struct Vector* Vector;

Vector create_vector();


void add_element(Vector vec,void* data,size_t size);
void* element_at(Vector vec,int index);
size_t size_at(Vector vec, int index);
unsigned int get_vec_size(Vector vec);
void free_vector(Vector vec);

char* vector_as_string(Vector vec);

#endif // !VECTOR
