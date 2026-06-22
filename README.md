# Cost-Effective-Bio-3D-Printer
This project focused on designing a 3D bio-printer that performs at the same level at those on the market at a fraction of the price point, the printer was be built, tested, and refined based on tests. Using knowledge obtained from literature reviewed as well as knowledge from previous work on customizing FDM printers.


This repository documents the design, construction, firmware, calibration, and testing of a low-cost pneumatic extrusion bio-3D printer platform developed for research involving in-place Video Vibrometry Analysis (VVA).

The goal of this project is to allow other researchers and students to replicate a modular bio-3D printer system using a modified FDM printer, pneumatic syringe extrusion, pressure sensing, and microcontroller-based control.

## Project Overview

Traditional bio-3D printing platforms can be expensive and difficult to modify for experimental research. This project modifies a conventional 3D printer platform into a pneumatic extrusion system capable of depositing gel-like materials while supporting in-place VVA testing.

The system includes:

- Modified FDM printer frame/platform
- Pneumatic syringe extrusion system
- ControlAir Type 500-X I/P transducer
- Arduino Nano-based control system
- MCP4725 DAC for analog pressure command output
- ADS1115 ADC for pressure sensor and reference voltage readings
- LCD I2C 20x4 display
- Relay-controlled purge and isolation solenoids
- Pressure sensors for monitoring pneumatic output
- Manual and automatic control modes

## Research Motivation

Organ shortages remain a major biomedical challenge. Bio-3D printing has the potential to support tissue engineering research, but print quality and defect detection remain important problems. Video Vibrometry Analysis can help identify defects, but moving samples after printing may introduce error. This project supports in-place VVA testing by integrating a low-cost extrusion platform with pressure monitoring and control.

## System Architecture

The system is divided into four main subsystems:

1. **Mechanical system**  
   Modified printer frame, syringe mount, pneumatic tubing, and extrusion hardware.

2. **Pneumatic system**  
   Pressure regulator, I/P transducer, solenoid valves, syringe, and air supply.

3. **Electronics system**  
   Arduino Nano, ADS1115, MCP4725, LCD, relays, pressure sensors, and power regulation.

4. **Firmware/control system**  
   Manual and automatic pressure control, sensor polling, LCD display, DAC output, and safety checks.

## Hardware Used

| Component | Purpose |
|---|---|
| Modified FDM 3D printer | Motion platform |
| Arduino Nano | Main external pressure controller |
| ADS1115 | Reads pressure sensors, potentiometer, and reference voltage |
| MCP4725 | Outputs analog voltage command |
| ControlAir Type 500-X I/P transducer | Converts electrical signal to pneumatic pressure |
| 20x4 I2C LCD | Displays pressure, DAC voltage, and mode |
| Relay module | Controls purge and isolation solenoids |
| Pressure sensors | Monitor pneumatic pressure |
| Syringe extrusion system | Deposits bioink/gel material |

## Pinout Summary

| Function | Arduino Pin / Channel |
|---|---|
| SoftwareSerial RX | D2 |
| SoftwareSerial TX | D3 |
| Mode switch | D9 |
| Plug/socket detect | D10 |
| Purge relay | D11 |
| Isolation relay | D12 |
| Status LED | Built-in LED |
| Sensor 1, 100 psi | ADS1115 A3 |
| Sensor 2, 15 psi | ADS1115 A0 |
| Potentiometer/variator | ADS1115 A2 |
| Reference voltage | ADS1115 A1 |
| LCD I2C address | 0x27 |
| MCP4725 DAC address | 0x60 |

## Firmware Features

- Manual pressure control using potentiometer input
- Automatic control using ratio-based input
- Continuous ADS1115 sensor polling
- Pressure display for two sensors
- DAC output for 4–20 mA control through external current driver
- Plug/socket validation
- LCD status display
- Relay control for pneumatic purge and isolation

## Repository Contents

```text
firmware/   Arduino and printer firmware notes
hardware/   BOM, wiring diagrams, CAD, and schematics
docs/       Assembly, calibration, operation, and troubleshooting guides
images/     Photos and diagrams of the completed system
data/       Example pressure logs and test data
research/   Abstract, project summary, and references
