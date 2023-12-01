# BZdevice
Experimental firmware for devices on the TLSR825x chip operating simultaneously in Zigbee 3 and Bluetooth LE.

## Test version for Xiaomi LYWSD03MMC.

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

It is not recommended to use experimental versions for those who do not have the ability to reprogram the device using wired connections!

For those not afraid to experiment:

* The firmware is carried out from the [BLE version](https://github.com/pvvx/ATC_MiThermometer) by downloading a [*.zigbee or *.bin](https://github.com/pvvx/BZdevice/tree/master/bin) file  in [TelinkMiFlasher.html](https://pvvx.github.io/ATC_MiThermometer/TelinkMiFlasher.html). In the file name input field, paste https://github.com/pvvx/BZdevice/raw/master/bin/1141-020a-01113001-Z03MMC.zigbee
* For BLE OTA, when this version is already working, [TelinkOTA.html](https://pvvx.github.io/ATC_MiThermometer/TelinkOTA.html) is used. 
