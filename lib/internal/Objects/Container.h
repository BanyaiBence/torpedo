//
// Created by bence on 2025. 06. 04..
//

#ifndef CONTAINER_H
#define CONTAINER_H

#include "Object.h"

class(Container, Object)
    void *data; // Pointer to the data stored in the container
    bool is_initialized; // Flag to check if the container is initialized
    void (*destroy)(Container* self);
endclass(Container, Object)

static void Container_destroy(Container* self) {
    super_destroy_Container(self);
    free(self->data);
    free(self);
}

static void Container_init(Container* self) {
    super_init_Container(self);
    self->is_initialized = true;
    self->data = NULL;
    self->destroy = Container_destroy;
}


#endif //CONTAINER_H
