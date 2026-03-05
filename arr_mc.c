#include "arr_mc.h"

int main() {
	int* arr = NULL; // Initialize array pointer
	arr_push(arr, 10); // Initialize array & push 10
	arr_push(arr, 20); // Push 20

	for (int i = 0; i < arr_count(arr); i++) {
		printf("%d\n", arr[i]); // arr[i] = *(arr+i)
	}
	arr_free(arr); // Free array after use
	return 0;
}
