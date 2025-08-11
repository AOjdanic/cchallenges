#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dynamic_array {
  int size;
  int capacity;
  void *elements;
  size_t elementSize;
} DynamicArray;

void DynamicArray_shrink(DynamicArray *arr) {
  if (arr->size < arr->capacity / 4 && arr->capacity > 1) {
    int newCap = arr->capacity / 2;
    void *newP = realloc(arr->elements, newCap * arr->elementSize);
    if (newP) {
      arr->elements = newP;
      arr->capacity = newCap;
    }
  }
}

DynamicArray *DynamicArray_initialize(size_t elementSize, int initialCapacity) {
  if (elementSize == 0) {
    return NULL;
  }

  int capacity = initialCapacity > 0 ? initialCapacity : 1;

  void *p = calloc(capacity, elementSize);
  if (!p) {
    return NULL;
  }

  DynamicArray *arr = malloc(sizeof(DynamicArray));

  if (!arr) {
    free(p);
    return NULL;
  }

  arr->size = 0;
  arr->elements = p;
  arr->capacity = capacity;
  arr->elementSize = elementSize;

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

bool DynamicArray_push(DynamicArray *arr, void *el) {
  if (!arr || !arr->elements) {
    return false;
  }

  if (arr->size == arr->capacity) {
    void *newP = realloc(arr->elements, arr->capacity * 2 * arr->elementSize);
    if (!newP) {
      return false;
    }

    arr->elements = newP;
    arr->capacity *= 2;
  }

  void *dest = (char *)arr->elements + arr->size * arr->elementSize;
  memcpy(dest, el, arr->elementSize);
  arr->size++;

  return true;
}

bool DynamicArray_pop(DynamicArray *arr, void *out) {
  if (!arr || !arr->elements || !arr->size) {
    return false;
  }

  void *src = (char *)arr->elements + (arr->size - 1) * arr->elementSize;
  memcpy(out, src, arr->elementSize);
  arr->size--;

  DynamicArray_shrink(arr);

  return true;
}

bool DynamicArray_remove(DynamicArray *arr, int index, void *out) {
  if (!arr || !arr->elements || index < 0 || index >= arr->size) {
    return false;
  }

  if (index == arr->size - 1) {
    return DynamicArray_pop(arr, out);
  }

  void *src = (char *)arr->elements + index * arr->elementSize;
  memcpy(out, src, arr->elementSize);

  if (index < arr->size - 1) {
    void *dst = (char *)arr->elements + index * arr->elementSize;
    void *src = (char *)arr->elements + (index + 1) * arr->elementSize;
    memmove(dst, src, (arr->size - index - 1) * arr->elementSize);
  }

  arr->size--;
  DynamicArray_shrink(arr);

  return true;
}

bool DynamicArray_get(DynamicArray *arr, int index, void *out) {
  if (!arr || !arr->elements || index < 0 || index >= arr->size) {
    return false;
  }

  void *src = (char *)arr->elements + index * arr->elementSize;
  memcpy(out, src, arr->elementSize);

  return true;
}

bool DynamicArray_set(DynamicArray *arr, int index, void *value) {
  if (!arr || !arr->elements || index < 0 || index >= arr->size) {
    return false;
  }

  void *dest = (char *)arr->elements + index * arr->elementSize;
  memcpy(dest, value, arr->elementSize);

  return true;
}

int main() {
  DynamicArray *arr = DynamicArray_initialize(sizeof(int), 0);

  if (arr) {
    for (int i = 0; i < 9; i++) {
      DynamicArray_push(arr, &i);
      int value;
      if (DynamicArray_get(arr, i, &value)) {
        printf("%d ", value);
      }
    }

    printf("\n");

    int setter = 10;

    DynamicArray_set(arr, 2, &setter);
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
}
