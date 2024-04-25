/********************************************************************************************************
 * @file    zigbee_ble_switch.c
 *
 * @brief   This is the source file for zigbee_ble_switch
 *
 * @author  Zigbee Group
 * @date    2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *******************************************************************************************************/

#include "tl_common.h"
#include "zigbee_ble_switch.h"
#include "zb_common.h"
#include "stack/ble/ble.h"
#include "stack/ble/ble_config.h"
#include "stack/ble/ble_common.h"
#include "device.h"
#include "sensors.h"
#include "ble_cfg.h"

app_dualModeInfo_t g_dualModeInfo = {
		.slot     = DUALMODE_SLOT_BLE,
		.bleState = BLS_LINK_STATE_IDLE,
};

#define ZB_RF_ISR_RECOVERY		do{  \
									if(CURRENT_SLOT_GET() == DUALMODE_SLOT_ZIGBEE) rf_set_irq_mask(FLD_RF_IRQ_RX|FLD_RF_IRQ_TX);  \
								}while(0)

extern u8 g_ble_txPowerSet;

_attribute_ram_code_ void switch_to_zb_context(void){
	ZB_RADIO_RX_DISABLE;

	backup_ble_rf_context();

	restore_zb_rf_context();
	//switch tx power for zb mode
	ZB_RADIO_TX_POWER_SET(g_zb_txPowerSet);

	ZB_RADIO_RX_ENABLE;

	CURRENT_SLOT_SET(DUALMODE_SLOT_ZIGBEE);
}


_attribute_ram_code_ void switch_to_ble_context(void){
    /* disable zb rx dma to avoid un-excepted rx interrupt*/
	ZB_RADIO_TX_DISABLE;

	ZB_RADIO_RX_DISABLE;

	restore_ble_rf_context();
	/* switch tx power for ble mode */
	ZB_RADIO_TX_POWER_SET(g_ble_txPowerSet);

	ZB_RADIO_RX_ENABLE;

	CURRENT_SLOT_SET(DUALMODE_SLOT_BLE);
}

#if SCAN_IN_ADV_STATE
/*
 * ble is doing scan in the state of ADV
 *
 * @param ref_tick  beginning time the ADV
 *
 * @param index     is to control the scan interval, scan interval is (ADV-interval * index/16)
 *
 * */
static u32	blc_scan_busy_in_adv(u32 ref_tick, u8 index){
	unsigned int ret = 0;
	if(blts.scan_extension_mask & BLS_FLAG_SCAN_IN_ADV_MODE){
		ret = ((unsigned int)((ref_tick + (blta.adv_interval >> 4) * (index & 0x0f)) - reg_system_tick)) < BIT(30);
	}
	return ret;
}
#endif


inline int is_switch_to_ble(void){
	return get_ble_next_event_tick() - (reg_system_tick + ZIGBEE_AFTER_TIME) > BIT(31);
}

inline int is_switch_to_zigbee(void){
	return get_ble_next_event_tick() - (reg_system_tick + BLE_IDLE_TIME) < BIT(31);
}


void zb_task(void){
	ev_main();

#if (MODULE_WATCHDOG_ENABLE)
	drv_wd_clear();
#endif

    tl_zbTaskProcedure();

}

void concurrent_mode_main_loop(void){
	u32 r = 0;

///	sensors_task();

	APP_BLE_STATE_SET(BLE_BLT_STATE_GET()); //bltParam.blt_state);

	//zb_task();
	//blt_sdk_main_loop();
	//return;

	if(CURRENT_SLOT_GET() == DUALMODE_SLOT_BLE){
		 g_dualModeInfo.bleTaskTick = clock_time();

		 /*
		  * ble task
		  *
		  * */

		 blt_sdk_main_loop();
#if USE_BLE_OTA
		 if(ota_is_working) {
			 return;
//			 while(blt_sdk_main_loop());
		 }
#endif
		 if(APP_BLE_STATE_GET() == BLS_LINK_STATE_CONN) {
			 if(batteryValueInCCC && (measured_data.flag & FLG_MEASURE_CC_VBAT)) {
				 measured_data.flag &= ~FLG_MEASURE_CC_VBAT;
				 bls_att_pushNotifyData(BATT_LEVEL_INPUT_DP_H, (u8 *)&my_batVal, 1);
			 }
		 }

		 DBG_ZIGBEE_STATUS(0x30);

		 r = drv_disable_irq();

		 if(((get_ble_event_state() && is_switch_to_zigbee()) || APP_BLE_STATE_GET() == BLS_LINK_STATE_IDLE)
			 ){
			 /*
			  * ready to switch to ZIGBEE mode
			  *
			  * */
			DBG_ZIGBEE_STATUS(0x31);

			switch_to_zb_context();

			drv_restore_irq(r);
			zb_task();

		 } else {
			 drv_restore_irq(r);
		 }
		 DBG_ZIGBEE_STATUS(0x32);
	 } else {
		 /*
		  * now in zigbee mode
		  *
		  * */
		 DBG_ZIGBEE_STATUS(0x33);

		 r = drv_disable_irq();

		 if(!zb_rfTxDoing() && is_switch_to_ble() && APP_BLE_STATE_GET() != BLS_LINK_STATE_IDLE){
			 /*
			  * ready to switch to BLE mode
			  *
			  * */
			 switch_to_ble_context();

			 DBG_ZIGBEE_STATUS(0x34);

			 drv_restore_irq(r);
			 return;
		 }

		 drv_restore_irq(r);
		 DBG_ZIGBEE_STATUS(0x35);
		 zb_task();
	 }
}

#if 0
u8 ble_task_stop(void){
	u32 r = drv_disable_irq();

	ble_sts_t ret = BLE_SUCCESS;
	if(APP_BLE_STATE_GET() == BLS_LINK_STATE_CONN){
		ret = bls_ll_terminateConnection(HCI_ERR_OP_CANCELLED_BY_HOST);//cut any ble connections
	}else{
		ret = bls_ll_setAdvEnable(BLC_ADV_DISABLE);

		/* rf irq is cleared in the "bls_ll_setAdvEnable",
		 * so that the rf tx/rx interrupt will be missed if the "bls_ll_setAdvEnable" is called in Zigbee mode
		 */
		if(ret == BLE_SUCCESS){
			ZB_RF_ISR_RECOVERY;
		}
	}

	drv_restore_irq(r);
	return ret;
}

u8 ble_task_restart(void){
	u32 r = drv_disable_irq();

	ble_sts_t ret = bls_ll_setAdvEnable(BLC_ADV_ENABLE);
	/* rf irq is cleared in the "bls_ll_setAdvEnable",
	 * so that the rf tx/rx interrupt will be missed if the "bls_ll_setAdvEnable" is called in Zigbee mode
	 */
	if(ret == BLE_SUCCESS){
		ZB_RF_ISR_RECOVERY;
	}

	drv_restore_irq(r);
	return ret;
}
#endif

