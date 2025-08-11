#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dynamic_array {
  int size;
  int capacity;
  void *elements;
  size_t elementSize;
} DynArr;

void DynArr_shrink(DynArr *arr) {
  if (arr->size < arr->capacity / 4 && arr->capacity > 1) {
    int newCap = arr->capacity / 2;
    void *newP = realloc(arr->elements, newCap * arr->elementSize);
    if (newP) {
      arr->elements = newP;
      arr->capacity = newCap;
    }
  }
}

DynArr *DynArr_init(size_t elementSize, int initialCapacity) {
  if (elementSize == 0) {
    return NULL;
  }

  int capacity = initialCapacity > 0 ? initialCapacity : 1;

  void *p = calloc(capacity, elementSize);
  if (!p) {
    return NULL;
  }

  DynArr *arr = malloc(sizeof(DynArr));

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

void DynArr_free(DynArr **arr) {
  if (!arr || !*arr) {
    return;
  }

  DynArr *tmp = *arr;

  free(tmp->elements);
  tmp->elements = NULL;

  free(tmp);
  *arr = NULL;
}

bool DynArr_push(DynArr *arr, void *el) {
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

bool DynArr_pop(DynArr *arr, void *out) {
  if (!arr || !arr->elements || !arr->size) {
    return false;
  }

  void *src = (char *)arr->elements + (arr->size - 1) * arr->elementSize;
  memcpy(out, src, arr->elementSize);
  arr->size--;

  DynArr_shrink(arr);

  return true;
}

bool DynArr_remove(DynArr *arr, int index, void *out) {
  if (!arr || !arr->elements || index < 0 || index >= arr->size) {
    return false;
  }

  if (index == arr->size - 1) {
    return DynArr_pop(arr, out);
  }

  void *src = (char *)arr->elements + index * arr->elementSize;
  memcpy(out, src, arr->elementSize);

  if (index < arr->size - 1) {
    void *dst = (char *)arr->elements + index * arr->elementSize;
    void *src = (char *)arr->elements + (index + 1) * arr->elementSize;
    memmove(dst, src, (arr->size - index - 1) * arr->elementSize);
  }

  arr->size--;
  DynArr_shrink(arr);

  return true;
}

bool DynArr_get(DynArr *arr, int index, void *out) {
  if (!arr || !arr->elements || index < 0 || index >= arr->size) {
    return false;
  }

  void *src = (char *)arr->elements + index * arr->elementSize;
  memcpy(out, src, arr->elementSize);

  return true;
}

bool DynArr_set(DynArr *arr, int index, void *value) {
  if (!arr || !arr->elements || index < 0 || index >= arr->size) {
    return false;
  }

  void *dest = (char *)arr->elements + index * arr->elementSize;
  memcpy(dest, value, arr->elementSize);

  return true;
}

int main() {
  DynArr *arr = DynArr_init(sizeof(int), 0);

  if (arr) {
    for (int i = 0; i < 9; i++) {
      DynArr_push(arr, &i);
      int value;
      if (DynArr_get(arr, i, &value)) {
        printf("%d ", value);
      }
    }

    printf("\n");

    int setter = 10;

    DynArr_set(arr, 2, &setter);
    int poppedValue;
    if (DynArr_pop(arr, &poppedValue)) {
      printf("poppedValue: %d\n", poppedValue);
    }

    int removed;
    if (DynArr_remove(arr, 5, &removed)) {
      printf("removed: %d\n", removed);
    }

    for (int i = 0; i < arr->size; i++) {
      int value;
      if (DynArr_get(arr, i, &value)) {
        printf("%d ", value);
      }
    }

    DynArr_free(&arr);

    printf("\n");
  }
}
