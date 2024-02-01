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

#endif // __mkb_stack__
