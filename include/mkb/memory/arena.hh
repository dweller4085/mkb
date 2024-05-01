#ifndef __mkb_arena__
#define __mkb_arena__

#include "../base.hh"

// [mkb] (30 apr '24) make a 'bound' arena, that is bound to some allocator?
// [mkb] (30 apr '24) and also make a generic allocator interface I guess?

struct t_arena {
    static constexpr void * memory_exhausted = (void *) (0);
    static function create(t_slice<> memory) -> t_arena;
    
    function alloc(u32 size, u32 align) -> void *;
    function alloc_zeroed(u32 size, u32 align) -> void *;
    function alloc_as_slice(u32 size, u32 align) -> t_slice<>;
    function clear() -> void;
    
    template<typename t_> function alloc_object() -> t_ *;
    template<typename t_> function alloc_array(u32 count) -> t_slice<t_>;
    
    u8 * memory;
    u32 size;
    u32 head;
};

inline function t_arena::create(t_slice<> memory) -> t_arena {
    return { .memory = memory.ptr, .size = (u32) memory.len, .head = 0 };
}

inline function t_arena::alloc(u32 size, u32 align) -> void * {
    let padding = m_distance_forward_to_align((uint_ptr) self.memory + self.head, align);
    m_assert(self.head + size + padding <= self.size);
    
    let memory = self.memory + self.head + padding;
    self.head += size + padding;
    
    return memory;
}

inline function t_arena::alloc_zeroed(u32 size, u32 align) -> void * {
    let memory = self.alloc(size, align);
    memset(memory, 0, size);
    return memory;
}

inline function t_arena::alloc_as_slice(u32 size, u32 align) -> t_slice<> {
    return { .ptr = (u8 *) self.alloc(size, align), .len = size };
}

inline function t_arena::clear() -> void {
    self.head = 0;
}

template<typename t_> function t_arena::alloc_array(u32 count) -> t_slice<t_> {
    return { .ptr = (t_ *) self.alloc(sizeof(t_) * count, alignof(t_)), .len = count };
}

template<typename t_> function t_arena::alloc_object() -> t_ * {
    return (t_ *) self.alloc(sizeof(t_), alignof(t_));
}

#endif // __mkb_arena__
