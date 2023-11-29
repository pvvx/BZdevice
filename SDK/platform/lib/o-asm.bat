@set TLSDK=E:\Telink\SDK
@set PATH=%TLSDK%\bin;%TLSDK%\opt\tc32\bin;%TLSDK%\usr\bin;%PATH%
for %%a in (*.a) do (
md %%a.o
cd %%a.o
tc32-elf-ar x ..\%%a
for %%o in (*.o) do tc32-elf-objdump -S %%o > %%o.asm
cd ..
)

