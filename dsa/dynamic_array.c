#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dynamic_array {
  int size;
  int capacity;
  int *elements;
} DynamicArray;

void DynamicArray_shrink(DynamicArray *arr) {
  if (arr->size < arr->capacity / 4 && arr->capacity > 1) {
    int newCap = arr->capacity / 2;
    int *newP = realloc(arr->elements, newCap * sizeof(int));
    if (newP) {
      arr->elements = newP;
      arr->capacity = newCap;
    }
  }
}

DynamicArray *DynamicArray_initialize(int initialSize) {
  int size = initialSize ? initialSize : 1;

  int *p = calloc(size, sizeof(int));
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

bool DynamicArray_push(DynamicArray *arr, int el) {
  if (!arr || !arr->elements || arr->size > arr->capacity) {
    return false;
  }

  if (arr->capacity == 0) {
    arr->capacity = 1;
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

  return true;
}

bool DynamicArray_pop(DynamicArray *arr, int *result) {
  if (!arr || !arr->elements || !arr->size) {
    return false;
  }

  *result = arr->elements[arr->size - 1];
  arr->size--;

  DynamicArray_shrink(arr);

  return true;
}

bool DynamicArray_remove(DynamicArray *arr, int index, int *result) {
  if (!arr || !arr->elements || index < 0 || index >= arr->size) {
    return false;
  }

  if (index == arr->size - 1) {
    return DynamicArray_pop(arr, result);
  }

  *result = arr->elements[index];

  if (index < arr->size - 1) {
    memmove(&arr->elements[index], &arr->elements[index + 1],
            (arr->size - index - 1) * sizeof(int));
  }

  arr->size--;
  DynamicArray_shrink(arr);

  return true;
}

bool DynamicArray_get(DynamicArray *arr, int index, int *result) {
  if (!arr || !arr->elements || index < 0 || index >= arr->size) {
    return false;
  }

  *result = arr->elements[index];

  return true;
}

bool DynamicArray_set(DynamicArray *arr, int index, int value) {
  if (!arr || !arr->elements || index < 0 || index >= arr->size) {
    return false;
  }

  arr->elements[index] = value;

  return true;
}

int main() {
  DynamicArray *arr = DynamicArray_initialize(0);

  for (int i = 0; i < 9; i++) {
    DynamicArray_push(arr, i);
    int value;
    if (DynamicArray_get(arr, i, &value)) {
      printf("%d ", value);
    }
  }

  printf("\n");

  DynamicArray_set(arr, 2, 10);
  int poppedValue;
  if (DynamicArray_pop(arr, &poppedValue)) {
    printf("poppedValue: %d\n", poppedValue);
  }

  int removed;
  if (DynamicArray_remove(arr, 5, &removed)) {
    printf("removed: %d\n", removed);
  }

  for (int i = 0; i < arr->size; i++) {
    int value;
    if (DynamicArray_get(arr, i, &value)) {
      printf("%d ", value);
    }
  }

  DynamicArray_free(&arr);

  printf("\n");
}
