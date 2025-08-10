#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dynamic_array {
  int size;
  int capacity;
  int *elements;
} DynamicArray;

DynamicArray *DynamicArray_initialize(int initialSize) {
  int size = initialSize ? initialSize : 1;

  int *p = malloc(size * sizeof(int));
  if (p == NULL) {
    return NULL;
  }

  DynamicArray *arr = malloc(sizeof(DynamicArray));

  if (arr == NULL) {
    free(p);
    return NULL;
  }

  arr->size = 0;
  arr->capacity = size;
  arr->elements = p;

  return arr;
}

void DynamicArray_free(DynamicArray **arr) {
  if (!arr || !*arr) {
    return;
  }

  DynamicArray *tmp = *arr;

  free(tmp->elements);
  tmp->elements = NULL;

  free(tmp);
  *arr = NULL;
}

DynamicArray *DynamicArray_push(DynamicArray *arr, int el) {
  if (!arr || !arr->elements) {
    return NULL;
  }

  if (arr->size == arr->capacity) {
    int *newP = realloc(arr->elements, arr->capacity * 2 * sizeof(int));
    if (newP == NULL) {
      return NULL;
    }

    arr->elements = newP;
    arr->capacity *= 2;
  }

  arr->elements[arr->size] = el;
  arr->size++;

  return arr;
}

int DynamicArray_pop(DynamicArray *arr) {
  if (!arr || !arr->elements || !arr->size) {
    return 0;
  }

  int temp = arr->elements[arr->size - 1];
  arr->size--;

  return temp;
}

int DynamicArray_remove(DynamicArray *arr, int index) {
  if (!arr || !arr->elements || index < 0 || index >= arr->size) {
    return 0;
  }
  int removed = arr->elements[index];

  if (index == arr->size - 1) {
    return DynamicArray_pop(arr);
  }

  if (index < arr->size - 1) {
    memmove(&arr->elements[index], &arr->elements[index + 1],
            (arr->size - index - 1) * sizeof(int));
  }

  arr->size--;

  return removed;
}

int *DynamicArray_get(DynamicArray *arr, int index) {
  if (!arr || !arr->elements || index < 0 || index >= arr->size) {
    return NULL;
  }

  return &arr->elements[index];
}

void DynamicArray_set(DynamicArray *arr, int index, int value) {
  if (!arr || !arr->elements || index < 0 || index >= arr->size) {
    return;
  }

  arr->elements[index] = value;
}

int main() {
  DynamicArray *arr = DynamicArray_initialize(0);

  for (int i = 0; i < 9; i++) {
    DynamicArray_push(arr, i);
    printf("%d ", *DynamicArray_get(arr, i));
  }

  printf("\n");

  DynamicArray_set(arr, 2, 10);
  DynamicArray_pop(arr);
  DynamicArray_remove(arr, 5);

  for (int i = 0; i < arr->size; i++) {
    printf("%d ", *DynamicArray_get(arr, i));
  }

  DynamicArray_free(&arr);

  printf("\n");
}

// improvements
// error handling
