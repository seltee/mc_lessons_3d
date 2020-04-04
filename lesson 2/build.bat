clang++ --target=thumb -mthumb -mfloat-abi=soft -fdeclspec -c -m32 -Os lesson2.cpp engine.cpp utils.cpp f_math.cpp m_math.cpp
..\tools\Linker lesson2.o engine.o utils.o f_math.o m_math.o lesson2.vex
copy lesson2.vex lesson2.bin
"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -P lesson2.bin 0x08006000
"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -Rst
pause
