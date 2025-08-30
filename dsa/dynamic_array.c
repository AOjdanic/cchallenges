#include "dynamic_array.h"

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
