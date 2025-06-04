//
// Created by eenbabn on 6/4/2025.
//

#include "../Container.h"
#include "../../UtilMacros/UtilMacros.h"

int main() {
    Container cs[100];
    for (int i = 0; i < 100; i++) {
        Container c;
        cs[i] = c;
    }
    foreach(Container c, cs) {
        c.print(&c);
        c.base.print(&c.base);
        del(c);
    }

    return 0;
}