#pragma once
#include <stddef.h>

typedef struct DyArray DyArray;
typedef void (* DyArrayPrinter) (const void * element);
typedef void (* DyArrayDestructor) (const void * element);

DyArray *dyarray_create(size_t cap,size_t d_size, DyArrayPrinter printer, DyArrayDestructor destructor);
size_t dyarray_size(const DyArray * arr);
size_t dyarray_capacity(const DyArray * arr);
void dyarray_get(const DyArray *arr,size_t index, void *out_element);
void dyarray_set(const DyArray *arr,size_t index, const void * element);
void dyarray_remove(DyArray *arr, size_t index, void *out_element);
void dyarray_pop(DyArray *arr,void *out_element);
void dyarray_push(DyArray *arr,const void *element);
void dyarray_print_all(const DyArray *arr);
void dyarray_destroy(DyArray *arr);
