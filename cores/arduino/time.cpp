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
#include "IRQManager.h"
#include "FspTimer.h"

volatile unsigned long agt_time_ms = 0;
uint32_t _freq_hz = 0;

__attribute__((weak)) void delay(uint32_t ms) {
	R_BSP_SoftwareDelay(ms, BSP_DELAY_UNITS_MILLISECONDS);
}

void delayMicroseconds(unsigned int us) {
	R_BSP_SoftwareDelay(us, BSP_DELAY_UNITS_MICROSECONDS);
}

__attribute__((weak)) void yield() {
}

static FspTimer main_timer;

static uint32_t _top_counter;

static void timer_micros_callback(timer_callback_args_t __attribute((unused)) *p_args) {
	agt_time_ms += 1; //1ms
}

void startAgt() {
	main_timer.begin(TIMER_MODE_PERIODIC, AGT_TIMER, 0, 2000.0f, 0.5f, timer_micros_callback);
	IRQManager::getInstance().addPeripheral(IRQ_AGT,(void*)main_timer.get_cfg());
	main_timer.open();
	_top_counter = main_timer.get_counter();
	main_timer.start();
	_freq_hz = main_timer.get_freq_hz();
}

unsigned long millis()
{
#ifdef AZURE_RTOS_THREADX
	return tx_time_get();
#else
	return agt_time_ms;
#endif
}

unsigned long micros() {

	// Convert time to us
	NVIC_DisableIRQ(main_timer.get_cfg()->cycle_end_irq);
	uint32_t time_us = ((main_timer.get_period_raw() - main_timer.get_counter()) * 1000 / main_timer.get_period_raw()) +  (agt_time_ms * 1000);
	NVIC_EnableIRQ(main_timer.get_cfg()->cycle_end_irq);
	return time_us;
}
