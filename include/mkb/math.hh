#ifndef __mkb_math__
#define __mkb_math__

#include "core.hh"

struct t_vec2 {
    union { f32 x; };
    union { f32 y; };
};

using vec2 = t_vec2;

#endif // __mkb_math__
