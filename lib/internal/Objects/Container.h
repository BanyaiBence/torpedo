//
// Created by bence on 2025. 06. 04..
//

#ifndef CONTAINER_H
#define CONTAINER_H

#include "Object.h"

class(Container) { extends(Object);
    void *data; // Pointer to the data stored in the container
    bool is_initialized; // Flag to check if the container is initialized

    void (*destroy)(Container *self); // Function to destroy the container
};
void Container_destroy(Container *self) {
    if (self == NULL) {
        fprintf(stderr, "Error: Container pointer is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (self->data != NULL) {
        free(self->data); // Free the data if it is allocated
        self->data = NULL; // Set data pointer to NULL after freeing
    }
    self->is_initialized = false; // Mark the container as uninitialized
}
void Container_print(const Container *self) {
    if (self == NULL) {
        fprintf(stderr, "Error: Container pointer is NULL.\n");
        exit(EXIT_FAILURE);
    }
    const Container *container = (const Container *) self;
    printf("Container of type: %s\n", container->base.type_id);
    if (container->data != NULL) {
        printf("Data pointer: %p\n", container->data);
    } else {
        printf("Data pointer is NULL.\n");
    }
}

bool Container_equals(const Object *self, const Object *other) {
    if (self == NULL || other == NULL) {
        fprintf(stderr, "Error: One or both Object pointers are NULL.\n");
        return false;
    }
    if (strcmp(self->type_id, other->type_id) != 0) {
        return false; // Different types
    }
    const Container *container_self = (const Container *) self;
    const Container *container_other = (const Container *) other;
    return container_self->data == container_other->data; // Compare data pointers
}

void Container_set_type_id(Container *self, const char *type_id) {
    if (self == NULL) {
        fprintf(stderr, "Error: Container pointer is NULL.\n");
        exit(EXIT_FAILURE);
    }
    if (type_id == NULL) {
        fprintf(stderr, "Error: Type ID cannot be NULL.\n");
        exit(EXIT_FAILURE);
    }
    self->base.type_id = type_id; // Set the type ID of the container
}

char* *Container_get_type_id(const Container *self) {
    if (self == NULL) {
        fprintf(stderr, "Error: Object pointer is NULL.\n");
        exit(EXIT_FAILURE);
    }
    return self->base.type_id; // Return the type ID of the container
}

void Container_init(Container *self, const char *type_id,
                  void (*destroy_fn)(Container *self),
                  void (*print_fn)(const Object *self),
                  bool (*equals_fn)(const Object *self, const Object *other)) {
    if (self == NULL) {
        fprintf(stderr, "Error: Container pointer is NULL.\n");
        exit(EXIT_FAILURE);
    }
    Object_init((Object *) self, type_id, destroy_fn, print_fn, equals_fn);
    self->data = NULL;
    self->is_initialized = false;
}

#endif //CONTAINER_H
