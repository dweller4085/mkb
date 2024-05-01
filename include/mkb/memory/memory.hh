#ifndef __mkb_memory__
#define __mkb_memory__

#include <stdlib.h>
#include "../core.hh"

inline function allocate(u64 size) -> t_slice<> {
    return { .ptr = (u8 *) malloc(size), .len = size };
}

#endif // __mkb_memory__
