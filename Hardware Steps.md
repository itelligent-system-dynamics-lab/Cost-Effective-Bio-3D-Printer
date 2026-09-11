# Replication Steps

## Overview

1. Build or modify the printer frame.
2. Install the syringe extrusion mount.
3. Assemble the pneumatic system.
4. Wire the Arduino Nano controller.
5. Connect the ADS1115, MCP4725, LCD, relays, and sensors.
6. Update the printer and Arduino firmware.
7. Calibrate the pressure sensors.
8. Test solenoid operation.
9. Run low-pressure extrusion tests.

> **See `README.md` for required components.**

---

## 1. Assemble Printer

- Ensure the printer functions as intended **before making any modifications**.
- Confirm that all motion axes move correctly.
- Remove filament extrusion components, including:
  - Extruder motor
  - Hotend

### Sovol SV08

For the Sovol SV08, the following components will need to remain installed:

- Extruder control board
- Eddy-current probe

Modify the Klipper firmware and remove/comment out control of the following components to avoid errors while printing:

- Hotend
- Heated bed
- Extruder motor

### Initial Printer Test

Before installing the new extrusion system:

1. Test the printer without the extrusion components.
2. Run a complete print from start to finish.
3. Confirm that all motion axes operate correctly.
4. Verify that no errors occur during the entire print.

---

## 2. Install Syringe Mount

- Use the provided STL file to 3D print a new mount for:
  - 10 mL syringe
  - Eddy-current probe
- Install the new mount on the existing printer carriage.
- Connect the pneumatic tubing using the appropriate barrel adapter.
- See [`Pneumatics.md`](Pneumatics.md) for the rest of the pneumatic setup.

---

## 3. Assemble Electronics

See [`README.md`](README.md) for the required components.

See [`Wiring.md`](Wiring.md) for:

- Arduino Nano R4 pinout
- Electronics wiring instructions
- Sensor connections
- Peripheral connections

The electronics system includes:

- Arduino Nano R4
- ADS1115
- MCP4725
- LCD
- Relays
- Pressure sensors
- Other required sensors and control components

---

## 4. Assemble Control Panel

- 3D print the control-panel mount using the provided STL file.
- Mount the control panel in the same position as the existing printer screen.
- The left side of the mount is for the existing display.
- The right side of the mount is for an interchangeable control panel.

### Interchangeable Control Panel

The provided interchangeable panel supports:

- 0.96-inch OLED display
- Toggle switch
- Potentiometer

Install the desired control-panel configuration and connect the components according to [`Wiring.md`](Wiring.md).

---

## 5. Assemble Pneumatic System

See [`Pneumatics.md`](Pneumatics.md) for detailed instructions on assembling the pneumatic system.

The pneumatic system includes:

- Pneumatic tubing
- Barrel adapter
- Pressure regulation components
- Solenoids
- Syringe connections
- Pressure sensors

Verify all pneumatic connections before applying pressure to the system.

---

## 6. Update Firmware

### Printer Firmware

- Modify the Klipper configuration as required.
- Remove or comment out control of the components that have been removed from the printer.
- Verify that the printer can complete a motion-only print without errors.

### Arduino Firmware

- Upload the provided Arduino firmware.
- Verify communication with all connected sensors and peripherals.
- Confirm that the display and control inputs operate correctly.

---

## 7. Calibration and Testing

### Pressure Sensor Calibration

1. Connect the pressure sensors.
2. Verify that the Arduino receives pressure readings.
3. Calibrate the pressure sensors according to the provided calibration procedure.
4. Confirm that the measured pressure corresponds to the applied pressure.

### Solenoid Test

1. Verify all pneumatic connections.
2. Power the pneumatic system.
3. Activate each solenoid individually.
4. Confirm that each solenoid opens and closes correctly.
5. Check the pneumatic system for air leaks.

### Low-Pressure Extrusion Test

1. Load the syringe with the desired extrusion material.
2. Verify that the syringe and pneumatic connections are secure.
3. Begin with low pressure.
4. Activate the extrusion system.
5. Verify consistent material flow.
6. Monitor the pressure sensors throughout the test.
7. Gradually increase pressure only after confirming that the system operates correctly.

---

## Related Documentation

- [`README.md`](README.md) — Required components and project overview
- [`Pneumatics.md`](Pneumatics.md) — Pneumatic system assembly
- [`Wiring.md`](Wiring.md) — Electronics wiring and Arduino Nano R4 pinout
