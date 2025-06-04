//
// Created by bence on 2025. 06. 03..
//

#include "../Box.h"

#define BOX_T double
#include "../Box.h"

int main(void) {
    Box_int boxed;
    Box_int_init_and_set(&boxed, 42);


    int unwrapped_value = 0;
    boxed.try_unwrap(&boxed, &unwrapped_value);
    printf("Unwrapped value: %d\n", unwrapped_value);
    boxed.free(&boxed);
    unwrapped_value = 0;
    boxed.try_unwrap(&boxed, &unwrapped_value);
    if (unwrapped_value == 0) {
        printf("Box is empty after free.\n");
    } else {
        printf("Unwrapped value after free: %d\n", unwrapped_value);
    }


    boxed.free(&boxed);

    Box_double double_boxed;
    Box_double_init(&double_boxed);

    double_boxed.set(&double_boxed, 3.14);

    double unwrapped_double_value = 0.0;
    double_boxed.try_unwrap(&double_boxed, &unwrapped_double_value);
    printf("Unwrapped double value: %.2f\n", unwrapped_double_value);

    double_boxed.free(&double_boxed);

    return 0;
}
