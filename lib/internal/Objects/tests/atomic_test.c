//
// Created by eenbabn on 6/4/2025.
//

#include <stdatomic.h>
#include <stdio.h>

// Declare an atomic variable
atomic_size_t global_counter = ATOMIC_VAR_INIT(0);

int main() {
    for (int i = 1; i <= 10; i++)
        printf("Counter: %zu\n", atomic_fetch_add(&global_counter, 1));
    return 0;
}