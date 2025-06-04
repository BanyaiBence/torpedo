//
// Created by bence on 2025. 06. 03..
//

#define EITHER_T_LEFT int
#define EITHER_T_RIGHT double
#include "../Either.h"

int main(void) {;
    Either_int_double either;
    Either_int_double_init(&either);
    either.set_left(&either, 42);
    either.set_right(&either, 3.14);
    int left_value;
    double right_value;
    either.unwrap(&either, &left_value, &right_value);
    printf("Left: %d, Right: %.2f\n", left_value, right_value);
    if (either.is_left) {
        printf("Either is left with value: %d\n", either.get_left(&either));
    } else {
        printf("Either is right with value: %.2f\n", either.get_right(&either));
    }


    return 0;
}