@set TLSDK=D:\MCU\TelinkIoTStudio
@set PATH=%TLSDK%\bin;%TLSDK%\opt\tc32\bin;%TLSDK%\mingw\bin;%TLSDK%\opt\tc32\tc32-elf\bin;%PATH%
@set SWVER=_v0209
@del /Q .\bin\*.bin
@del /Q .\bin\*.zigbee
@del /Q .\build
make -s -j clean
make -s -j VERSION_BIN=%SWVER% PROJECT_NAME=Z03MMC POJECT_DEF="-DBOARD=BOARD_LYWSD03MMC" ZNAME="Xiaomi:LYWSD03MMC-bz"
@if not exist "bin\Z03MMC%SWVER%.bin" goto :error
make -s -j clean
make -s -j VERSION_BIN=%SWVER% PROJECT_NAME=ZCGDK2 POJECT_DEF="-DBOARD=BOARD_CGDK2" ZNAME="Qingping:CGDK2-bz"
@if not exist "bin\ZCGDK2%SWVER%.bin" goto :error
make -s -j clean
make -s -j VERSION_BIN=%SWVER% PROJECT_NAME=ZMHOC122 POJECT_DEF="-DBOARD=BOARD_MHO_C122" ZNAME="MiaoMiaoCe:MHO-C122-bz"
@if not exist "bin\ZMHOC122%SWVER%.bin" goto :error
make -s -j clean
make -s -j VERSION_BIN=%SWVER% PROJECT_NAME=ZMHOC401N POJECT_DEF="-DBOARD=BOARD_MHO_C401N" ZNAME="MiaoMiaoCe:MHO-C401N-bz"
@if not exist "bin\ZMHOC401N%SWVER%.bin" goto :error
make -s -j clean
make -s -j VERSION_BIN=%SWVER% PROJECT_NAME=ZTS0201Z3000 POJECT_DEF="-DBOARD=BOARD_TS0201_TZ3000" ZNAME="Tuya:TS0201-bz"
@if not exist "bin\ZTS0201Z3000%SWVER%.bin" goto :error
make -s -j clean
make -s -j VERSION_BIN=%SWVER% PROJECT_NAME=ZTH03Z POJECT_DEF="-DBOARD=BOARD_TH03Z" ZNAME="Tuya:TH03Z-bz"
@if not exist "bin\ZTH03Z%SWVER%.bin" goto :error
python3 make\zb_bin_ota.py bin\ZTS0201Z3000%SWVER%.bin bin\TS0201z%SWVER% -m0x1141 -i0xd3a3 -v0x01993001 -s"Tuya to BZdevice"
python3 make\zb_bin_ota.py bin\ZTH03Z%SWVER%.bin bin\TH03Zz%SWVER% -m0x1141 -i0xd3a3 -v0x01993001 -s"Tuya to BZdevice"
cd .\zigpy_ota
call update.cmd %SWVER%
cd ..
@exit
:error
echo "Error!"

         