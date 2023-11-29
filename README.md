# BZdevice
Experimental firmware for devices on the TLSR825x chip operating simultaneously in Zigbee 3 and Bluetooth LE.

## Test version for Xiaomi LYWSD03MMC.

Average consumption for Xiaomi LYWSD03MMC B1.4 - 18 µA

* Warning: Not use BLE OTA TelinkMiFlasher for this version! The OTA BLE function uses a different format!

## Dual Zigbee + BLE device

![image](https://github.com/pvvx/BZdevice/assets/12629515/f0b2662c-ad69-42fe-9d2f-96fefca9850f)


![image](https://github.com/pvvx/BZdevice/assets/12629515/7a384562-41bf-4311-9356-7d7ccf695b19)

## Reports configurations in ZHA:

RelativeHumidity: min/max/change - 30/180/50

TemperatureMeasurement: min/max/change - 30/180/10

![image](https://github.com/pvvx/BZdevice/assets/12629515/960e19b5-cc69-4ff2-9eb6-57030053ea0c)

If the measured values by the sensor change rapidly:

![image](https://github.com/pvvx/BZdevice/assets/12629515/06cc4639-dbf2-48dc-91f5-ce85add8b7f6)

For BLE it is always 10 seconds.
