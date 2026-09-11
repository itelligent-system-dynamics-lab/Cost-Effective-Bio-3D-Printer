Replication Steps
Overview
Build or modify the printer frame.
Install the syringe extrusion mount.
Assemble the pneumatic system.
Wire the Arduino Nano controller.
Connect the ADS1115, MCP4725, LCD, relays, and sensors.
Update the printer and Arduino firmware.
Calibrate the pressure sensors.
Test solenoid operation.
Run low-pressure extrusion tests.

See README.md for the required components.

1. Assemble Printer
Ensure the printer functions as intended before making any modifications.
Confirm that all motion axes move correctly.
Remove filament-extrusion components, including:
Extruder motor
Hotend
For the Sovol SV08, the following components must remain installed:
Extruder control board
Eddy-current probe
Modify the Klipper firmware to remove or comment out control of the following components:
Hotend
Heated bed
Extruder motor
This prevents firmware errors while printing.
Initial Printer Test

Before installing the new extrusion system:

Test the printer without the extrusion components.
Run a complete print from start to finish.
Confirm that all motion axes operate correctly.
Verify that no firmware or printer errors occur during the print.
2. Install Syringe Mount
Use the provided STL file to 3D print a new mount designed for:
10 mL syringe
Eddy-current probe
Install the new mount on the existing printer carriage.
Connect the pneumatic tubing using the appropriate barrel adapter.
Refer to Pneumatics.md for the complete pneumatic system setup.
3. Assemble Electronics

Refer to the following documentation:

README.md — Required components
Wiring.md — Electronics wiring and connections

The electronics system includes:

Arduino Nano R4
ADS1115
MCP4725
LCD
Relays
Pressure sensors
Other required sensors and control components

See Wiring.md for the Arduino Nano R4 pinout and detailed wiring instructions.

4. Assemble Control Panel
3D print the control-panel mount using the provided STL file.
Install the control-panel mount in the same position as the printer's existing display.
The mount is divided into two sections:
Left side: Existing printer display
Right side: Interchangeable control panel
Interchangeable Control Panel

The provided interchangeable panel supports:

0.96-inch OLED display
Toggle switch
Potentiometer

Install the desired control-panel configuration and connect the components according to Wiring.md.

5. Assemble Pneumatic System

Refer to Pneumatics.md for detailed instructions on:

Pneumatic tubing
Barrel adapters
Pressure regulation
Solenoid installation
Syringe connections
Pneumatic system testing
6. Firmware

Update the printer and Arduino firmware after completing the hardware installation.

Printer Firmware
Modify the Klipper configuration as required.
Ensure control of the removed extrusion components is disabled.
Verify that the printer can complete a motion-only print without errors.
Arduino Firmware
Upload the provided Arduino firmware.
Verify communication with connected sensors and peripherals.
Confirm that the LCD/OLED and control inputs operate correctly.
7. Calibration and Testing

Complete the following tests before attempting full-pressure extrusion:

Pressure Sensor Calibration
Connect the pressure sensors.
Verify sensor readings through the Arduino controller.
Calibrate the sensors according to the provided calibration procedure.
Confirm that the measured pressure corresponds to the applied pressure.
Solenoid Test
Verify all pneumatic connections.
Power the pneumatic system.
Activate each solenoid individually.
Confirm that each solenoid opens and closes correctly.
Check the system for air leaks.
Low-Pressure Extrusion Test
Load the syringe with the desired extrusion material.
Verify that the syringe and pneumatic connections are secure.
Begin with low pressure.
Activate the extrusion system.
Verify consistent material flow.
Monitor the pressure sensors throughout the test.
Gradually increase pressure only after confirming that the system operates correctly.
Related Documentation
README.md — Required components and project overview
Pneumatics.md — Pneumatic system assembly
Wiring.md — Electronics wiring and Arduino Nano R4 pinout
