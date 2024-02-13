#ifndef __mkb_string__
#define __mkb_string__

#include <string.h>
#include "base.hh"

using t_str = t_slice<char>;

template<> struct t_slice<char> {
    static function from_cstr(char * cstr) -> t_str {
        return { .ptr = cstr, .len = strlen(cstr) };
    }
    
    bool operator == (t_str other) { return self.len == other.len && !strncmp(self.ptr, other.ptr, self.len); }
    operator char * () { return this->ptr; }
    char& operator [] (u64 index) { return this->ptr [index]; }
    
    char * ptr;
    u64 len;
};

#endif // __mkb_string__