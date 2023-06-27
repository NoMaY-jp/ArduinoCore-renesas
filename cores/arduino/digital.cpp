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

void pinMode(pin_size_t pin, const PinMode mode) {
	switch (mode) {
		case INPUT:
		case INPUT_PULLDOWN: // TODO: document the INPUT_PULLDOWN is unavailable
			R_IOPORT_PinCfg(NULL, g_pin_cfg[pin].pin, IOPORT_CFG_PORT_DIRECTION_INPUT);
			break;
		case INPUT_PULLUP:
			R_IOPORT_PinCfg(NULL, g_pin_cfg[pin].pin, IOPORT_CFG_PORT_DIRECTION_INPUT | IOPORT_CFG_PULLUP_ENABLE);
			break;
		case OUTPUT:
			R_IOPORT_PinCfg(NULL, g_pin_cfg[pin].pin, IOPORT_CFG_PORT_DIRECTION_OUTPUT);
			break;
		case OUTPUT_OPENDRAIN:
			R_IOPORT_PinCfg(NULL, g_pin_cfg[pin].pin, IOPORT_CFG_PORT_DIRECTION_OUTPUT | IOPORT_CFG_PMOS_ENABLE);
			break;
		}
}

void digitalWrite(pin_size_t pin, PinStatus val) {
	R_IOPORT_PinWrite(NULL, g_pin_cfg[pin].pin, val == LOW ? BSP_IO_LEVEL_LOW : BSP_IO_LEVEL_HIGH);
}

PinStatus digitalRead(pin_size_t pin) {
	bsp_io_level_t ret;
	R_IOPORT_PinRead(NULL, g_pin_cfg[pin].pin, &ret);
	return (ret == BSP_IO_LEVEL_LOW ? LOW : HIGH);
}
