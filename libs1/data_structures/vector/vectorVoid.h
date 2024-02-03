#ifndef INC_VECTORVOID_H
#define INC_VECTORVOID_H

#include <limits.h>
#include <stdbool.h>

typedef struct vectorVoid {
    void *data;          // указатель на нулевой элемент вектора
    size_t size;         // размер вектора вместимость вектора
    size_t capacity;     // размер базового например, если вектор хранит int -
    size_t baseTypeSize; // то поле baseTypeSize = sizeof(int)
    // если вектор хранит float -
    // то поле baseTypeSize = sizeof(float)
} vectorVoid;

//создает вектор размером n и типом sizeof(type)
vectorVoid createVectorV(size_t n, size_t baseTypeSize);

//изменяет количество памяти, выделенное под хранение элементов вектора
void reserveV(vectorVoid *v, size_t newCapacity);

//освобождает память, выделенную под неиспользуемые элементы
void shrinkToFitV(vectorVoid *v);

//удаляет элементы из контейнера, но не освобождает выделенную память
void clearV(vectorVoid *v);

//освобождает память, выделенную вектору
void deleteVectorV(vectorVoid *v);

//является ли вектор пустым
bool isEmptyV(vectorVoid *v);

//является ли вектор полным
bool isFullV(vectorVoid *v);

//записывает по адресу destination index-ый элемент вектора v
void getVectorValueV(vectorVoid *v, size_t index, void *destination);

//записывает на index-ый элемент вектора v значение, расположенное по адресу source
void setVectorValueV(vectorVoid *v, size_t index, void *source);

#endif