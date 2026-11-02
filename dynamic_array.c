#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dynamic_array.h"
#define DEFAULT_CAPACITY 5

struct DyArray{
    size_t capacity;
    size_t size;
    void * data;
    size_t d_size;
    DyArrayPrinter printer;
    DyArrayDestructor destructor;
};

void dyarray_resize(DyArray *arr);

DyArray *dyarray_create(size_t cap,size_t d_size, DyArrayPrinter printer, DyArrayDestructor destructor){
    if(cap == 0){
        return NULL;
    }
    DyArray *arr = malloc(sizeof(* arr));
    if(arr == NULL){
        return NULL;
    }
    arr->capacity = cap;
    arr->size = 0;
    arr->d_size = d_size;
    arr->printer = printer;
    arr->destructor = destructor;
    arr->data = NULL;

    arr->data = malloc(arr->capacity * arr->d_size);
    if(arr->data == NULL){
        free(arr);
        return NULL;
    }
    return arr;
}

size_t dyarray_size(const DyArray * arr){
    if(arr == NULL){
        return 0;
    }
    return arr->size;
    }

size_t dyarray_capacity(const DyArray * arr){
    if(arr == NULL){
        return 0;
    }
    return arr->capacity;
}

void dyarray_resize(DyArray *arr){
    if(arr == NULL){
        return;
    }
    size_t new_capacity = (arr->capacity == 0) ? DEFAULT_CAPACITY : arr->capacity * 2;
    void * new_data = realloc(arr->data, new_capacity * arr->d_size);
    if(new_data == NULL){
        return;
    }
    arr->data = new_data;
    arr->capacity = new_capacity;
    return;
}

void dyarray_get(const DyArray *arr,size_t index, void *out_element){
    if(arr == NULL || out_element == NULL){
        return;
    }
    if(index >= arr->size){
        return;
    }
    const void * source = (const char *)arr->data + (index * arr->d_size);
    memcpy(out_element, source, arr->d_size);
    return;
}

void dyarray_set(const DyArray *arr,size_t index, const void * element){
    if(arr == NULL || element == NULL){
        return;
    }
    if(index >= arr->size){
        return;
    }
    void * destination = (char *)arr->data + (index * arr->d_size);
    if(arr->destructor != NULL){
        arr->destructor(destination);
    }
    memcpy(destination, element, arr->d_size);
    return;
}

void dyarray_remove(DyArray *arr, size_t index, void *out_element){
    if(arr == NULL){
        return;
    }
    if(index >= arr->size){
        return;
    }
    void * source = arr->data + (index * arr->d_size);
    if(out_element){
        memcpy(out_element,source, arr->d_size);
    }
    else if(arr->destructor != NULL){
        arr->destructor(source);
    }
    size_t elements_to_move = arr->size - index - 1;
    if(elements_to_move > 0){
        void * destination = arr->data + ((index + 1) * arr->d_size);
        memmove(source, destination, arr->d_size * elements_to_move);
    }
    arr->size--;
    return;
}

void dyarray_pop(DyArray *arr,void *out_element){
    if(arr == NULL || out_element == NULL || arr->size == 0){
        return;
    }
    size_t index = arr->size - 1;
    void * source = (char *)arr->data + (index * arr->d_size);
    memcpy(out_element, source, arr->d_size);
    arr->size--;
    return;
}

void dyarray_push(DyArray *arr,const void *element){
    if(arr == NULL || element == NULL){
        return;
    }
    if(arr->size >= arr->capacity){
        dyarray_resize(arr);
    }
    void * destination = (char *)arr->data + (arr->size * arr->d_size);
    memcpy(destination, element, arr->d_size);
    arr->size++;
    return;
}

void dyarray_print_all(const DyArray *arr){
    if(arr == NULL || arr->printer == NULL){
        return;
    }
    for(size_t i = 0;i<arr->size;i++){
        const void * element = arr->data + (i * arr->d_size);
        arr->printer(element);
        printf("\n");
    }
    return;
}

void dyarray_destroy(DyArray *arr){
    if(arr == NULL){
        return;
    }
    if(arr->destructor != NULL){
        char *data = arr->data;
        for(size_t i = 0;i<arr->size;i++){
            void * element = data + (i * arr->d_size);
            arr->destructor(element);
        }
    }
    free(arr->data);
    free(arr);
}
