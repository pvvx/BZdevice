#ifndef _REPORTING_H_
#define _REPORTING_H_


#include "tl_common.h"
#include "zcl_include.h"
typedef struct {
	u32 oldTimeSec;
	u32 oldSysTick;
	u8  cntRepeat;
	u8  extraSend;
} app_wrk_report_t;

extern app_wrk_report_t wrk_rpt;

status_t app_forcedReport(u8 endpoint, u16 claster_id, u16 attr_id);
status_t app_chk_report(u16 uptime_sec);
void app_set_thb_report(void);
void app_report_handler(void);

#endif // _REPORTING_H_
