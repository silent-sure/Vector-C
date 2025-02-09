# Vector-C

A C implementation for C++'s ``std::vector``.

Variables, Functions, and Macros:
```c
typedef struct {
  void *ptr;
  size_t unit;
  int size, cap;
} Vector;

Vector * const Vector_MakeWithZero(size_t unit, int size);
Vector * const Vector_Make(size_t unit, int size, const void *p_val);
Vector * const Vector_Copy(const Vector * const B);
void * const Vector_At(const Vector *A, int pos);
const void * Vector_Front(const Vector *A);
const void * Vector_Back(const Vector *A);
void Vector_Reserve(Vector * const A, int cap);
void Vector_PushBack(Vector * const A, const void *p_val);
void Vector_PopBack(Vector * const A);
void Vector_ResizeWithZero(Vector * const A, int size);
void Vector_Resize(Vector * const A, int size, const void *p_val);

#define Vector_Delete(A) free((A)->ptr)
#define Vector_Clear(A) (void)((A)->size = 0)
#define Vector_Empty(A) !(A)->size
#define Vector_Size(A) (A)->size
#define Vector_Capacity(A) (A)->cap
```
