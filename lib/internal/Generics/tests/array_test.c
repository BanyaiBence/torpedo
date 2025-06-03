//
// Created by bence on 2025. 06. 03..
//

#include <stdio.h>
// The default array type is int, but we can define our own types as well.
#include "../Array.h"
#include <assert.h>

// Let's define an array for doubles
#define ARRAY_T double
#define ORDER_ARRAY_T(a, b) ((a) > (b))
#define COMPARE_ARRAY_T(a, b) ((a) == (b))
#define ARRAY_T_PRINT_FORMAT "%f" // Default format for printing doubles
#include "../Array.h"

int main(void) {
    int_Array array;
    int_Array_init(&array);
    assert(array.count == 0); // Ensure the array is initialized empty
    assert(array.capacity == 0); // Ensure the initial capacity is zero
    assert(array.items == NULL); // Ensure the items pointer is NULL
    assert(array.push != NULL); // Ensure the push function is initialized
    array.push(&array, 1);
    array.push(&array, 3);
    array.push(&array, 2);

    assert(array.count == 3); // Ensure the count is correct
    assert(array.capacity >= 3); // Ensure the capacity is sufficient
    assert(array.get(&array, 0) == 1); // Ensure the first element is correct
    assert(array.get(&array, 1) == 3); // Ensure the second element is correct
    assert(array.get(&array, 2) == 2); // Ensure the third element is correct
    array.print(&array);
    array.sort(&array);
    assert(array.get(&array, 0) == 1); // After sorting, first element should be 1
    assert(array.get(&array, 1) == 2); // After sorting, second element should be 2
    assert(array.get(&array, 2) == 3); // After sorting, third element should be 3
    assert(array.count == 3); // Ensure the count is still correct after sorting
    array.print(&array);
    array.destroy(&array);
    assert(array.count == 0); // Ensure the array is empty after destruction
    assert(array.items == NULL); // Ensure the items pointer is NULL after destruction

    double_Array array2;
    double_Array_init(&array2);
    assert(array2.count == 0); // Ensure the double array is initialized empty
    assert(array2.capacity == 0); // Ensure the initial capacity is zero
    assert(array2.items == NULL); // Ensure the items pointer is NULL
    assert(array2.push != NULL); // Ensure the push function is initialized


    array2.push(&array2, 1.5);
    array2.push(&array2, 3.14);
    array2.push(&array2, 2.6);
    assert(array2.count == 3); // Ensure the count is correct
    assert(array2.capacity >= 3); // Ensure the capacity is sufficient
    assert(array2.get(&array2, 0) == 1.5); // Ensure the first element is correct
    assert(array2.get(&array2, 1) == 3.14); // Ensure the second element is correct
    assert(array2.get(&array2, 2) == 2.6); // Ensure the third element is correct
    array2.print(&array2);
    array2.sort(&array2);
    assert(array2.get(&array2, 0) == 1.5); // After sorting, first element should be 1.5
    assert(array2.get(&array2, 1) == 2.6); // After sorting, second element should be 2.6
    assert(array2.get(&array2, 2) == 3.14); // After sorting, third element should be 3.14
    assert(array2.count == 3); // Ensure the count is still correct after sorting
    array2.print(&array2);
    array2.destroy(&array2);
    assert(array2.count == 0); // Ensure the double array is empty after destruction
    assert(array2.items == NULL); // Ensure the items pointer is NULL after destruction

    return 0;
}
