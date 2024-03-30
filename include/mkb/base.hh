#ifndef __mkb_base__
#define __mkb_base__

#include <stdint.h>
#include <assert.h>
#include <string.h>

#define __mkb_funny__

#if defined(__x86_64__) || defined(_M_X64)
    #define __mkb_amd64__
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
    #define __mkb_i386__
#endif

#ifdef _MSC_VER
    #define __mkb_msvc__
#endif

#ifdef __clang__
    #define __mkb_clang__
#endif

#ifdef __GNUC__
    #define __mkb_gcc__
#endif

#ifdef _DEBUG
    #define __mkb_debug__
#endif

#ifdef __cplusplus
    #define __mkb_cc__
#else
    #define __mkb_c__
#endif

#ifdef __mkb_cc__

    #ifdef __mkb_funny__
    
        #define function auto
        #define let auto
        #define self (* this)
        
    #endif
    
    #define null nullptr

#endif

#ifdef  __mkb_c__

    #define null ((void *) 0)
    #define true 1
    #define false 0
    
#endif



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


// todo do something better here?
#define m_assert(condition) (assert(condition))
#define m_die(message, exit_code) ((void) 0)



typedef uint8_t  u8,  uint8,  byte;
typedef uint16_t u16, uint16, word;
typedef uint32_t u32, uint32, dword, uint;
typedef uint64_t u64, uint64, qword;

typedef int8_t  s8,  int8;
typedef int16_t s16, int16;
typedef int32_t s32, int32;
typedef int64_t s64, int64;

typedef float  f32, float32;
typedef double f64, float64;

typedef s64 int_ptr;
typedef u64 uint_ptr;

typedef s32 b32, bool32;


#ifdef __mkb_cc__

    template <typename t_ = byte> struct t_slice {
        operator t_ * () { return this->ptr; }
        t_& operator [] (u64 index) { return this->ptr [index]; }
        t_ * ptr;
        u64 len;
    };
    
    using t_str = t_slice<char>;
    
    template<> struct t_slice<char> {
        static function from_cstr(char * cstr) -> t_str { return { .ptr = cstr, .len = strlen(cstr) }; }
        
        char& operator [] (u64 index) { return this->ptr [index]; }
        bool operator == (t_str other) { return self.len == other.len && !strncmp(self.ptr, other.ptr, self.len); }
        operator char * () { return this->ptr; }
        
        char * ptr;
        u64 len;
    };

#endif // __mkb_cc__

#endif // __mkb_base__
