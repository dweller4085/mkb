#ifndef __mkb_arena__
#define __mkb_arena__

#include "../base.hh"

struct t_arena {
    static constexpr void * memory_exhausted = (void *) (0);
    static function create(t_slice<> memory) -> t_arena;
    
    function init(t_slice<> memory) -> void;
    function alloc(dword size, dword align) -> void *;
    function alloc_as_slice(dword size, dword align) -> t_slice<>;
    function clear() -> void;
    
    template<typename t_> function alloc_object() -> t_ *;
    template<typename t_> function alloc_array(dword count) -> t_slice<t_>;
    
    t_slice<> memory;
    dword head;
};

inline function t_arena::create(t_slice<> memory) -> t_arena {
    return { .memory = memory, .head = 0 };
}

inline function t_arena::init(t_slice<> memory) -> void {
    self = t_arena::create(memory);
}

inline function t_arena::alloc(dword size, dword align) -> void * {
    let padding = m_distance_forward_to_align((dword) self.memory.ptr + self.head, align);
    m_assert(self.head + size + padding <= self.memory.len);
    
    let memory = self.memory.ptr + self.head + padding;
    self.head += size + padding;
    
    return memory;
}

inline function t_arena::alloc_as_slice(dword size, dword align) -> t_slice<> {
    return { .ptr = (u8 *) self.alloc(size, align), .len = size };
}

inline function t_arena::clear() -> void {
    self.head = 0;
}

template<typename t_> function t_arena::alloc_array(dword count) -> t_slice<t_> {
    return { .ptr = (t_ *) self.alloc(sizeof(t_) * count, alignof(t_)), .len = count };
}

template<typename t_> function t_arena::alloc_object() -> t_ * {
    return (t_ *) self.alloc(sizeof(t_), alignof(t_));
}

#endif // __mkb_arena__
