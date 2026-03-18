/*
 * battery.h
 *
 *  Created on: 24 янв. 2025 г.
 *      Author: pvvx
 */

#ifndef _BATTERY_H_
#define _BATTERY_H_

#define BATTERY_LOW_POWER			2000//2.0v
#define BATTERY_SAFETY_THRESHOLD	2200//2.2v
#define LOW_POWER_SLEEP_TIME_ms		180*1000 // 180 sec

void adc_channel_init(ADC_InputPchTypeDef p_ain); // in adc_drv.c
u16 get_adc_mv(int flg); // in adc_drv.c

void battery_detect(bool startup_flg);

#endif /* _BATTERY_H_ */
