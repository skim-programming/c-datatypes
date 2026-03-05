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

/* @brief Initialize array of type T
*  @param T* arr (ensure arr is NULL)
*  @example arr_mc.c
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

/* @brief Initialize array of type T with capacity c
*  @param T* arr, array ptr (ensure arr is NULL); size_t c, capacity
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

/* @brief Intialize array of type T if uninitialized; Push x to array
*  @param T* arr, array ptr; T x, value to be pushed
   @example arr_mc.c
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

/* @brief Free array
*  @param T* arr - array ptr
*  @example arr_mc.c
*/
#define arr_free(arr) free((Header*)(arr)-1)

/* @brief Get # of items in array
*  @param T* arr, array ptr
*  @example arr_mc.c
*/
#define arr_count(arr) ((Header*)(arr)-1)->count

/* @brief Get capacity of array
*  @param T* arr, array ptr
*/
#define arr_capacity(arr) ((Header*)(arr)-1)->capacity

/* @brief Pop back of array
*  @param T* arr, array ptr
*/
#define arr_pop(arr) if (arr_count(arr) > 0) arr[arr_count(arr)-1] = 0

/* @brief Get back of array
*  @param T* arr, array ptr
*/
#define arr_back(arr) arr[arr_count(arr)-1]

#endif
