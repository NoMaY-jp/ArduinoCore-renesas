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

#include "Arduino.h"
#include "variant.h"

extern const PinMuxCfg_t g_pin_cfg[];
extern const size_t g_pin_cfg_size;

std::array<uint16_t, 3> getPinCfgs(const pin_size_t pin, PinCfgReq_t req) {

  std::array<uint16_t, 3> ret = {0 , 0, 0};
  if (pin > g_pin_cfg_size) {
    return ret;
  }

  uint8_t cfg_idx = 0;
  const uint16_t* cfg = g_pin_cfg[pin].list;

  bool thats_all = false;
  uint8_t index = 0;

  while(!thats_all) {

    if(PIN_CFG_REQ_UART_TX == req && IS_PIN_UART_TX(*(cfg + index))) {
      ret[cfg_idx++] = *(cfg + index);
    }
    else if(PIN_CFG_REQ_UART_RX == req && IS_PIN_UART_RX(*(cfg + index))) {
      ret[cfg_idx++] = *(cfg + index);
    }
    else if(PIN_CFG_REQ_SCL == req && IS_PIN_SCL(*(cfg + index))) {
        ret[cfg_idx++] = *(cfg + index);
    }
    else if(PIN_CFG_REQ_SDA == req && IS_PIN_SDA(*(cfg + index))) {
        ret[cfg_idx++] = *(cfg + index);
    }
    else if(PIN_CFG_REQ_MISO == req && IS_PIN_MISO(*(cfg + index))) {
        ret[cfg_idx++] = *(cfg + index);
    }
    else if(PIN_CFG_REQ_MOSI == req && IS_PIN_MOSI(*(cfg + index))) {
        ret[cfg_idx++] = *(cfg + index);
    }
    else if(PIN_CFG_REQ_SCK == req && IS_PIN_SCK(*(cfg + index))) {
        ret[cfg_idx++] = *(cfg + index);
    }
    else if(PIN_CFG_REQ_PWM == req && IS_PIN_PWM(*(cfg + index))) {
      ret[cfg_idx++] = *(cfg + index);
    }
    else if(PIN_CFG_REQ_INTERRUPT == req && IS_PIN_INTERRUPT(*(cfg + index))) {
      ret[cfg_idx++] = *(cfg + index);
    }
    else if(PIN_CFG_REQ_ADC == req && IS_PIN_ANALOG(*(cfg + index))) {
      ret[cfg_idx++] = *(cfg + index);
    }
    else if(PIN_CFG_REQ_CAN_RX == req && IS_PIN_CAN_RX(*(cfg + index))) {
      ret[cfg_idx++] = *(cfg + index);
    }
    else if(PIN_CFG_REQ_CAN_TX == req && IS_PIN_CAN_TX(*(cfg + index))) {
      ret[cfg_idx++] = *(cfg + index);
    }
    else if(PIN_CFG_REQ_DAC == req && IS_PIN_DAC(*(cfg + index))) {
      ret[cfg_idx++] = *(cfg + index);
    }

    if(IS_LAST_ITEM(*(cfg + index))) {
      thats_all = true;
    }
    else {
      index++;
    }
  }
  return ret;
}