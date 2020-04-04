clang++ --target=thumb -mthumb -mfloat-abi=soft -fdeclspec -c -m32 -Os lesson1.cpp engine.cpp utils.cpp f_math.cpp
..\tools\Linker lesson1.o engine.o utils.o f_math.o lesson1.vex
copy lesson1.vex lesson1.bin
"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -P lesson1.bin 0x08006000
"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -Rst
pause
