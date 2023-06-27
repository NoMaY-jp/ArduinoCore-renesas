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

#ifndef _ARDUINO_FIFO_BUFFER_DH_
#define _ARDUINO_FIFO_BUFFER_DH_

#include <stdint.h>
#include <string.h>
#include <Arduino.h>

namespace arduino {


#define FIFO_DEFAULT_SIZE 64

template <typename T, uint32_t size = FIFO_DEFAULT_SIZE>
class FifoBuffer
{
  private:
    uint32_t nextIndex(uint32_t index) {
      synchronized {
        return (uint32_t)(index + 1) % size;
      }
    }
    inline bool isEmpty() const { return (_numElems == 0); }
    T _aucBuffer[size] ;
    uint32_t _iHead ;
    uint32_t _iTail ;
    uint32_t _numElems;
  public:
    /* ---------------------------------------------------------------------- */
    FifoBuffer( void ) {
      memset( _aucBuffer, 0, size * sizeof(T) ) ;
      clear();
    }
    /* ---------------------------------------------------------------------- */
    bool store( T c ) {
      bool rv = true;
      synchronized {
        if (!isFull()) {
          _aucBuffer[_iHead] = c ;
          _iHead = nextIndex(_iHead);
          _numElems++;
        }
        else {
          rv = false;
        }
      }
      return rv;
    }
    /* ---------------------------------------------------------------------- */
    void clear() {
      _iHead = 0;
      _iTail = 0;
      _numElems = 0;
    }
    /* ---------------------------------------------------------------------- */
    T read(bool *read_ok) {
      *read_ok = true;
      if (isEmpty()) {
        *read_ok = false;
        return _aucBuffer[0];
      }
      synchronized {
        T value = _aucBuffer[_iTail];
        _iTail = nextIndex(_iTail);
        _numElems--;
      
        return value;
      }
    }
    /* ---------------------------------------------------------------------- */
    int available() {
      synchronized {
        return _numElems;
      }
    }
    /* ---------------------------------------------------------------------- */
    int freePositions() {
      synchronized {
        return (size - _numElems);
      }
    }
    /* ---------------------------------------------------------------------- */
    T peek() {
      if (isEmpty())
        return -1;

      return _aucBuffer[_iTail];
    }
    /* ---------------------------------------------------------------------- */
    bool isFull() {
      synchronized {
        return (_numElems == size);
      }
    }
    /* ---------------------------------------------------------------------- */
    uint32_t lenght()  const { return size; }

  
};


} //namespace arduino

#endif /* _ARDUINO_FIFO_BUFFER_DH_ */
#endif /* __cplusplus */