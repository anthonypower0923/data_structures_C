#include "dynamic_array.h"
#include <stdio.h>

void print_int(const void * element){
    // const int *value = element;
    printf("%d, ", *(const int *)element);
}

int main(void){
   DyArray *arr = dyarray_create(5,sizeof(int), print_int, NULL);
   int a = 9;
   int b = 89;
   int c = 24;
   Dya_Err_e e;
   int *ptr;
   e = dyarray_pop(arr, ptr);
   printf("%s",dyarray_error_handler(e));
   dyarray_push(arr, &a);
   dyarray_push(arr, &b);
   dyarray_push(arr, &c);
   dyarray_print_all(arr);
   dyarray_destroy(arr);
}
