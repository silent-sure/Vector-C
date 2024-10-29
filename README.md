# Vector-C
*Under construction.*
A C implementation for C++'s ``std::vector``.
Variables and Functions:
```c
typedef struct {
  void *ptr;
  size_t unit;
  int size, capacity;
} Vector;

Vector * Vector_Make(size_t unit, int size, int val);
Vector * Vector_Copy(const Vector *other);
__inline__ void Vector_Delete(Vector *A);
__inline__ void * Vector_At(const Vector *A, int pos);
__inline__ void * Vector_Front(const Vector *A);
__inline__ void * Vector_Back(const Vector *A);
__inline__ int Vector_Empty(const Vector *A);
__inline__ int Vector_Size(const Vector *A);
__inline__ int Vector_Capacity(const Vector *A);
__inline__ void Vector_Reserve(Vector *A);
__inline__ void Vector_clear(Vector *A);
__inline__ void Vector_PushBack(Vector *A, const void *p_val);
__inline__ void Vector_PopBack(Vector *A);
__inline__ void Vector_Resize(Vector *A, int size);
__inline__ void Vector_Swap(Vector *A, Vector *B);
```
