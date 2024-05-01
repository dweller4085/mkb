#ifndef __mkb_stack_allocator__
#define __mkb_stack_allocator__

#include "../core.hh"

struct t_stack_allocator {
    static constexpr void * memory_exhausted = (void *) (0);
    static function create(t_slice<> memory) -> t_stack_allocator;
    
    function init(t_slice<> memory) -> void;
    function push(u32 size, u32 align) -> void *;
    function push_as_slice(u32 size, u32 align) -> t_slice<>;
    function push_remainder() -> t_slice<>;
    function pop() -> void;
    function clear() -> void;
    
    t_slice<> memory;
    u32 frame;
    u32 head;
};

inline function t_stack_allocator::create(t_slice<> memory) -> t_stack_allocator {
    return { .memory = memory, .frame = 0, .head = 0 };
}

inline function t_stack_allocator::init(t_slice<> memory) -> void {
    self = t_stack_allocator::create(memory);
}

inline function t_stack_allocator::push(u32 size, u32 align) -> void * {
    let header_padding = m_distance_forward_to_align((uint_ptr) self.memory.ptr + self.head, alignof(u32));
    let data_padding = m_distance_forward_to_align((uint_ptr) self.memory.ptr + self.head + header_padding + sizeof(u32), align);
    
    m_assert(header_padding + sizeof(u32) + data_padding + size <= self.memory.len);
    
    * ((u32 *) self.memory.ptr + self.head + header_padding) = head;
    
    head += header_padding + sizeof(u32) + data_padding;
    let address = self.memory.ptr + head;
    head += size;
    
    return address;
}

inline function t_stack_allocator::push_as_slice(u32 size, u32 align) -> t_slice<> {
    return { .ptr = (u8 *) self.push(size, align), .len = size };
}

inline function t_stack_allocator::push_remainder() -> t_slice<> {
    // fixme this does not work, because the header u32 takes up space and adds padding
    return self.push_as_slice(self.memory.len - self.head, 1);
}

inline function t_stack_allocator::pop() -> void {
    self.head = self.frame;
    self.frame = * (u32 *) (self.memory.ptr + m_align_forward(self.head, alignof(u32)));
}

inline function t_stack_allocator::clear() -> void {
    self.frame = 0;
    self.head = 0;
}

#endif // __mkb_stack_allocator__
