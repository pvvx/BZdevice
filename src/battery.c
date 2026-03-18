/*
 * battery.c
 *
 *  Created on: 18 нояб. 2023 г.
 *      Author: pvvx
 */

#include "tl_common.h"
#include "device.h"
#include "sensors.h"
#include "lcd.h"

#define _BAT_SPEED_CODE_SEC_ //_attribute_ram_code_sec_ // for speed
#define BAT_AVERAGE_COUNT_SHL	9 // 4,5,6,7,8,9,10,11,12 -> 16,32,64,128,256,512,1024,2048,4096

struct {
	u32 summ;
	u32 cnt;
} bat_average;

_BAT_SPEED_CODE_SEC_
__attribute__((optimize("-Os")))
void battery_detect(bool startup_flg)
{
	u16 battery_level = BATTERY_LOW_POWER;
	if(startup_flg)
		battery_level = BATTERY_SAFETY_THRESHOLD;
	adc_channel_init(SHL_ADC_VBAT);
	measured_data.battery_mv = get_adc_mv(0);
	if(measured_data.battery_mv < battery_level){
#if PM_ENABLE
#if USE_DISPLAY
		display_off();
#endif
#if USE_SENSOR_TH
		sensor_go_sleep();
#endif
		drv_pm_longSleep(PM_SLEEP_MODE_DEEPSLEEP, PM_WAKEUP_SRC_TIMER, LOW_POWER_SLEEP_TIME_ms);
#else
		SYSTEM_RESET();
#endif
	}
	bat_average.summ += measured_data.battery_mv;
	bat_average.cnt++;
	if(bat_average.cnt >= (1<<BAT_AVERAGE_COUNT_SHL)) {
		measured_data.average_battery_mv = bat_average.summ >> BAT_AVERAGE_COUNT_SHL;
		bat_average.summ -= measured_data.average_battery_mv;
		bat_average.cnt--;
	} else {
		measured_data.average_battery_mv = bat_average.summ / bat_average.cnt;
	}
	if(measured_data.average_battery_mv > BATTERY_SAFETY_THRESHOLD) {
		battery_level = (measured_data.average_battery_mv - BATTERY_SAFETY_THRESHOLD) / 4;
		if(battery_level > 200)
			battery_level = 200;
	} else
		battery_level = 0;
    measured_data.battery_level = (u8)battery_level;
    measured_data.batVal = (u8)(battery_level >> 1);
    measured_data.flag |= FLG_MEASURE_VB;
}
