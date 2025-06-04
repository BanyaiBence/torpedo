//
// Created by bence on 2025. 06. 03..
//

#ifndef UTILMACROS_H
#define UTILMACROS_H

#define count_of(x) (sizeof(x) / sizeof(x[0]))

#define foreach(_item_, _array_)                            \
for(size_t i = 0u, _keep_ = 1u;                         \
_keep_ && i < count_of(_array_);                     \
_keep_ = !_keep_, i++)                              \
for (_item_ = _array_[i]; _keep_; _keep_ = !_keep_)


#define foreach_reverse(_item_, _array_)                     \
for(size_t i = count_of(_array_) - 1u, _keep_ = 1u; \
_keep_ && i < count_of(_array_); \
_keep_ = !_keep_, i--) \
for (_item_ = _array_[i]; _keep_; _keep_ = !_keep_)

#define max(a, b) ((a) > (b)? (a) : (b))

#define min(a, b) ((a) < (b)? (a) : (b))

# define is_box(box) \
({ \
    if (box == NULL) { \
        fprintf(stderr, "Box is NULL\n"); \
        exit(EXIT_FAILURE); \
    } \
    if (box->value == NULL) { \
        fprintf(stderr, "Box value is NULL\n"); \
        exit(EXIT_FAILURE); \
    } \
    true; \
})
if (strncmp(box->base.type_id, "Box_", 4) != 0) {
    fprintf(stderr, "Only boxed types are allowed\n");
    exit(EXIT_FAILURE);
}

#endif //UTILMACROS_H
