clang++ --target=thumb -mthumb -mfloat-abi=soft -fdeclspec -c -m32 -Os test.cpp engine.cpp utils.cpp f_math.cpp
..\tools\Linker test.o engine.o utils.o f_math.o test.vex
copy test.vex test.bin
"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -P test.bin 0x08006000
"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -Rst
pause
