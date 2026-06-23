<img width="411" height="308" alt="image" src="https://github.com/user-attachments/assets/4ee92056-6c39-4d84-969b-b0280d408e01" />
ADS1115 Pinout
Vdd- 5V Power Line
Gnd- Gnd Line
SCL- Arduino SCL
SDA- Arduino SDA
A0- Sensor 2
A1-Voltage reference- 5V Power Line
A2- 10K Ohm Potentiometer
A3-Sensor 1
<img width="750" height="499" alt="image" src="https://github.com/user-attachments/assets/c476966f-7700-467b-a974-8fc766f9e6bc" />
## 4 Relay Module Wiring diagram
|Function|Pin|
|---|---|
| VCC | 5V Power Rail |
| Gnd |Gnd Line |
| IN1 |Arduino D5 |
| IN2 |Arduino D6 |
| IN3 |Arduino D7 |
| R1 Normally Closed | Vent Solenoid |
|  -Diode coming fron Gnd going into Relay |
| R2 Normally Closed | Gate Solenoid |
|  -Diode coming fron Gnd going into Relay |
| R3 Normally closed | Isolator Solenoid |
|  -Diode coming fron Gnd going into Relay |
##

<img width="750" height="422" alt="image" src="https://github.com/user-attachments/assets/535cfba7-1747-4271-842d-1eb75576e504" />
##Arduino Nano R4 Pinout
## Arduino Nano Pinout

| Function           |  Arduino Pin | Code Name         | Notes                                       |
| ------------------ | -----------: | ----------------- | ------------------------------------------- |
| Vent relay         |           D5 | `RELAY_VENT`      | Controls vent/purge relay                   |
| Gate relay         |           D6 | `RELAY_GATE`      | Controls gate relay                         |
| Isolation relay    |           D7 | `RELAY_ISO`       | Controls isolation relay                    |
| Mode switch        |           D9 | `MODE_SWITCH_PIN` | LOW = manual mode, HIGH = auto mode         |
| Plug/socket detect |          D10 | `PLUG_PIN`        | Uses internal pull-up during plug challenge |
| Status LED         | Built-in LED | `LED_PIN`         | Blinks every 250 ms                         |
| I2C SDA            |           A4 | SDA               | Shared by OLED, ADS1115, and MCP4725        |
| I2C SCL            |           A5 | SCL               | Shared by OLED, ADS1115, and MCP4725        |
| USB Serial         |     USB port | `Serial`          | Communicates at 115200 baud                 |

## ADS1115 Channel Mapping

| ADS1115 Channel | Connected Device        | Code Variable | Notes                 |
| --------------- | ----------------------- | ------------- | --------------------- |
| A0              | 15 psi pressure sensor  | `Pressure2`   | Low-pressure sensor   |
| A1              | Reference voltage       | `vrefValue`   | Reads Vref            |
| A2              | Potentiometer           | `potValue`    | Manual pressure input |
| A3              | 100 psi pressure sensor | `Pressure1`   | Main pressure sensor  |

## I2C Device Addresses

| Device               | I2C Pins |              Address | Purpose                                |
| -------------------- | -------- | -------------------: | -------------------------------------- |
| SSD1306 OLED display | A4/A5    | Default hardware I2C | Displays pressure and DAC output       |
| ADS1115 ADC          | A4/A5    |       Usually `0x48` | Reads sensors, potentiometer, and Vref |
| MCP4725 DAC          | A4/A5    |               `0x60` | Sends analog voltage command           |

<img width="588" height="276" alt="image" src="https://github.com/user-attachments/assets/4c28a15d-9e6d-4b1d-9c53-967cda5464da" />
MCP4725 Pinout

<img width="411" height="308" alt="image" src="https://github.com/user-attachments/assets/42eaab3d-0e8b-4266-a2ac-147a54756882" />
XTR111 Pinout

