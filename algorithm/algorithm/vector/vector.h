#ifndef VECTOR_H
#define VECTOR_H

/**
 * @brief Represents a dynamic array.
 */
typedef struct Vector {
    int size; /**< The number of elements in the vector. */
    int capacity; /**< The maximum number of elements the vector can hold. */
    int *data; /**< Pointer to the underlying array. */
}Vector;

Vector* Create(int capacity);
void PushBack(Vector *vector, int value);
int PopBack(Vector *vector);
int Get(Vector *vector, int index);
/**
 * Sets the value at the specified index in the vector.
 *
 * @param vector The vector to modify.
 * @param index The index of the element to set.
 * @param data The new value to set at the specified index.
 */
void Set(Vector *vector, int index, int data);
void Clear(Vector *vector);
void Destroy(Vector *vector);
void Print(Vector *vector);

#endif // VECTOR_H