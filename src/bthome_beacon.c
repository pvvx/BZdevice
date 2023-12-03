/*
 * bthome_beacon.c
 *
 *  Created on: 17.10.23
 *      Author: pvvx
 */

#include "tl_common.h"
#include "ble_cfg.h" // 8258/gap/gap.h"
#include "stack/ble/ble.h" // 8258/gap/gap.h"
#include "device.h"
#include "sensors.h"
#include "bthome_beacon.h"

#define USE_OUT_AVERAGE_BATTERY		1

adv_buf_t adv_buf;

extern u8 my_batVal;
//void bls_set_advertise_prepare(void *p);

//_attribute_ram_code_
__attribute__((optimize("-Os")))
void bthome_data_beacon(padv_bthome_ns1_t p) {
	//	padv_bthome_ns1_t p = (padv_bthome_ns1_t)&adv_buf.data;
	p->flag[0] = 0x02; // size
	p->flag[1] = GAP_ADTYPE_FLAGS; // type
	/*	Flags:
	 	bit0: LE Limited Discoverable Mode
		bit1: LE General Discoverable Mode
		bit2: BR/EDR Not Supported
		bit3: Simultaneous LE and BR/EDR to Same Device Capable (Controller)
		bit4: Simultaneous LE and BR/EDR to Same Device Capable (Host)
		bit5..7: Reserved
	 */
	p->flag[2] = 0x04 | GAP_ADTYPE_LE_GENERAL_DISCOVERABLE_MODE_BIT; // Flags
	p->head.type = GAP_ADTYPE_SERVICE_DATA_UUID_16BIT; // 16-bit UUID
	p->head.UUID = ADV_BTHOME_UUID16;
	p->info = BtHomeID_Info;
	p->p_id = BtHomeID_PacketId;
	p->pid = (u8)adv_buf.send_count;
	p->data.b_id = BtHomeID_battery;
	p->data.battery_level = measured_data.batVal;
	p->data.t_id = BtHomeID_temperature;
	p->data.temperature = measured_data.temp; // x0.01 C
	p->data.h_id = BtHomeID_humidity;
	p->data.humidity = measured_data.humi; // x0.01 %
	p->data.v_id = BtHomeID_voltage;
#if USE_OUT_AVERAGE_BATTERY
	p->data.battery_mv = measured_data.average_battery_mv; // x mV
#else
	p->data.battery_mv = measured_data.battery_mv; // x mV
#endif
	p->head.size = sizeof(adv_bthome_ns1_t) - sizeof(p->head.size) - sizeof(p->flag);
}

//	bls_set_advertise_prepare(app_advertise_prepare_handler); // TODO: not work if EXTENDED_ADVERTISING
int app_advertise_prepare_handler(rf_packet_adv_t * p)	{
	(void) p;
	if(adv_buf.adv_restore_count) {
		adv_buf.adv_restore_count--;
		if(adv_buf.adv_restore_count == 0)
			// restore next adv. interval
			blta.advInt_min = DEF_ADV_INTERVAL_MIN;
			blta.advInt_max = DEF_ADV_INTERVAL_MAX;
			blta.adv_interval = DEF_ADV_INTERVAL_MIN*625*CLOCK_16M_SYS_TIMER_CLK_1US; // system tick
	}
	if (measured_data.flag & FLG_MEASURE_ADV) { // new measured_data ?
		measured_data.flag &= ~FLG_MEASURE_ADV;
		adv_buf.send_count++; // count & id advertise, = beacon_nonce.cnt32
		bthome_data_beacon(&adv_buf.data);
		bls_ll_setAdvData((u8 *)&adv_buf.data, sizeof(adv_buf.data));
	}
	return 1;		// = 1 ready to send ADV packet, = 0 not send ADV
}



