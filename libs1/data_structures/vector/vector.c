#include <stdio.h>
#include <malloc.h>
#include "vector.h"

vector createVector(size_t n)
{
    int *data = (int*)malloc(sizeof(int) * n);
    if (data == NULL)
    {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    return (vector) {data, 0, n};
}
vector createVector1(size_t n) {
    vector v;

    // Выделяем память для элементов вектора.
    v.data = (int *)malloc(sizeof(int) * n);

    if (v.data == NULL) {
        // Обработка ошибки выделения памяти (например, можно вызвать exit(1)).
        // Здесь предполагается, что вы будете использовать функцию createVector в контексте,
        // где можно обработать ошибку.
        exit(1);
    }

    v.size = n;
    v.capacity = n; // Пусть вместимость равна размеру, вы можете изменить это по вашему усмотрению.

    return v;
}

void reserve(vector *v, size_t newCapacity)
{
    if (newCapacity > v->size)
    {
        v->data = malloc(sizeof(int) * newCapacity);
        if (v->data == NULL)
        {
            fprintf(stderr, "bad alloc");
            exit(1);
        }
        v->capacity = newCapacity;
    } else if (newCapacity < v->size || newCapacity == v->size)     //why ||
    {
        v->data = malloc(sizeof(int) * newCapacity);
        v->size = newCapacity;
        v->capacity = newCapacity;
    } else if (newCapacity == 0)
    {
        v->data = malloc(sizeof(NULL));
        v->data = NULL;
        v->size = 0;
        v->capacity = 0;
    }
}

void clear(vector *v)                           //верно ли?
{
    v->size = 0;
}

void shrinkToFit(vector *v)
{
    reserve(v, v->size);
}

void deleteVector(vector *v)
{
    if (v->data != NULL)
    {
        free(v->data);
        v->data = NULL;
    }
    v->size = 0;
    v->capacity = 0;
}

bool isEmpty(vector *v)
{
    return v->size == 0;
}

bool isFull(vector *v)
{
    return v->size == v->capacity && v->size > 0;
}

int getVectorValue(vector *v, size_t i)
{
    return v->data[i];
}

void pushBack(vector *v, int x)
{
    if (isFull(v))
    {
        reserve(v, v->capacity * 2);
        v->data[++v->size] = x;
        return;
    }

    if (v->capacity == 0)
    {
        reserve(v, 1);
        v->data[v->size++] = x;
        return;
    }

    v->data[v->size++] = x;
}

void popBack(vector *v)
{
    if (isEmpty(v))
    {
        fprintf(stderr, "vector is empty");
        exit(1);
    }
    v->size--;
}

int *atVector(vector *v, size_t index)
{
    if (v->size < index)
    {
        fprintf(stderr, "IndexError: a[%zu] is not exists", index);
        exit(1);
    }

    return &(v->data[index]);
}

int *back(vector *v)
{
    return &v->data[v->size - 1];
}

int *front(vector *v)
{
    return &v->data[0];
}