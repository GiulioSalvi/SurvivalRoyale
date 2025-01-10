#include "consts.h"
#include "includes.h"

#ifndef _VECTOR_H_
    /// @brief Include guard.
    #define _VECTOR_H_

    /// @brief Defines the minimum allocated memory for the vector. If data_type is char, this is 2B of data.
    #define MIN_CAPACITY 2
    /// @brief Defines the maximum allocable memory for the vector. If data_type is char, this is 2KiB of data.
    #define MAX_CAPACITY 2048
    /// @brief Defines the multiplicative coefficient for which the vector has to be resized.
    #define RESIZE_COEFFICIENT 2

    /// @brief The type of data wrapped in the vector structure. For convenience char has been choosen so it can wrap, by casting, any other primitive data type.
    typedef char data_type;

    /// @brief The vector structure.
    typedef struct vector {
        /// @brief Field for determining the amount of elements actually stored in memory.
        size_t size;
        /// @brief Field for determining the amount of possible elements that can be stored in memory without resizing the vector.
        size_t capacity;
        /// @brief Contiguous memory segment with in data is stored.
        data_type* data;
    } vector;

    /// @brief Builds a vector structure initializing its fields. If vector's allocation or data's block allocation fails, it exits with EXIT_ALLOC_FAILED exit code.
    /// @return A vector structure.
    vector* buildVector();
    /// @brief Frees the memory used from the vector structure.
    /// @param vector The vector to be free.
    void freeVector(vector* const vector);
    /// @brief Resizes the capacity of the vector with the new capacity specified. If vector's data's block allocation fails, it exits with EXIT_ALLOC_FAILED exit code.
    /// @param vector The vector that has to be resized.
    /// @param newCapacity The new capacity of the vector.
    void resize(vector* const vector, const size_t newCapacity);
    /// @brief Pushes an element at the back of the vector.
    /// @param vector The vector into the element has to be pushed. If necessary, the vector is resized automatically.
    /// @param element The element to be pushed.
    void pushBack(vector* const vector, const data_type element);
    /// @brief Pops the element at the back of the vector. If necessary, the vector is resized automatically. If the vector is empty, it exits with EXIT_POP_FAILURE exit code.
    /// @param vector The vector from which the element is poped.
    /// @return Returns the element at the back of the vector.
    data_type popBack(vector* const vector);
    /// @brief Pushes an element at the front of the vector. If necessary, the vector is resized automatically.
    /// @param vector The vector into the element has to be pushed.
    /// @param element The element to be pushed.
    void pushFront(vector* const vector, const data_type element);
    /// @brief Pops the element at the back of the vector. If necessary, the vector is resized automatically. If the vector is empty, it exits with EXIT_POP_FAILURE exit code.
    /// @param vector The vector from which the element is poped.
    /// @return Returns the element at the front of the vector.
    data_type popFront(vector* const vector);
    /// @brief Access at the element in the given index of the vector. If the index is greater or equal to the vector's size, it exits with EXIT_ILLEGAL_INDEX_FAILURE exit code.
    /// @param vector The vector.
    /// @param index The index to access to.
    /// @return The element at the index position in the vector.
    data_type at(vector* vector, size_t index);
#endif