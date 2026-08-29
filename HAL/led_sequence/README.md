# LED Sequence using STM32

## Description

This project implements an LED sequence using the STM32F401RE microcontroller.

The LEDs are turned ON one by one with a delay of **500 ms** between each LED.

The sequence is:

**D1 → D2 → D3 → D4 → D5 → D6 → D7**

At any time, only one LED remains ON.

## Hardware

* STM32F401RE
* 7 LEDs (D1–D7)
* Resistors
* Push button (if used)
* Breadboard and jumper wires

## Software

* STM32CubeIDE
* STM32 HAL Library
* C programming language

## Working

The program continuously turns ON each LED one at a time. After **500 ms**, the current LED is turned OFF and the next LED is turned ON.

## File

* `main.c` — Main program containing the LED sequence logic.

## Objective

To understand GPIO configuration, GPIO output control, and delay functions using the STM32 HAL library.
