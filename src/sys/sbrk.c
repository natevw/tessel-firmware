// Copyright 2014 Technical Machine, Inc. See the COPYRIGHT
// file at the top-level directory of this distribution.
//
// Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
// http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
// <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
// option. This file may not be copied, modified, or distributed
// except according to those terms.


extern unsigned char  _heap;  // Start of heap defined in linker
extern unsigned char  _eheap; // End of heap

static unsigned char* heap = 0;

unsigned char* _sbrk ( int size ) {
    if (heap == 0) {
        heap = (unsigned char*)&_heap;
    }

    unsigned char* r = heap;

    // Align to 8-byte boundary
    unsigned char* next = (unsigned char*)(((unsigned int)(heap + size) + 7) & ~7);
   
    if (next > &_eheap) {
        return 0; // Out of memory
    } else {
        heap = next;
        return r;
    }    
}