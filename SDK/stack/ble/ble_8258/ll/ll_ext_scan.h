/********************************************************************************************************
 * @file     ll_ext_scan.h
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

#ifndef LL_SCAN_EXT_H_
#define LL_SCAN_EXT_H_

#include <stack/ble/ble_8258/ble_common.h>
#include <stack/ble/ble_8258/blt_config.h>
#include <stack/ble/ble_8258/hci/hci_const.h>
#include <stack/ble/ble_8258/hci/hci_event.h>
#include <stack/ble/ble_8258/hci/hci_cmd.h>
#include <stack/ble/ble_8258/ll/ll_adv.h>
#include <stack/ble/ble_8258/ll/ll_encrypt.h>
#include <stack/ble/ble_8258/ll/ll_init.h>
#include <stack/ble/ble_8258/ll/ll_pm.h>
#include <stack/ble/ble_8258/ll/ll_scan.h>
#include <stack/ble/ble_8258/ll/ll_whitelist.h>
#include "stack/ble/ble_8258/ll/ll_conn/ll_slave.h"
#include "stack/ble/ble_8258/ll/ll_conn/ll_master.h"


#include "tl_common.h"
//#include "drivers.h"


/******************************************** User Interface  ********************************************************************/
ble_sts_t blc_ll_setExtScanParam_1_phy (own_addr_type_t  ownAddrType, 	scan_fp_type_t scanFilterPolicy,	u8	scan_phys,
										scan_type_t 	 scanType,    	u16 		   scan_interval, 		u16 scan_window);

ble_sts_t blc_hci_le_setExtScanEnable (scan_en_t  extScan_en, 	dupFilter_en_t filter_duplicate,	u16 duration,	u16 period);



/****************************************** Stack Interface, user can not use!!! *************************************************/

ble_sts_t blc_hci_le_setExtScanParam (own_addr_type_t  ownAddrType, 	scan_fp_type_t scanFilterPolicy,	u8 scan_phys,	u8 *pData);


#endif /* LL_SCAN_EXT_H_ */
