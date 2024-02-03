#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "algorithm.h"
#include "C:/Users/bob/CLionProjects/cource/libs/algorithms/array/array.h"


static void unordered_array_set_shrinkToFit(unordered_array_set *a) {
    if (a->size != a->capacity) {
        a->data = (int *) realloc(a->data, sizeof(int) * a->size);
        a->capacity = a->size;
    }
}

unordered_array_set unordered_array_set_create(size_t capacity) {
    return (unordered_array_set) {malloc(sizeof(int) * capacity), 0, capacity};
}

unordered_array_set unordered_array_set_create_from_array(const int *a, size_t size) {
    unordered_array_set set = unordered_array_set_create(size);
    for (size_t i = 0; i < size; i++)
        unordered_array_set_insert(&set, a[i]);
    unordered_array_set_shrinkToFit(&set);
    return set;
}

size_t unordered_array_set_in(unordered_array_set set, int value) {
    return linearSearch_(set.data, set.size, value);
}

bool unordered_array_set_isSubset(unordered_array_set subset, unordered_array_set set) {
    size_t count = 0;
    for (size_t i = 0; i < subset.size; i++) {
        if (linearSearch_(set.data, set.size, subset.data[i]) < set.size)
            count++;
    }
    if (count == subset.size)
        return 1;

    return 0;
}

bool unordered_array_set_isEqual(unordered_array_set set1, unordered_array_set set2) {
    return (unordered_array_set_union(set1, set2)).size == set1.size;
}

void unordered_array_set_isAbleAppend(unordered_array_set *set) {
    assert(set->size < set->capacity);
}

void unordered_array_set_insert(unordered_array_set *set, int value) {
    if (linearSearch_(set->data, set->size, value) == set->size)
        append_(set->data, (size_t *) set->size, (int)set->size);
}

void unordered_array_set_deleteElement(unordered_array_set *set, int value) {
    size_t position = linearSearch_(set->data, set->size, value);
    if (position <= set->size)
        return deleteByPosSaveOrder_(set->data, (size_t *) set->size, position);
}

unordered_array_set unordered_array_set_union(unordered_array_set set1, unordered_array_set set2) {

    unordered_array_set res = unordered_array_set_create(set1.size+set2.size);

    size_t count = 0;
    for(size_t i=0; i<set1.size; i++, count++)
        insert_(res.data, &res.size, i, set1.data[i]);
    count++;

    for(size_t i=0; i<set2.size; i++)
        unordered_array_set_insert(&res, set2.data[count+i]);

    return res;
}
unordered_array_set unordered_array_set_intersection(unordered_array_set set1, unordered_array_set set2)
{
    unordered_array_set res = unordered_array_set_create(set1.size);

    for(size_t i = 0; i<set1.size; i++)
    {
        if(linearSearch_(set2.data, set2.size, set1.data[i]) < set2.size)
            append_(res.data, &res.size, set1.data[i]);
    }

    return res;
}
unordered_array_set unordered_array_set_difference (unordered_array_set set1 , unordered_array_set set2)
{
    unordered_array_set res = unordered_array_set_create(set1.size);

    for(size_t i = 0; i<set1.size; i++)
    {
        if(unordered_array_set_in(set2, set1.data[i]) == set2.size)
            append_(res.data, &res.size, set1.data[i]);
    }

    return res;
}
unordered_array_set unordered_array_set_complement (unordered_array_set set , unordered_array_set universumSet)
{
    unordered_array_set res = unordered_array_set_create(universumSet.size);

    assert(unordered_array_set_intersection(set, universumSet).size == set.size);

    for(size_t i = 0; i<universumSet.size; i++)
    {
        if(linearSearch_(set.data, set.size, universumSet.data[i]) == set.size)
            append_(res.data, &res.size, universumSet.data[i]);
    }

    return res;
}
unordered_array_set unordered_array_set_symmetricDifference (unordered_array_set set1 , unordered_array_set set2)
{
    unordered_array_set res = unordered_array_set_create(set1.size+set2.size);


    for(size_t i = 0; i<set1.size; i++)
    {
        if(linearSearch_(set2.data, set2.size, set1.data[i]) == set2.size)
            append_(res.data, &res.size, set1.data[i]);
    }

    for(size_t i = 0; i<set2.size; i++)
    {
        if(linearSearch_(set1.data, set1.size, set2.data[i]) == set1.size)
            append_(res.data, &res.size, set2.data[i]);
    }

    return res;
}
void unordered_array_set_print ( unordered_array_set set )
{
    puts("Set.data");
    outputArray_(set.data, set.size);

    printf("Current number of items: %zu", set.size);

    printf("The capacity of the set: %zu", set.capacity);
}
void unordered_array_set_delete ( unordered_array_set set )
{
    free(set.data);
}





ordered_array_set ordered_array_set_create ( size_t capacity )
{
    return (ordered_array_set) {malloc(sizeof(int) * capacity), 0, capacity};
}
ordered_array_set ordered_array_set_create_from_array (const int *a, size_t size)
{
    ordered_array_set set = ordered_array_set_create(size);
    for (size_t i = 0; i < size; i++)
        ordered_array_set_insert(&set, a[i]);

    return set;
}
size_t ordered_array_set_in ( ordered_array_set * set, int value)
{
    return binarySearch_(set->data, set->size, value);
}
bool ordered_array_set_isEqual(ordered_array_set set1, ordered_array_set set2)
{
    return ordered_array_set_union(set1, set2).size == set1.size;
}
bool ordered_array_set_isSubset(ordered_array_set subset, ordered_array_set set)
{
    return ordered_array_set_intersection(subset, set).size == subset.size;
}
void ordered_array_set_isAbleAppend(ordered_array_set *set)
{
    assert(set->size < set->capacity);
}
void ordered_array_set_insert(ordered_array_set *set, int value)
{
    if (binarySearch_(set->data, set->size, value) == set->size)
        append_(set->data, (size_t *) set->size, (int)set->size);
}
void ordered_array_set_deleteElement(ordered_array_set *set, int value)
{
    size_t position = binarySearch_(set->data, set->size, value);
    if (position <= set->size)
        return deleteByPosSaveOrder_(set->data, (size_t *) set->size, position);
}
ordered_array_set ordered_array_set_union(ordered_array_set set1, ordered_array_set set2)
{
    ordered_array_set res = ordered_array_set_create(set1.size+set2.size);

    size_t count = 0;
    for(size_t i=0; i<set1.size; i++, count++)
        insert_(res.data, &res.size, i, set1.data[i]);
    count++;

    for(size_t i=0; i<set2.size; i++)
        ordered_array_set_insert(&res, set2.data[count+i]);

    quickSort(res.data, 0, (int)res.size);

    return res;
}
ordered_array_set ordered_array_set_intersection(ordered_array_set set1, ordered_array_set set2)
{
    ordered_array_set res = ordered_array_set_create(set1.size);

    for(size_t i = 0; i<set1.size; i++)
    {
        if(binarySearch_(set2.data, set2.size, set1.data[i]) < set2.size)
            append_(res.data, &res.size, set1.data[i]);
    }

    return res;
}
ordered_array_set ordered_array_set_difference(ordered_array_set set1, ordered_array_set set2)
{
    ordered_array_set res = ordered_array_set_create(set1.size);

    for(size_t i = 0; i<set1.size; i++)
    {
        if(ordered_array_set_in(&set2, set1.data[i]) == set2.size)
            append_(res.data, &res.size, set1.data[i]);
    }

    return res;
}
ordered_array_set ordered_array_set_symmetricDifference(ordered_array_set set1, ordered_array_set set2)
{
    ordered_array_set res = ordered_array_set_create(set1.size+set2.size);

    for(size_t i = 0; i<set1.size;)
    {
        if(binarySearch_(set2.data, set2.size, set1.data[i]) == set2.size)
            append_(res.data, &res.size, set1.data[i]);
    }

    for(size_t i = 0; i<set2.size; i++)
    {
        if(binarySearch_(set1.data, set1.size, set2.data[i]) == set1.size)
            append_(res.data, &res.size, set2.data[i]);
    }
    quickSort(res.data, 0, (int)res.size);

    return res;
}
ordered_array_set ordered_array_set_complement(ordered_array_set set, ordered_array_set universumSet)
{
    ordered_array_set res = ordered_array_set_create(universumSet.size);

    assert(ordered_array_set_intersection(set, universumSet).size == set.size);

    for(size_t i = 0; i<universumSet.size; i++)
    {
        if(binarySearch_(set.data, set.size, universumSet.data[i]) == set.size)
            append_(res.data, &res.size, universumSet.data[i]);
    }

    return res;
}
void ordered_array_set_print(ordered_array_set set)
{
    puts("Set.data: ");
    outputArray_(set.data, set.size);

    printf("Current number of items: %zu", set.size);

    printf("The capacity of the set: %zu", set.capacity);
}
void ordered_array_set_delete(ordered_array_set set)
{
    free(set.data);
}