//
// Created by bence on 2025. 06. 04..
//

#ifndef OBJECT_H
#define OBJECT_H

#include <stdatomic.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

atomic_size_t __GLOBAL_OBJECT_ID = ATOMIC_VAR_INIT(0);

static char *concat_type_id(const char *base_type_id, const char *class_name) {
    const size_t length = strlen(base_type_id) + strlen(class_name) + 2; // +2 for separator and null terminator
    char *result = malloc(length);
    if (result == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    snprintf(result, length, "%s/%s", base_type_id, class_name);
    return result;
}

static size_t get_new_object_id() {
    return atomic_fetch_add(&__GLOBAL_OBJECT_ID, 1);
}


// Expand arguments (to support optional second argument)
#define EXPAND(x) x

// Detect if there's a second argument
#define GET_MACRO(_1, _2, NAME, ...) NAME
#define class(...) EXPAND(GET_MACRO(__VA_ARGS__, CLASS_INHERITS, CLASS_SIMPLE)(__VA_ARGS__))
#define endclass(...) EXPAND(GET_MACRO(__VA_ARGS__, END_CLASS_INHERITS, END_CLASS_SIMPLE)(__VA_ARGS__))

#define new(ClassName) ({ \
ClassName* __obj = malloc(sizeof(ClassName)); \
if (!__obj) { \
fprintf(stderr, "Allocation failed for " #ClassName "\n"); \
exit(EXIT_FAILURE); \
} \
ClassName##_init(__obj); \
__obj; \
})

#define del(ObjectPtr) do { \
if (ObjectPtr) { \
ObjectPtr->destroy(ObjectPtr); \
free(ObjectPtr); \
ObjectPtr = NULL; \
} \
} while(0)

// Base class with no inheritance
#define CLASS_SIMPLE(ClassName) \
typedef struct ClassName ClassName; \
struct ClassName { \
char* type_id; \
int id; \
void (*print)(ClassName* self);


// Class with inheritance (first field is the parent)
#define CLASS_INHERITS(ClassName, BaseName) \
typedef struct ClassName ClassName; \
struct ClassName { \
BaseName base; \
char* type_id; \
int id; \
void (*print)(ClassName* self);


#define END_CLASS_SIMPLE(ClassName) }; \
void super_print_##ClassName(ClassName* self) { \
printf("%s(ID:%zu)\n", self->type_id, self->id); \
} \
void  super_init_##ClassName(ClassName* self){ \
self->id = get_new_object_id(); \
self->print = super_print_##ClassName; \
self->type_id = #ClassName; \
}


#define END_CLASS_INHERITS(ClassName, BaseName) }; \
void super_print_##ClassName(ClassName* self) { \
printf("%s(ID:%zu)\n", self->type_id, self->id); \
} \
void  super_init_##ClassName(ClassName* self){ \
self->id = get_new_object_id(); \
self->print = super_print_##ClassName; \
self-> type_id = #ClassName; \
BaseName ## _init(&(self->base)); \
}

class(Object)

    bool (*equals)(const Object *self, const Object *other);

    void (*destroy)(Object *self);

endclass(Object)


static bool Object_equals(const Object *self, const Object *other) {
    return self->id == other->id;
}

static void Object_destroy(Object *self) {
    free(self->type_id);
}

static void Object_init(Object *obj) {
    super_init_Object(obj);
    if (obj == NULL) {
        fprintf(stderr, "Error: Object pointer is NULL.\n");
        exit(EXIT_FAILURE);
    }
    obj->equals = Object_equals;
    obj->destroy = Object_destroy;
}

#endif //OBJECT_H
