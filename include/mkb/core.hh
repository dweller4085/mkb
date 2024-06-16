#ifndef __mkb_core__
#define __mkb_core__

#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>


#ifdef _DEBUG
    #define __debug__
#endif


#define function auto
#define let auto
#define self (* this)
#define null nullptr


#define __in__
#define __out__
#define __inout__


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

#define m_max(a, b) ((a) > (b) ? (a) : (b))
#define m_min(a, b) ((a) < (b) ? (a) : (b))

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


constexpr u8 u8_max = 255;
constexpr u8 u8_min = 0;
constexpr u16 u16_max = 65535;
constexpr u16 u16_min = 0;
constexpr u32 u32_max = 4294967295;
constexpr u32 u32_min = 0;
constexpr u64 u64_max = 18446744073709551615;
constexpr u64 u64_min = 0;

constexpr s8 s8_max = +127;
constexpr s8 s8_min = -128;
constexpr s16 s16_max = +32767;
constexpr s16 s16_min = -32768;
constexpr s32 s32_max = +2147483647;
constexpr s32 s32_min = -2147483648;
constexpr s64 s64_max = +9223372036854775807;
constexpr s64 s64_min = -9223372036854775808;


constexpr f32 f32_epsilon = FLT_EPSILON;
constexpr f32 f32_max = FLT_MAX;
constexpr f64 f64_epsilon = DBL_EPSILON;
constexpr f64 f64_max = DBL_MAX;


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

#endif // __mkb_core__
