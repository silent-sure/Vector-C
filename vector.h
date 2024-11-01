#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  void *ptr;
  size_t unit;
  int size, cap;
} Vector;
Vector * const Vector_MakeWithZero(size_t unit, int size) {
  Vector * const A = malloc(sizeof(Vector));
  A->unit = unit, A->size = size;
  if (!size) {
    size = 1;
  }
  A->cap = 1 << (__builtin_clz(1) + 1 - __builtin_clz(size));
  if ((size & (size - 1)) == 0) {
    A->cap >>= 1;
  }
  A->ptr = malloc(unit * A->cap);
  memset(A->ptr, 0, unit * A->size);
  return A;
}
Vector * const Vector_Make(size_t unit, int size, const void *p_val) {
  Vector * const A = malloc(sizeof(Vector));
  void *end;
  A->unit = unit, A->size = size;
  if (!size) {
    size = 1;
  }
  A->cap = 1 << (__builtin_clz(1) + 1 - __builtin_clz(size));
  if ((size & (size - 1)) == 0) {
    A->cap >>= 1;
  }
  A->ptr = malloc(unit * A->cap);
  end = A->ptr + unit*A->size;
  for (void * p = A->ptr; p < end; p += unit) {
    memcpy(p, p_val, unit);
  }
  return A;
}
Vector * const Vector_Copy(const Vector * const B) {
  Vector * const A = malloc(sizeof(Vector));
  A->unit = B->unit, A->size = B->size, A->cap = B->cap;
  A->ptr = malloc(B->unit * B->cap);
  memcpy(A->ptr, B->ptr, B->unit * B->size);
  return A;
}
void * const Vector_At(const Vector *A, int pos) {
  return A->ptr + A->unit*pos;
}
const void * Vector_Front(const Vector *A) { return A->ptr; }
const void * Vector_Back(const Vector *A) {
  return A->ptr + A->unit * (A->size - 1);
}
#define Vector_Delete(A) free((A)->ptr)
#define Vector_Clear(A) (void)((A)->size = 0)
#define Vector_Empty(A) !(A)->size
#define Vector_Size(A) (A)->size
#define Vector_Capacity(A) (A)->cap
void Vector_Reserve__(Vector * const A, int cap) {
  void * ptr = malloc(A->unit * cap);
  memcpy(ptr, A->ptr, A->unit * A->size);
  free(A->ptr);
  A->ptr = ptr, A->cap = cap;
}
void Vector_Reserve(Vector * const A, int cap) {
  if (cap > A->cap) {
    Vector_Reserve__(A, cap);
  }
}
void Vector_PushBack(Vector * const A, const void *p_val) {
  if (A->size == A->cap) {
    Vector_Reserve__(A, A->cap << 1);
  }
  memcpy(A->ptr + A->unit*A->size++, p_val, A->unit);
}
void Vector_PopBack(Vector * const A) { --A->size; }
void Vector_ResizeWithZero(Vector * const A, int size) {
  if (A->size < size) {
    if (A->cap < size) {
      int cap = 1 << (__builtin_clz(1) - __builtin_clz(size) + 1);
      if ((size & (size - 1)) == 0) {
        cap >>= 1;
      }
      Vector_Reserve__(A, cap);
    }
    memset(A->ptr + A->unit*A->size, 0, A->unit * (size - A->size));
  }
  A->size = size;
}
void Vector_Resize(Vector * const A, int size, const void *p_val) {
  if (A->size < size) {
    void *end;
    if (A->cap < size) {
      int cap = 1 << (__builtin_clz(1) - __builtin_clz(size) + 1);
      if ((size & -size) == size) {
        cap >>= 1;
      }
      Vector_Reserve__(A, cap);
    }
    end = A->ptr + A->unit*size;
    for (void * p = A->ptr + A->unit*A->size; p < end; p += A->unit) {
      memcpy(p, p_val, A->unit);
    }
  }
  A->size = size;
}
