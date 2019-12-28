# STM32G071-Bare_Minimum
Bare minimum STM32CubeIDE project for the NUCLEO-G071

This project was created to get up and running with the absolute bare minimum of CMSIS files.
It sets up clock to run 64 MHz on internal RC and configures PA5 as output.
It then blinks LED4 on NUCLEO-G071 using a blocking loop.

main.cpp is compatiple with plain C.

Tested on STM32CubeIDE 1.0.2.
Point workspace to STM32G071-Bare_Minimum (which must include the folders .metadata and BlinkLED).
