/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 microDev
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "py/runtime.h"

#include "shared-bindings/watchdog/__init__.h"
#include "shared-bindings/microcontroller/__init__.h"

#include "common-hal/watchdog/WatchDogTimer.h"

#include "hardware/watchdog.h"

#define WATCHDOG_ENABLE watchdog_enable(self->timeout * 1000, false)

void common_hal_watchdog_feed(watchdog_watchdogtimer_obj_t *self) {
    watchdog_update();
}

void common_hal_watchdog_deinit(watchdog_watchdogtimer_obj_t *self) {
    if (self->mode == WATCHDOGMODE_NONE) {
        return;
    }
    hw_clear_bits(&watchdog_hw->ctrl, WATCHDOG_CTRL_ENABLE_BITS);
    self->mode = WATCHDOGMODE_NONE;
}

mp_float_t common_hal_watchdog_get_timeout(watchdog_watchdogtimer_obj_t *self) {
    return self->timeout;
}

void common_hal_watchdog_set_timeout(watchdog_watchdogtimer_obj_t *self, mp_float_t new_timeout) {
    if (!(self->timeout < new_timeout || self->timeout > new_timeout)) {
        return;
    }

    // max timeout is 8.388607 sec, this is rounded down to 8 sec
    mp_arg_validate_int_max(new_timeout, 8, MP_QSTR_timeout);
    self->timeout = new_timeout;

    if (self->mode == WATCHDOGMODE_RESET) {
        WATCHDOG_ENABLE;
    }
}

watchdog_watchdogmode_t common_hal_watchdog_get_mode(watchdog_watchdogtimer_obj_t *self) {
    return self->mode;
}

void common_hal_watchdog_set_mode(watchdog_watchdogtimer_obj_t *self, watchdog_watchdogmode_t new_mode) {
    if (self->mode == new_mode) {
        return;
    }

    switch (new_mode) {
        case WATCHDOGMODE_NONE:
            common_hal_watchdog_deinit(self);
            break;
        case WATCHDOGMODE_RAISE:
            mp_raise_NotImplementedError(NULL);
            break;
        case WATCHDOGMODE_RESET:
            WATCHDOG_ENABLE;
            break;
        default:
            return;
    }

    self->mode = new_mode;
}
