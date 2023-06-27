/*

MIT License

Copyright (c) 2022-2023 Arduino SA

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifdef __cplusplus

#ifndef _SAFE_RING_BUFFER_
#define _SAFE_RING_BUFFER_

#include <api/RingBuffer.h>
#include "sync.h"

namespace arduino {

template <int N>
class SafeRingBufferN : public RingBufferN<N>
{
  public:
    int read_char();
    void store_char( uint8_t c ) ;
    int available() ;
};

typedef SafeRingBufferN<SERIAL_BUFFER_SIZE> SafeRingBuffer;

template <int N>
int SafeRingBufferN<N>::read_char() {
  synchronized {
    return RingBufferN<N>::read_char();
  }

  // We should never reached this line because the synchronized {} block gets
  // executed at least once. However the compiler gets confused and prints a
  // warning about control reaching the end of a non-void function. This
  // silences that warning.
  return -1;
}

template <int N>
int SafeRingBufferN<N>::available() {
  synchronized {
    return RingBufferN<N>::available();
  }
  return -1;
}

template <int N>
void SafeRingBufferN<N>::store_char(uint8_t c) {
  synchronized {
    RingBufferN<N>::store_char(c);
  }
}

}

#endif /* _SAFE_RING_BUFFER_ */
#endif /* __cplusplus */
