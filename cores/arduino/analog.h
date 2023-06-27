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

#ifndef ARDUINO_ANALOG_H
#define ARDUINO_ANALOG_H

#include "Arduino.h"
#include "r_adc_api.h"
#include "r_adc.h"
#include "bsp_api.h"
#include "r_dac.h"
#if (DAC8_HOWMANY > 0)
#include "r_dac8.h"
#endif

using ADCCbk_f = void (*)(adc_callback_args_t * p_args);

using ADCIrqCbk_f = void (*)(uint8_t unit);

typedef enum {
  ADC_IRQ_SCAN_END,
  ADC_IRQ_SCAN_END_B,
  ADC_IRQ_WIN_CMP_A,
  ADC_IRQ_WIN_CMP_B
} ADCIrqType_t;


class ADC_Container {
public:
  ADC_Container(uint8_t unit, ADCCbk_f cbk, void *ctx = nullptr);
  ~ADC_Container();
  adc_instance_ctrl_t ctrl;
  adc_extended_cfg_t cfg_extend;
  adc_cfg_t cfg;
  adc_channel_cfg_t channel_cfg;
};

bool analogAttachIrq(ADCIrqCbk_f cbk, ADCIrqType_t type, uint8_t priority = 12);



typedef enum {
  ADC_SCAN_GROUP_A,
  ADC_SCAN_GROUP_B //unsupported
} ScanGroup_t;

/* only add to SCAN GROUP A is supported */
bool analogAddPinToGroup(bsp_io_port_pin_t pin, ScanGroup_t g = ADC_SCAN_GROUP_A);
bool analogAddPinToGroup(pin_size_t pinNumber, ScanGroup_t g = ADC_SCAN_GROUP_A);

void analogStartScan();


bool attachScanEndIrq(ADCIrqCbk_f cbk, adc_mode_t mode = ADC_MODE_SINGLE_SCAN, uint8_t priority = 12);
#ifdef USE_SCAN_GROUP_B
bool attachScanEndBIrq(ADCIrqCbk_f cbk, adc_mode_t mode = ADC_MODE_GROUP_SCAN, uint8_t priority = 12);
#endif
bool analogAttachIrqCompareA(uint16_t low_th, uint16_t high_th, bool enable_window, ADCIrqCbk_f cbk, adc_mode_t mode = ADC_MODE_CONTINUOUS_SCAN, uint8_t priority  = 12 );
bool analogAttachIrqCompareB(bsp_io_port_pin_t pinNumber, bool lower_or_outside_wnd, uint16_t low_th, uint16_t high_th, bool enable_window, ADCIrqCbk_f cbk, adc_mode_t mode = ADC_MODE_CONTINUOUS_SCAN, uint8_t priority = 12);
bool analogAttachIrqCompareB(pin_size_t pinNumber, bool lower_or_outside_wnd, uint16_t low_th, uint16_t high_th, bool enable_window, ADCIrqCbk_f cbk, adc_mode_t mode = ADC_MODE_CONTINUOUS_SCAN, uint8_t priority = 12);
bool analogAddPinToCompare(bsp_io_port_pin_t pin, bool lower_or_outside_wnd) ;
bool analogAddPinToCompare(pin_size_t pinNumber, bool lower_or_outside_wnd);

int analogRead(bsp_io_port_pin_t pinNumber);

#endif