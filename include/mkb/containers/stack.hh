#ifndef __mkb_stack__
#define __mkb_stack__

#include "../base.hh"

template<typename t_> struct t_stack {
    static function create(t_slice<> memory) -> t_stack;    
    
    function init(t_slice<> memory) -> void;
    function push(t_ * item) -> void;
    function pop() -> t_ *;
    function top() -> t_ *;
    function is_empty() -> bool;
    
    t_slice<> memory;
    mword head;
};

template<typename t_> inline function t_stack<t_>::create(t_slice<> memory) -> t_stack {
    return { .memory = memory, .head = 0 };
}

template<typename t_> inline function t_stack<t_>::init(t_slice<> memory) -> void {
    self = t_stack::create(memory);
}

template<typename t_> inline function t_stack<t_>::push(t_ * item) -> void {
    
}

template<typename t_> inline function t_stack<t_>::pop() -> t_ * {
    
}

template<typename t_> inline function t_stack<t_>::top() -> t_ * {
    
}

template<typename t_> inline function t_stack<t_>::is_empty() -> bool {
    return self.head == 0;
}


#endif // __mkb_stack__
