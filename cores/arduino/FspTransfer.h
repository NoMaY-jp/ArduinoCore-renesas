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

#ifndef ARDUINO_FSP_TRANSFERT_H
#define ARDUINO_FSP_TRANSFERT_H

#include "r_dmac.h"

/* Wrapper class for DMA */

using DmaCallback_f = void (*)(dmac_callback_args_t * cb_data);

class FspDma {
    public:
    FspDma(uint8_t ch) {
        cfg.p_info = &info;
        cfg.p_extend = &extend_cfg;

        info.transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_FIXED;
        info.transfer_settings_word_b.repeat_area = TRANSFER_REPEAT_AREA_SOURCE;
        info.transfer_settings_word_b.irq = TRANSFER_IRQ_END;
        info.transfer_settings_word_b.chain_mode = TRANSFER_CHAIN_MODE_DISABLED;
        info.transfer_settings_word_b.src_addr_mode = TRANSFER_ADDR_MODE_FIXED;
        info.transfer_settings_word_b.size = TRANSFER_SIZE_2_BYTE;
        info.transfer_settings_word_b.mode = TRANSFER_MODE_NORMAL;
        info.p_dest = (void*) NULL;
        info.p_src = (void const*) NULL;
        info.num_blocks = 0;
        info.length = 1;

        extend_cfg.offset = 1; 
        extend_cfg.src_buffer_size = 1;
        extend_cfg.irq = FSP_INVALID_VECTOR;
        extend_cfg.ipl = (BSP_IRQ_DISABLED);
        extend_cfg.channel = ch; 
        extend_cfg.p_callback = NULL; 
        extend_cfg.p_context = NULL; 
        extend_cfg.activation_source = ELC_EVENT_NONE;

        instance.p_ctrl = &ctrl;
        instance.p_cfg = &cfg;
        instance.p_api = &g_transfer_on_dmac;
    }

    bool set_activation_source(elc_event_t ev) {
        extend_cfg.activation_source = ev;
    } 

    bool setup_irq(DmaCallback_f fnc, uint8_t priority = 12, void *ctx = nullptr) {
        bool rv = IRQManager::getInstance().addDMA(extend_cfg);

        if(rv) {
            extend_cfg.ipl = priority;
            extend_cfg.p_callback = fnc;
            extend_cfg.p_context = ctx;
        }
        else {
            extend_cfg.irq = FSP_INVALID_VECTOR;    
        }
        return rv;
    }
    
    
    transfer_cfg_t cfg;
    dmac_instance_ctrl_t ctrl;
    transfer_info_t info;
    dmac_extended_cfg_t extend_cfg;
    transfer_instance_t  instance;
};



#endif