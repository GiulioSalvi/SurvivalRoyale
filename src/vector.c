#include "../h/vector.h"
#include "../h/includes.h"

vector* buildVector() {
    vector* v = (vector*)malloc(sizeof(vector));

    if(v == NULL) {
        free(v);
        exit(EXIT_ALLOC_FAILURE);
    }
    
    v->size = 0;
    v->capacity = MIN_CAPACITY;
    v->data = (data_type*)malloc(MIN_CAPACITY*sizeof(data_type));

    if(v->data == NULL) {
        free(v);
        exit(EXIT_ALLOC_FAILURE);
    }

    return v;
}

void freeVector(vector* const vector) {
    free(vector->data);
    free(vector);
}

void resize(vector* const vector, const size_t newCapacity) {
    data_type* newDataBuffer = (data_type*)malloc(newCapacity*sizeof(data_type));
    if(newDataBuffer == NULL) {
        freeVector(vector);
        exit(EXIT_ALLOC_FAILURE);
    }

    for(size_t i = 0; i < vector->size; i++)
        newDataBuffer[i] = vector->data[i];

    free(vector->data);
    vector->data = newDataBuffer;
    vector->capacity = newCapacity;
}

void pushBack(vector* const vector, const data_type element) {
    if(vector->size == vector->capacity)
        resize(vector, RESIZE_COEFFICIENT*vector->capacity);
    
    vector->data[vector->size++] = element;
}

data_type popBack(vector* const vector) {
    if(vector->size == 0) {
        freeVector(vector);
        exit(EXIT_POP_FAILURE);
    }
    
    data_type rs = vector->data[vector->size-- - 1];
    if(vector->size <= vector->capacity/RESIZE_COEFFICIENT)
        resize(vector, vector->capacity/RESIZE_COEFFICIENT);

    return rs;
}

void pushFront(vector* const vector, const data_type element) {
    if(vector->size == vector->capacity)
        resize(vector, RESIZE_COEFFICIENT*vector->capacity);
    
    for(size_t i = 0; i < vector->size - 1; i++)
        vector->data[i + 1] = vector->data[i];
    
    vector->data[0] = element;
    vector->size++;
}

data_type popFront(vector* const vector) {
    if(vector->size == 0) {
        freeVector(vector);
        exit(EXIT_POP_FAILURE);
    }
    
    data_type rs = vector->data[0];
    for(size_t i = 0; i < vector->size - 1; i++)
        vector->data[i] = vector->data[i + 1];
    vector->size--;

    if(vector->size <= vector->capacity/RESIZE_COEFFICIENT)
        resize(vector, vector->capacity/RESIZE_COEFFICIENT);

    return rs;
}

data_type at(vector* vector, size_t index) {
    if(index >= vector->size)
        exit(EXIT_FAILURE);
    
    return vector->data[index];
}