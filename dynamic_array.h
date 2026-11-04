#pragma once
#include <stddef.h>

typedef struct DyArray DyArray;
typedef void (* DyArrayPrinter) (const void * element);
typedef void (* DyArrayDestructor) (const void * element);

typedef enum {
    DYA_ERR_OK = 0,
    DYA_ERR_BASE_ALLOC,
    DYA_ERR_EXPAND_ALLOC,
    DYA_ERR_NULL_ARG,
    DYA_ERR_INDEX_OUT_OF_BOUNDS
} Dya_Err_e;

DyArray *dyarray_create(size_t cap,size_t d_size, DyArrayPrinter printer, DyArrayDestructor destructor);
size_t dyarray_size(const DyArray * arr);
size_t dyarray_capacity(const DyArray * arr);
Dya_Err_e dyarray_get(const DyArray *arr,size_t index, void *out_element);
Dya_Err_e dyarray_set(const DyArray *arr,size_t index, const void * element);
Dya_Err_e dyarray_remove(DyArray *arr, size_t index, void *out_element);
Dya_Err_e dyarray_pop(DyArray *arr,void *out_element);
Dya_Err_e dyarray_push(DyArray *arr,const void *element);
Dya_Err_e dyarray_print_all(const DyArray *arr);
Dya_Err_e dyarray_destroy(DyArray *arr);
char * dyarray_error_handler(Dya_Err_e error);
