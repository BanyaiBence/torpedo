//
// Created by bence on 2025. 06. 04..
//

#ifndef CLASS_H
#define CLASS_H

// Expand arguments (to support optional second argument)
#define EXPAND(x) x

// Detect if there's a second argument
#define GET_MACRO(_1, _2, NAME, ...) NAME
#define class(...) EXPAND(GET_MACRO(__VA_ARGS__, CLASS_INHERITS, CLASS_SIMPLE)(__VA_ARGS__))
#define inherits(...) EXPAND(GET_MACRO(__VA_ARGS__, INHERITS)(__VA_ARGS__))

// Base class with no inheritance
#define CLASS_SIMPLE(ClassName) \
typedef struct ClassName ClassName; \
struct ClassName

// Class with inheritance (first field is the parent)
#define CLASS_INHERITS(ClassName, BaseName) \
typedef struct ClassName ClassName; \
struct ClassName { \
BaseName base;

#define extends(BaseName) \
    BaseName base;

#define endclass };

#endif //CLASS_H
