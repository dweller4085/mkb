#ifndef __mkb_base__
#define __mkb_base__

#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>


#ifdef _DEBUG
    #define __debug__
#endif


#define function auto
#define let auto
#define self (* this)
#define null nullptr


#define m_pow2_modulo(x, a) ((x) & ((a) - 1))
#define m_is_aligned(x, a) (m_pow2_modulo((x), (a)) == 0)
#define m_is_power_of_two(x) (m_pow2_modulo((x), (x)) == 0)

#define m_distance_forward_to_align(x, a) ((a) - m_pow2_modulo((x), (a)))
#define m_distance_backward_to_align(x, a) (m_pow2_modulo((x), (a)))
#define m_align_forward(x, a) ((x) + m_distance_forward_to_align((x), (a)))
#define m_align_backward(x, a) ((x) - m_distance_backward_to_align((x), (a)))

#define m_clamp_above(x, upper_bound) (((x) > (upper_bound)) ? (upper_bound) : (x))
#define m_clamp_below(x, lower_bound) (((x) < (lower_bound)) ? (lower_bound) : (x))
#define m_clamp(x, lower_bound, upper_bound) (m_clamp_above(m_clamp_below((x), (lower_bound)), (upper_bound)))

#define m_idiv_ceil(a, b) (((a) - 1) / (b) + 1)
#define m_idiv_floor(a, b) ((a) / (b))

#define m_assert(condition) (assert(condition))


typedef uint8_t  u8,  uint8;
typedef uint16_t u16, uint16;
typedef uint32_t u32, uint32;
typedef uint64_t u64, uint64;

typedef int8_t  s8,  int8;
typedef int16_t s16, int16;
typedef int32_t s32, int32;
typedef int64_t s64, int64;

typedef float  f32, float32;
typedef double f64, float64;

typedef int64_t int_ptr;
typedef uint64_t uint_ptr;

typedef int32_t b32, bool32;


template <typename t_ = u8> struct t_slice {
    u64 length() { return len; }
    t_ * at(u64 index) { return ptr + index; }
    operator t_ * () { return this->ptr; }
    t_& operator [] (u64 index) { return this->ptr[index]; }
    
    t_ * ptr;
    u64 len;
};

template<> struct t_slice<char> {
    t_slice() = default;
    t_slice(char const * str): ptr { const_cast<char *>(str)}, len {strlen(str)} {}
    
    char& operator [] (u64 index) { return this->ptr[index]; }
    bool operator == (t_slice<char> other) { return self.len == other.len && !strncmp(self.ptr, other.ptr, self.len); }
    operator char * () { return this->ptr; }
    
    char * ptr;
    u64 len;
};

using t_str = t_slice<char>;

#endif // __mkb_base__
