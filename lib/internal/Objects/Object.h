//
// Created by bence on 2025. 06. 04..
//

#ifndef OBJECT_H
#define OBJECT_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "./Class.h"

class(Object){
    const char *type_id; // Unique identifier for the type of object

    void (*destroy)(Object *self); // Function pointer for destroying the object
    void (*print)(const Object *self); // Function pointer for printing the object
    bool (*equals)(const Object *self, const Object *other); // Function pointer for comparing two objects
    void (*set_type_id)(Object *self, const char *type_id); // Function pointer to set the type ID of the object
    char* (*get_type_id)(const Object *self); // Function pointer to get the type ID of the object
};

static inline void Object_init(Object *obj, const char *type_id,
                            void (*destroy_fn)(Object *self),
                            void (*print_fn)(const Object *self),
                            bool (*equals_fn)(const Object *self, const Object *other),
                            void (*set_type_id_fn)(Object *self, const char *type_id),
                            char* (*get_type_id_fn)(const Object *self)
                               ) {
    if (obj == NULL) {
        fprintf(stderr, "Error: Object pointer is NULL.\n");
        exit(EXIT_FAILURE);
    }
    obj->type_id = type_id;
    obj->destroy = destroy_fn;
    obj->print = print_fn;
    obj->equals = equals_fn;
    obj->set_type_id = set_type_id_fn;
    obj->get_type_id = get_type_id_fn;
}

#endif //OBJECT_H
