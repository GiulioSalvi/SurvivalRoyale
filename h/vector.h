#include "consts.h"
#include "includes.h"

/// @brief Defines the minimum allocated memory for the vector. If data_type is char, this is 2B of data.
#define MIN_CAPACITY 2
/// @brief Defines the maximum allocable memory for the vector. If data_type is char, this is 2KiB of data.
#define MAX_CAPACITY 2048
/// @brief Defines the multiplicative coefficient for which the vector has to be resized.
#define RESIZE_COEFFICIENT 2

typedef char data_type;

typedef struct vector {
    size_t size;
    size_t capacity;
    data_type* data;
} vector;

vector* buildVector();
void freeVector(vector* const vector);
void resize(vector* const vector, const size_t newCapacity);
void pushBack(vector* const vector, const data_type element);
data_type popBack(vector* const vector);
void pushFront(vector* const vector, const data_type element);
data_type popFront(vector* const vector);
data_type at(vector* vector, size_t index);