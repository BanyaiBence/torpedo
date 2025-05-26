//
// Created by bence on 2025. 05. 24..
//

#ifndef COMMON_H
#define COMMON_H

#define COUNTOF(x) (sizeof(x) / sizeof(x[0]))

#define FOREACH(_item_, _array_)                            \
for(size_t i = 0u, _keep_ = 1u;                         \
_keep_ && i < COUNTOF(_array_);                     \
_keep_ = !_keep_, i++)                              \
for (_item_ = _array_[i]; _keep_; _keep_ = !_keep_)




#endif //COMMON_H
