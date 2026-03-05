#ifndef ARR_MC_H
#define ARR_MC_H
#include <stdlib.h> // malloc, realloc
#include <stdio.h> // printf

// Macro implementation of dynamic array

typedef struct {
	size_t count;
	size_t capacity;
} Header; // ~16 bytes

#define INIT_CAPACITY 1000

/* Initialize array of type T
* Params: T* arr (ensure arr is NULL)
*/
#define arr_init(arr) \
do{\
	if(arr == NULL){\
		Header* h = malloc(sizeof(*arr) * INIT_CAPACITY + sizeof(Header));\
		if(!h){printf("Error: Failed to allocate"); exit(1);}\
		h->count = 0; h->capacity = INIT_CAPACITY;\
		arr = (void*)(h+1);\
	}\
} while(0)

/* Initialize array of type T with capacity c
* Params: T* arr, array ptr (ensure arr is NULL); size_t c, capacity
*/
#define arr_init_c(arr, c) \
do{\
	if(arr == NULL){\
		Header* h = malloc(sizeof(*arr) * c + sizeof(Header));\
		if(!h){printf("Error: Failed to allocate"); exit(1);}\
		h->count = 0; h->capacity = c;\
		arr = (void*)(h+1);\
	}\
} while(0)

/* 1. Intialize array of type T if uninitialized; 2. Push x to array
* Params: T* arr, array ptr; T x, value to be pushed
*/
#define arr_push(arr, x)	\
do {\
	Header* h = NULL;\
	if (arr == NULL) {	\
			h = malloc(sizeof(*arr) * INIT_CAPACITY + sizeof(Header)); \
			if (!h) { printf("Error: Failed to allocate"); exit(1); }\
				h->count = 0; h->capacity = INIT_CAPACITY; \
				arr = (void*)(h + 1); \
	}\
	h = (Header*)(arr)-1;\
	if(h->count >= h->capacity){\
		size_t new_cap = h->capacity * 2; Header* temp = h;\
		temp = realloc(h, new_cap);\
		if(!temp) {printf("Error: Failed to reallocate"); exit(1);}\
		temp->capacity = new_cap; h = temp;\
		arr = (void*)(h+1);\
	}\
	arr[h->count++] = x;\
} while (0)

/* Free array
* Params: T* arr, array ptr
*/
#define arr_free(arr) free((Header*)(arr)-1)

/* Get # of items in array
* Params: T* arr, array ptr
*/
#define arr_count(arr) ((Header*)(arr)-1)->count

/* Get capacity of array
* Params: T* arr, array ptr
*/
#define arr_capacity(arr) ((Header*)(arr)-1)->capacity

#endif
