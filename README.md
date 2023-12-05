# BZdevice
Experimental firmware for devices on the TLSR825x chip operating simultaneously in Zigbee 3 and Bluetooth LE.

It is not recommended to use experimental versions for those who do not have the ability to reprogram the device using wired connections!

## Firmware supports:

* Zigbee OTA
* BLE OTA
* ZigBee Touchlink commissioning
* BLE advertising BTHome v2
* Screen display configuration

Average consumption for Xiaomi LYWSD03MMC B1.4 - 18 µA

* Warning: Not use BLE OTA TelinkMiFlasher for this version! In the current experimental version, BLE OTA is not yet stable. You may have to use [TelinkOTA.html](https://pvvx.github.io/ATC_MiThermometer/TelinkOTA.html) several times.

## Dual Zigbee + BLE device

![image](https://github.com/pvvx/BZdevice/assets/12629515/f0b2662c-ad69-42fe-9d2f-96fefca9850f)


![image](https://github.com/pvvx/BZdevice/assets/12629515/7a384562-41bf-4311-9356-7d7ccf695b19)

## Reports configurations in ZHA:

RelativeHumidity: min/max/change - 30/180/50

TemperatureMeasurement: min/max/change - 30/180/10

![image](https://github.com/pvvx/BZdevice/assets/12629515/960e19b5-cc69-4ff2-9eb6-57030053ea0c)

If the measured values by the sensor change rapidly:

![image](https://github.com/pvvx/BZdevice/assets/12629515/06cc4639-dbf2-48dc-91f5-ce85add8b7f6)

For BLE, the transmission step of all measured values is always 10 seconds. The transmission is duplicated 2 times in 5 second increments.

Zigbee transmission: ![image](https://github.com/pvvx/BZdevice/assets/12629515/d8e98da0-13df-489b-8ac9-cb7a50797bca)

BLE transmission: ![image](https://github.com/pvvx/BZdevice/assets/12629515/511335e5-dd00-4bbd-983c-233976df4c7a)

## OTA

For those not afraid to experiment:

* The firmware is carried out from the [BLE version](https://github.com/pvvx/ATC_MiThermometer) by downloading a [*.zigbee or *.bin](https://github.com/pvvx/BZdevice/tree/master/bin) file  in [TelinkMiFlasher.html](https://pvvx.github.io/ATC_MiThermometer/TelinkMiFlasher.html). In the file name input field, paste https://github.com/pvvx/BZdevice/raw/master/bin/1141-020a-01113001-Z03MMC.zigbee (for LYWSD03MMC)
* For BLE OTA, when this version is already working, [TelinkOTA.html](https://pvvx.github.io/ATC_MiThermometer/TelinkOTA.html) is used. 

## Zigbee OTA

[OTA update in ZHA](https://github.com/pvvx/ZigbeeTLc/issues/7)

Before flashing the firmware, check the compliance of the “Manufacturer Code” and “Image Type” between the OTA file and those issued by the Zigbee device.

Sample: "1141-020a-01103001-Z03MMC.zigbee" 

| Manufacturer Code | Image Type | File Version | Stack Version | Name | Ext OTA |
| -- | -- | -- | -- | -- | -- |
| 1141 | 020a | 0110 | 3001 | Z03MMC | zigbee |
| 0x1141 - Telink | 0x02 - TLSR825x, 0x0a - Xiaomi LYWSD03MMC | App release 0.1, App build 1.0 | Zigbee v3.0, Release 0.1 |  Z03MMC | OTA |

|Image Type| Device, note |
| -- | -- |
| 0x0201 |  MHO-C401 (old version) |
| 0x0202 |  CGG1 (old version) |
| 0x0203 |  LYWSD03MMC ver https://github.com/devbis/z03mmc |
| 0x0204 |  WATERMETER ver https://github.com/slacky1965/watermeter_zed |
| 0x0206 |  CGDK2 |
| 0x0207 |  CGG1 (new version) |
| 0x0208 |  MHO-C401 (new version) |
| 0x0209 |  MJWSD05MMC |
| 0x020A |  LYWSD03MMC |
| 0x020B |  MHO-C122 |
| 0x0210 |  Water Tank sensors |
| 0x0211 |  TS0201-TZ3000 |
| 0x0212 |  TS0202-TZ3000 |

* To restore to BLE, use the Zigbee OTA file with the same number device from: https://github.com/pvvx/ATC_MiThermometer/tree/master/zigbee_ota

