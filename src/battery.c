/*
 * battery.c
 *
 *  Created on: 18 нояб. 2023 г.
 *      Author: pvvx
 */

#include "tl_common.h"
#include "device.h"
#include "sensors.h"

#define _BAT_SPEED_CODE_SEC_ //_attribute_ram_code_sec_ // for speed

struct {
	u32 summ;
	u8 cnt;
} bat_average;

_BAT_SPEED_CODE_SEC_
void battery_detect(void)
{
	adc_channel_init(SHL_ADC_VBAT);
	measured_data.battery_mv = get_adc_mv();
	if(measured_data.battery_mv < BATTERY_SAFETY_THRESHOLD){
#if PM_ENABLE
		sensor_go_sleep();
		drv_pm_sleep(PM_SLEEP_MODE_DEEPSLEEP, 0, LOW_POWER_SLEEP_TIME);
#else
		SYSTEM_RESET();
#endif
	}
	bat_average.summ += measured_data.battery_mv;
	bat_average.cnt++;
	measured_data.average_battery_mv = measured_data.battery_mv / bat_average.cnt;
	if(bat_average.cnt >= BATTERY_AVERAGE_COUNT) {
		bat_average.cnt >>= 1;
		bat_average.summ >>= 1;
	}
	measured_data.battery_level = (measured_data.average_battery_mv - BATTERY_SAFETY_THRESHOLD)/4;
    if(measured_data.battery_level > 200)
    	measured_data.battery_level = 200;
    measured_data.batVal = (u8)(measured_data.battery_level >> 1);
    measured_data.flag |= FLG_MEASURE_VB;
}
