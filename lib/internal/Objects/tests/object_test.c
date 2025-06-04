//
// Created by eenbabn on 6/4/2025.
//

#include "../Object.h"

int main() {
    for (int i = 0; i < 10000; i++) {
        new(Object, obj);
        printf("%s", obj.type_id);
        obj.print(&obj);
    }
}