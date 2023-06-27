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

#ifndef __DAC_H__
#define __DAC_H__

#include "Arduino.h"
#include "r_dac.h"
#if DAC8_HOWMANY > 0
#include "r_dac8.h"
#endif

#ifndef DAC_MAX_CONVERSION_PERIOD
#define DAC_MAX_CONVERSION_PERIOD   4
#endif

using DAC_open_f                 = fsp_err_t(*) (dac_ctrl_t *const p_ctrl, dac_cfg_t const *const p_cfg);
using DAC_close_f                = fsp_err_t(*) (dac_ctrl_t *const p_ctrl);
using DAC_write_f                = fsp_err_t(*) (dac_ctrl_t *const p_ctrl, uint16_t value);
using DAC_start_f                = fsp_err_t(*) (dac_ctrl_t *const p_ctrl);
using DAC_stop_f                 = fsp_err_t(*) (dac_ctrl_t *const p_ctrl);

class CDac {
private:
  #if DAC8_HOWMANY > 0
  dac8_instance_ctrl_t ctrl_dac8;
  dac8_extended_cfg_t  ext_cfg_dac8;
  #endif

  dac_instance_ctrl_t  ctrl_dac;
  dac_extended_cfg_t   ext_cfg_dac;

  dac_cfg_t cfg;

  DAC_open_f           open;
  DAC_close_f          close;
  DAC_write_f          write;
  DAC_start_f          start;
  DAC_stop_f           stop;

  bool pin_init = false;

public:
  CDac(pin_size_t dac);
  void set(uint16_t value);
  void init();
  void analogWrite(int value);
  uint32_t dac;
  pin_size_t pin;
};

extern CDac _dac8[];
extern CDac _dac12[];

#endif