/* 
   Copyright 2015 Quazar Technologies Pvt. Ltd.
   Copyright 2015 Chintalagiri Shashank
   
   This file is part of
   Embedded bootstraps : Subsystem Interfaces
   
   This library is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/

/**
 * @file time.h
 * @brief Time Library Interface
 * 
 */

#ifndef TIME_IF_H
#define TIME_IF_H

#include "app/application.h"
#include "bsp/hal/uc.h"
#include <time/time.h>
#include <time/sync.h>
#include <time/cron.h>

uint16_t app_tm_init(uint16_t ucdm_next_address);

#if APP_ENABLE_SYSTICK == 1
    void systick_init(void);
#endif
    
#if APP_ENABLE_RTC == 1
    uint8_t time_get_rtc_time(tm_real_t * rtime_target);
#endif

#endif
