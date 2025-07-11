//
// Created by bence on 2025. 05. 24..
//

#ifndef COMMON_H
#define COMMON_H

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





#endif //COMMON_H
