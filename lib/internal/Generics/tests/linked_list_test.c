//
// Created by bence on 2025. 06. 11..
//



#include "../../UtilMacros/UtilMacros.h"
#define LINKEDLIST_T int
#include "../LinkedList.h"
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    LinkedList_int* list = new(LinkedList_int);
    WITH(list) {
        _this->add(_this, 1);
        _this->add(_this, 2);
        _this->add(_this, 3);
        _this->print(_this);
        _this->reverse(_this);
        _this->print(_this);
        _this->insert(_this, 4, 1);
        _this->print(_this);
    }


    printf("%llu\n", list->index_of(list, 1));
    for (int i = 0; i < 1000; i++) {
        list->add(list, rand() % 100);
    }
    list->print(list);
    printf("%llu\n", list->count(list, 10));

    return 0;
}