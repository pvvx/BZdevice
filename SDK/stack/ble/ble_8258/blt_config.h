/********************************************************************************************************
 * @file     blt_config.h
 *
 * @brief    This is the header file for 8258 BLE SDK
 *
 * @author	 BLE GROUP
 * @date         12,2021
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

#pragma once

//////////////////////////////////////////////////////////////////////////////
/**
 *  @brief  Definition for Device info
 */
//#include "drivers.h"
#include "tl_common.h"
#include "platform.h"

#define  MAX_DEV_NAME_LEN 				18

#ifndef DEV_NAME
#define DEV_NAME                        "tModule"
#endif




/////////////////// Flash  Address Config ////////////////////////////
#ifndef		CFG_ADR_MAC
#define		CFG_ADR_MAC						0x76000
#endif

#ifndef		CUST_CAP_INFO_ADDR
#define		CUST_CAP_INFO_ADDR				0x77000
#endif

#ifndef		CUST_FIRMWARE_SIGNKEY_ADDR
#define		CUST_FIRMWARE_SIGNKEY_ADDR		0x77180
#endif




//master
#ifndef		CFG_ADR_PEER
#define		CFG_ADR_PEER					0x78000
#endif








/*
 * only 1 can be set
 */
static inline void blc_app_setExternalCrystalCapEnable(u8  en)
{
	blt_miscParam.ext_cap_en = en;

	WriteAnalogReg(0x8a,ReadAnalogReg(0x8a)|0x80);//close internal cap

}



static inline void blc_app_loadCustomizedParameters(void)
{
	 if(!blt_miscParam.ext_cap_en)
	 {
		 //customize freq_offset adjust cap value, if not customized, default ana_81 is 0xd0
		 u8 cap_frqoft = *(unsigned char*) CUST_CAP_INFO_ADDR;
		 if( cap_frqoft != 0xff ){
			 analog_write(0x8A, cap_frqoft );
		 }
	 }
}







///////////////////  Feature ////////////////////////////


#ifndef SECURE_CONNECTION_ENABLE
#define SECURE_CONNECTION_ENABLE							1
#endif









#ifndef  LL_MASTER_MULTI_CONNECTION
#define  LL_MASTER_MULTI_CONNECTION							0
#endif




#ifndef  LL_MULTI_MASTER_SINGLE_SLAVE_ENABLE
#define  LL_MULTI_MASTER_SINGLE_SLAVE_ENABLE				0
#endif


#if (LL_MULTI_MASTER_SINGLE_SLAVE_ENABLE)

	#define BLE_CORE42_DATA_LENGTH_EXTENSION_ENABLE			0  // process later
	#define	FIX_HW_CRC24_EN						            1
	#define BLUETOOTH_VER									BLUETOOTH_VER_4_2
#endif




#ifndef		BLS_ADV_INTERVAL_CHECK_ENABLE
#define		BLS_ADV_INTERVAL_CHECK_ENABLE					0
#endif




#define	BLS_BLE_RF_IRQ_TIMING_EXTREMELY_SHORT_EN			0



//conn param update/map update
#ifndef	BLS_PROC_MASTER_UPDATE_REQ_IN_IRQ_ENABLE
#define BLS_PROC_MASTER_UPDATE_REQ_IN_IRQ_ENABLE			0
#endif


#ifndef LE_AUTHENTICATED_PAYLOAD_TIMEOUT_SUPPORT_EN
#define LE_AUTHENTICATED_PAYLOAD_TIMEOUT_SUPPORT_EN			0
#endif


#ifndef FIX_HW_CRC24_EN
#define	FIX_HW_CRC24_EN										1
#endif


#ifndef DEEP_RET_ENTRY_CONDITIONS_OPTIMIZATION_EN
#define	DEEP_RET_ENTRY_CONDITIONS_OPTIMIZATION_EN			0
#endif


#ifndef HOST_CONTROLLER_DATA_FLOW_IMPROVE_EN
#define	HOST_CONTROLLER_DATA_FLOW_IMPROVE_EN				1
#endif

#if (HOST_CONTROLLER_DATA_FLOW_IMPROVE_EN)
	#define ATT_RSP_BIG_MTU_PROCESS_EN						1
#endif






//Link layer feature enable flag default setting
#ifndef BLE_CORE42_DATA_LENGTH_EXTENSION_ENABLE
#define BLE_CORE42_DATA_LENGTH_EXTENSION_ENABLE						1
#endif

#ifndef LL_FEATURE_SUPPORT_LE_2M_PHY
#define LL_FEATURE_SUPPORT_LE_2M_PHY								1
#endif

#ifndef LL_FEATURE_SUPPORT_LE_CODED_PHY
#define LL_FEATURE_SUPPORT_LE_CODED_PHY								1
#endif

#ifndef LL_FEATURE_SUPPORT_LE_EXTENDED_ADVERTISING
#define LL_FEATURE_SUPPORT_LE_EXTENDED_ADVERTISING					1
#endif

#ifndef LL_FEATURE_SUPPORT_LE_PERIODIC_ADVERTISING
#define LL_FEATURE_SUPPORT_LE_PERIODIC_ADVERTISING					0
#endif

#ifndef LL_FEATURE_SUPPORT_CHANNEL_SELECTION_ALGORITHM2
#define LL_FEATURE_SUPPORT_CHANNEL_SELECTION_ALGORITHM2				1
#endif




#ifndef BQB_LOWER_TESTER_ENABLE
#define BQB_LOWER_TESTER_ENABLE										0
#endif




///////////////////////////////////////dbg channels///////////////////////////////////////////
#ifndef	DBG_CHN0_TOGGLE
#define DBG_CHN0_TOGGLE
#endif

#ifndef	DBG_CHN0_HIGH
#define DBG_CHN0_HIGH
#endif

#ifndef	DBG_CHN0_LOW
#define DBG_CHN0_LOW
#endif

#ifndef	DBG_CHN1_TOGGLE
#define DBG_CHN1_TOGGLE
#endif

#ifndef	DBG_CHN1_HIGH
#define DBG_CHN1_HIGH
#endif

#ifndef	DBG_CHN1_LOW
#define DBG_CHN1_LOW
#endif

#ifndef	DBG_CHN2_TOGGLE
#define DBG_CHN2_TOGGLE
#endif

#ifndef	DBG_CHN2_HIGH
#define DBG_CHN2_HIGH
#endif

#ifndef	DBG_CHN2_LOW
#define DBG_CHN2_LOW
#endif

#ifndef	DBG_CHN3_TOGGLE
#define DBG_CHN3_TOGGLE
#endif

#ifndef	DBG_CHN3_HIGH
#define DBG_CHN3_HIGH
#endif

#ifndef	DBG_CHN3_LOW
#define DBG_CHN3_LOW
#endif

#ifndef	DBG_CHN4_TOGGLE
#define DBG_CHN4_TOGGLE
#endif

#ifndef	DBG_CHN4_HIGH
#define DBG_CHN4_HIGH
#endif

#ifndef	DBG_CHN4_LOW
#define DBG_CHN4_LOW
#endif

#ifndef	DBG_CHN5_TOGGLE
#define DBG_CHN5_TOGGLE
#endif

#ifndef	DBG_CHN5_HIGH
#define DBG_CHN5_HIGH
#endif

#ifndef	DBG_CHN5_LOW
#define DBG_CHN5_LOW
#endif

#ifndef	DBG_CHN6_TOGGLE
#define DBG_CHN6_TOGGLE
#endif

#ifndef	DBG_CHN6_HIGH
#define DBG_CHN6_HIGH
#endif

#ifndef	DBG_CHN6_LOW
#define DBG_CHN6_LOW
#endif

#ifndef	DBG_CHN7_TOGGLE
#define DBG_CHN7_TOGGLE
#endif

#ifndef	DBG_CHN7_HIGH
#define DBG_CHN7_HIGH
#endif

#ifndef	DBG_CHN7_LOW
#define DBG_CHN7_LOW
#endif



#ifndef	BLC_REGISTER_DBG_GPIO_IN_STACK
#define BLC_REGISTER_DBG_GPIO_IN_STACK		0
#endif




#ifndef PA_TXEN_PIN
#define PA_TXEN_PIN                         GPIO_PB2
#endif

#ifndef PA_RXEN_PIN
#define PA_RXEN_PIN                         GPIO_PB3
#endif



#define PA_TYPE_OFF							0
#define PA_TYPE_TX_ON						1
#define PA_TYPE_RX_ON						2


typedef void (*rf_pa_callback_t)(int type);
extern rf_pa_callback_t  blc_rf_pa_cb;
