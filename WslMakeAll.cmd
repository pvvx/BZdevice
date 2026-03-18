@set SWVER=_v0209
@del /Q .\bin\*.bin
@del /Q .\bin\*.zigbee
@del /Q .\build
wsl make -s clean
wsl make -s VERSION_BIN=%SWVER% PROJECT_NAME=Z03MMC POJECT_DEF="-DBOARD=BOARD_LYWSD03MMC" ZNAME="Xiaomi:LYWSD03MMC-bz"
@if not exist "bin\Z03MMC%SWVER%.bin" goto :error
wsl make -s clean
wsl make -s VERSION_BIN=%SWVER% PROJECT_NAME=ZCGDK2 POJECT_DEF="-DBOARD=BOARD_CGDK2" ZNAME="Qingping:CGDK2-bz"
@if not exist "bin\ZCGDK2%SWVER%.bin" goto :error
wsl make -s clean
wsl make -s VERSION_BIN=%SWVER% PROJECT_NAME=ZMHOC122 POJECT_DEF="-DBOARD=BOARD_MHO_C122" ZNAME="MiaoMiaoCe:MHO-C122-bz"
@if not exist "bin\ZMHOC122%SWVER%.bin" goto :error
wsl make -s clean
wsl make -s VERSION_BIN=%SWVER% PROJECT_NAME=ZMHOC401N POJECT_DEF="-DBOARD=BOARD_MHO_C401N" ZNAME="MiaoMiaoCe:MHO-C401N-bz"
@if not exist "bin\ZMHOC401N%SWVER%.bin" goto :error
wsl make -s clean
wsl make -s VERSION_BIN=%SWVER% PROJECT_NAME=ZTS0201Z3000 POJECT_DEF="-DBOARD=BOARD_TS0201_TZ3000" ZNAME="Tuya:TS0201-bz"
@if not exist "bin\ZTS0201Z3000%SWVER%.bin" goto :error
wsl make -s clean
wsl make -s VERSION_BIN=%SWVER% PROJECT_NAME=ZTH03Z POJECT_DEF="-DBOARD=BOARD_TH03Z" ZNAME="Tuya:TH03Z-bz"
@if not exist "bin\ZTH03Z%SWVER%.bin" goto :error
@exit
:error
echo "Error!"

         