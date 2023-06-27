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
#include "FspTimer.h"

#ifndef __ARDUINO_PWM_H__
#define __ARDUINO_PWM_H__


class PwmOut {
  public:
    PwmOut(int pinNumber);
    ~PwmOut();

    /* that is "default" begin that set up a PWM with 490Hz of frequency and 50% of duty cycle */
    bool begin();
    /* with raw = false then period and pulse are supposed to be in micro second
       with raw = true then period_usec and pulse_usec will be user as raw value to be used directly in micro registers 
       Pay attention that in case of raw use the possible divider are
       TIMER_SOURCE_DIV_1
       TIMER_SOURCE_DIV_4 
       TIMER_SOURCE_DIV_16
       TIMER_SOURCE_DIV_64
       TIMER_SOURCE_DIV_256
       TIMER_SOURCE_DIV_1024 */
    bool begin(uint32_t period_usec, uint32_t pulse_usec, bool raw = false, timer_source_div_t sd = TIMER_SOURCE_DIV_1);
    void end();
    bool period(int ms);
    bool pulseWidth(int ms);
    bool period_us(int us);
    bool pulseWidth_us(int us);
    bool period_raw(int period);
    bool pulseWidth_raw(int pulse);
    bool pulse_perc(float duty);
    void suspend();
    void resume();

    FspTimer *get_timer() {return &timer;}

  private:
    bool cfg_pin(int max_index);
    int _pin;
    bool _enabled;
    bool _is_agt;
    TimerPWMChannel_t _pwm_channel;
    
    uint8_t timer_channel;  
    FspTimer timer;
};

#endif //__ARDUINO_PWM_H__
