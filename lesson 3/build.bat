clang++ --target=thumb -mthumb -mfloat-abi=soft -fdeclspec  -c -m32 -O0 lesson3.cpp engine.cpp utils.cpp f_math.cpp m_math.cpp
..\tools\Linker engine.o utils.o f_math.o m_math.o lesson3.o lesson3.vex
copy lesson3.vex lesson3.bin
"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -P lesson3.bin 0x08006000
"C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe" -Rst
pause
