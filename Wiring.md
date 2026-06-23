

<img width="750" height="499" alt="image" src="https://github.com/user-attachments/assets/c476966f-7700-467b-a974-8fc766f9e6bc" />
## 4. Relay Module Wiring Diagram

The relay module controls the pneumatic solenoids using Arduino digital pins D5, D6, and D7.

| Relay Module Connection | Connects To        | Function                             |
| ----------------------- | ------------------ | ------------------------------------ |
| VCC                     | 5V power rail      | Relay module logic power             |
| GND                     | Ground line        | Common ground                        |
| IN1                     | Arduino D5         | Vent relay control                   |
| IN2                     | Arduino D6         | Gate relay control                   |
| IN3                     | Arduino D7         | Isolation relay control              |
| Relay 1 NC terminal     | Vent solenoid      | Vent solenoid switching contact      |
| Relay 2 NC terminal     | Gate solenoid      | Gate solenoid switching contact      |
| Relay 3 NC terminal     | Isolation solenoid | Isolation solenoid switching contact |

### Flyback Diode Protection

Each solenoid should have a flyback diode installed across the solenoid coil.

| Solenoid           | Diode Placement                                |
| ------------------ | ---------------------------------------------- |
| Vent solenoid      | Diode connected across vent solenoid coil      |
| Gate solenoid      | Diode connected across gate solenoid coil      |
| Isolation solenoid | Diode connected across isolation solenoid coil |



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
| I2C SDA            |           A4 | SDA               | Shared                                      |
| I2C SCL            |           A5 | SCL               | Shared                                      |
| USB Serial         |     USB port | `Serial`          | Communicates at 115200 baud                 |

<img width="411" height="308" alt="image" src="https://github.com/user-attachments/assets/4ee92056-6c39-4d84-969b-b0280d408e01" />
## ADS1115 Channel Mapping

| ADS1115 Channel | Connected Device        | Code Variable | Notes                 |
| --------------- | ----------------------- | ------------- | --------------------- |
| A0              | 15 psi pressure sensor  | `Pressure2`   | Low-pressure sensor   |
| A1              | Reference voltage       | `vrefValue`   | Reads Vref            |
| A2              | Potentiometer           | `potValue`    | Manual pressure input |
| A3              | 100 psi pressure sensor | `Pressure1`   | Main pressure sensor  |


<img width="588" height="276" alt="image" src="https://github.com/user-attachments/assets/4c28a15d-9e6d-4b1d-9c53-967cda5464da" />
## 5. MCP4725 DAC Wiring Diagram

The MCP4725 digital-to-analog converter is used to create the analog voltage command for the pneumatic pressure control system.

| MCP4725 Pin | Connects To          | Function                      |
| ----------- | -------------------- | ----------------------------- |
| VCC         | 5V power rail        | Powers the MCP4725 module     |
| GND         | Ground line          | Common ground reference       |
| SDA         | Arduino A4           | Shared                        |
| SCL         | Arduino A5           | Shared                        |
| OUT / Vout  | Current driver input | Analog voltage command output |

### Output Signal Purpose

The MCP4725 output is used to send a variable analog voltage command from the Arduino to the pressure control circuit.
### Notes


<img width="1128" height="894" alt="image" src="https://github.com/user-attachments/assets/695e3a51-9019-49f3-8489-06d22fe49363" />
## XTR111 Pinout

The XTR111 section converts the analog output signal from the MCP4725 into a control signal for the I/P transducer. In this setup, the MCP4725 provides the command signal, the XTR111 circuit is powered from the 24V rail, and the output goes to the pneumatic I/P transducer.

| XTR111 Label | Connects To    | Description                                                   |
| ------------ | -------------- | ------------------------------------------------------------- |
| Vin          | MCP4725 Vout   | Receives the analog voltage command signal from the MCP4725   |
| GND          | Ground line    | Common ground reference for the control circuit               |
| VCC          | 24V power rail | Supplies power to the XTR111/current control circuit          |
| Vout         | I/P transducer | Sends the control output signal to the I/P transducer         |
| GND          | Ground line    | Shared ground connection for the analog output/control signal |

### Notes

* The MCP4725 output connects to `Vin`.
* The 24V supply connects to `VCC` and homes from printer power supply.
* The I/P transducer connects to `Vout`.
* All grounds should be connected to the same ground reference.
* Ensure proper current output prior to connecting transducer.
