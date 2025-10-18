#ifndef UTIL_H
#define UTIL_H


#define RETURN_IF_NULL_OPT(...) _RETURN_IF_NULL_IMPL(__VA_ARGS__, _WITH_RET, _NO_RET)(__VA_ARGS__)

#define _RETURN_IF_NULL_IMPL(_1, _2, NAME, ...) NAME

#define _WITH_RET(ptr, retval) \
    do { if ((ptr) == nullptr) return (retval); } while (0)

#define _NO_RET(ptr) \
    do { if ((ptr) == nullptr) return; } while (0)

#endif