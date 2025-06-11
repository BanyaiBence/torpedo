//
// Created by bence on 2025. 06. 03..
//



#define BOX_T int
#include "../Box.h"
#include "../../Objects/Object.h"

int main(void) {
    Box_int* boxed = new(Box_int);

    boxed->set(boxed, 5);

    int unwrapped_value = 0;
    boxed->try_unwrap(boxed, &unwrapped_value);
    printf("Unwrapped value: %d\n", unwrapped_value);
    boxed->free(boxed);
    unwrapped_value = 0;
    boxed->try_unwrap(boxed, &unwrapped_value);
    if (unwrapped_value == 0) {
        printf("Box is empty after free.\n");
    } else {
        printf("Unwrapped value after free: %d\n", unwrapped_value);
    }

    return 0;
}
