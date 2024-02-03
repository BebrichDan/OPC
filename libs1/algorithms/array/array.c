#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include "array.h"
#include "C:/Users/bob/CLionProjects/cource/libs/base/base.h"

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int getMinIndex(const int *arr, size_t n) {
    if (n == 0) {                           // Обработка случая пустого массива
        return -1;
    }

    int minElement = arr[0];
    int minIndex = 0;

    for (size_t i = 1; i < n; ++i) {
        if (arr[i] < minElement) {
            minElement = arr[i];
            minIndex = i;
        }
    }

    return minIndex;
}
int getMaxIndex(const int *arr, size_t n) {
    if (n == 0) {                           // Обработка случая пустого массива
        return -1;
    }

    int maxElement = arr[0];
    int maxIndex = 0;

    for (int i = 1; i < n; ++i) {
        if (arr[i] > maxElement) {
            maxElement = arr[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}

void inputArray_(int *const a, const size_t n) {
    for (size_t i = 0; i < n; i++)
        scanf("%d", &a[i]);
}

void outputArray_(const int *const a, const size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void append_(int *const a, size_t *const n, const int value) {
    a[*n] = value;
    (*n)++;
}

void insert_(int *const a, size_t *const n, const size_t pos, const int value) {
    assert(pos < *n);
    if (*n != 0) {
        size_t lowBound = (pos == 0) ? SIZE_MAX : pos;
        (*n)++;
        for (size_t i = *n; i != lowBound; i--)
            a[i] = a[i - 1];
        a[pos] = value;
    } else {
        (*n)++;
        a[pos] = value;
    }
}

void deleteByPosSaveOrder_(int *a, size_t *n, const size_t pos) {
    for (size_t i = pos; i < *n - 1; i++)
        a[i] = a[i + 1];
    (*n)--;
}

void deleteByPosUnsaveOrder_(int *a, size_t *n, size_t pos) {
    a[pos] = a[*n - 1];
    (*n)--;
}

size_t linearSearch_(const int *a, const size_t n, int x) {
    for (size_t i = 0; i < n; i++)
        if (a[i] == x)
            return i;
    return n;
}

int any_(const int *a, size_t n, int (*predicate)(int)) {
    for (size_t i = 0; i < n; i++)
        if (predicate(a[i]))
            return 1;
    return 0;
}

int all_(const int *a, size_t n, int (*predicate)(int)) {
    for (size_t i = 0; i < n; i++)
        if (!predicate(a[i]))
            return 0;
    return 1;
}

int countIf_(const int *const a, const size_t n, int (*predicate)(int)) {
    int count = 0;
    for (size_t i = 0; i < n; i++)
        count += predicate(a[i]);
    return count;
}

void deleteIf_(int *const a, size_t *const n, int (*deletePredicate)(int)) {
    size_t iRead = 0;
    while (iRead < *n && !deletePredicate(a[iRead]))
        iRead++;
    size_t iWrite = iRead;
    while (iRead < *n) {
        if (!deletePredicate(a[iRead])) {
            a[iWrite] = a[iRead];
            iWrite++;
        }
        iRead++;
    }
    *n = iWrite;
}

void forEach_(const int *source, int *dest, const size_t n, const int (*predicate)(int)) {
    for (size_t i = 0; i < n; i++)
        dest[i] = predicate(source[i]);
}

size_t binarySearch_(const int *a, size_t n, int x) {
    size_t left = 0;
    size_t right = n - 1;
    while (left <= right) {
        size_t middle = left + (right - left) / 2;
        if (a[middle] < x)
            left = middle + 1;
        else if (a[middle] > x)
            right = middle - 1;
        else
            return middle;
    }
    return n;
}

size_t binarySearchMoreOrEqual_(const int *a, size_t n, int x) {
    if (a[0] >= x)
        return 0;
    size_t left = 0;
    size_t right = n;
    while (right - left > 1) {
        size_t middle = left + (right - left) / 2;
        if (a[middle] < x)
            left = middle;
        else
            right = middle;
    }
    return right;
}

static void selectionSort(int *unsortedPart, int nUnsorted) {
    if (nUnsorted == 1) // массив из одного элемента является упорядоченным и так
        return;
    else {
        int minElementIndex = getMinIndex(unsortedPart, nUnsorted);
        swap(&unsortedPart[0], &unsortedPart[minElementIndex]);
        selectionSort(unsortedPart + 1, nUnsorted - 1);
    }
}

int split(int *a, int left, int right, int x) {
    int iWrite = left;
    for (int iRead = left; iRead < right - 1; iRead++) {
        if (a[iRead] < x) {
            swap(&a[iRead], &a[iWrite]);
            iWrite++;
        }
    }
    return iWrite;
}

void quickSort(int *a, int left, int right) {
    if (right - left <= 1) {
        return;
    } else {

        int x = a[rand() % (right - left) + left];

        int middle = split(a, left, right, x);

        quickSort(a, left, middle);
        quickSort(a, middle, right);
    }
}