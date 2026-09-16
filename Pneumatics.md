# Pneumatic System

The pneumatic system supplies and regulates pressurized air used for material extrusion. The system consists of an oil-free air compressor, pressure regulation, pressure monitoring, and electrically controlled solenoid valves.

> **System overview:**
> **Air Source → Pressure Monitoring → I/P Pressure Transducer → Pneumatic Distribution → Solenoid Valves → Syringe/Extrusion System**

## Bill of Materials

| Qty. | Component                                         | Description                                                             |
| ---: | ------------------------------------------------- | ----------------------------------------------------------------------- |
|    2 | 1/4"-27 NPT Pressure Transducer Sensors           | Pressure monitoring at the pneumatic system inlet and regulated output  |
|    1 | Syringe Barrel Valve Adapter                      | Connection between the pneumatic system and syringe barrel              |
|    2 | 1/4" NPT Male Hose Barb                           | Connection to pneumatic tubing                                          |
|    3 | 1/4" NPT Normally Closed Electric Solenoid Valves | Electrically controlled air-flow valves                                 |
|    1 | 1/4" NPT Female 4-Way Fitting                     | Main pneumatic distribution fitting                                     |
|    6 | 1/4" NPT Male Hex Nipples                         | Connections between threaded pneumatic components                       |
|    1 | 1/4" NPT Female 90° Elbow                         | Changes the direction of the pneumatic connection                       |
|    2 | 1/4" NPT Female Tees                              | Splits the pneumatic line for additional components                     |
|    1 | ControlAir Type 500X I/P Pressure Transducer      | Converts an electrical control signal into regulated pneumatic pressure |
|    1 | 1/4" NPT Male Quick-Connect Coupler               | Connection to the compressed-air supply                                 |
|    1 | Air Hose with Female Quick-Connect Couplers       | Connects the pneumatic system to the air source                         |
|    1 | Oil-Free Air Compressor                           | Pressurized air source used in this system                              |
|    1 | 1/4" NPT Low-Pressure Gauge                       | Visual monitoring of pneumatic pressure                                 |

> **Note:** Verify the pressure ratings, thread specifications, and compatibility of all pneumatic components before assembly. NPT fittings should be assembled using an appropriate pneumatic thread sealant where required.

---

## Pneumatic System Assembly

**[Insert image of completed pneumatic system here]**

The following steps describe the assembly of the pneumatic distribution system. Refer to the system image for the orientation of the fittings and valves.

### 1. Assemble the Main Distribution Fitting

Take the **1/4" NPT female 4-way fitting** and install a **1/4" NPT male hex nipple** into three of its four ports.

### 2. Install the First Pressure Sensor

Install one **pressure transducer sensor** into the remaining port of the 4-way fitting.

This sensor monitors the pressure at this section of the pneumatic system.

### 3. Install the Solenoid Valves

Thread a **normally closed electric solenoid valve** onto each of the three hex nipples installed in Step 1.

At this point, the three solenoid valves form the controlled output branches of the pneumatic distribution section.

### 4. Install the Hose Barbs

Install a **1/4" NPT male hose barb** into the output of two of the solenoid valves.

These connections provide attachment points for the pneumatic tubing.

### 5. Assemble the Third Solenoid Outlet

On the remaining solenoid valve:

1. Install a **1/4" NPT male hex nipple**.
2. Connect the **1/4" NPT female 90° elbow** to the nipple.

The elbow redirects the pneumatic line toward the downstream pressure-regulation assembly.

### 6. Connect the Elbow to a Tee

Use another **1/4" NPT male hex nipple** to connect the 90° elbow to one of the **1/4" NPT female tees**.

### 7. Connect the I/P Transducer Output

Install a **1/4" NPT male hex nipple** on the output side of the **ControlAir Type 500X I/P Pressure Transducer**.

Connect the nipple to the remaining connection on the tee assembled in Step 6.

This creates the connection between the regulated air output of the I/P transducer and the downstream pneumatic distribution system.

### 8. Install the Pressure Gauge

Install the **1/4" NPT low-pressure gauge** into the remaining port of the tee.

The gauge provides a visual indication of the pneumatic pressure in this section of the system.

### 9. Assemble the I/P Transducer Inlet

On the input side of the **ControlAir Type 500X I/P Pressure Transducer**, install a **1/4" NPT male hex nipple** and connect it to the second **1/4" NPT female tee**.

### 10. Install the Second Pressure Sensor

Install the second **pressure transducer sensor** into the branch of the tee.

This sensor monitors the pressure entering the I/P transducer.

### 11. Connect the Compressed-Air Input

Install the **1/4" NPT male quick-connect coupler** into the remaining port of the tee.

This provides the connection point for the compressed-air supply.

### 12. Connect the Air Source

Use the **air hose with female quick-connect couplers** to connect the pneumatic system to the **oil-free air compressor**.

Verify that all threaded connections are secure before supplying compressed air.

---

## Pneumatic Flow Path

Once assembled, the general air path is:

```text
## Air Flow Direction

The pneumatic system supplies compressed air to the ControlAir Type 500X,
which regulates the pressure before distributing the air to the controlled
outputs.

The general air-flow path is:

**Compressed Air Source**  
↓  
**Quick-Connect Coupler**  
↓  
**Inlet Tee / Pressure Sensor**  
↓  
**ControlAir Type 500X I/P Pressure Transducer**  
↓  
**Outlet Tee / Pressure Gauge**  
↓  
**4-Way Distribution Fitting**  
↓  
**Normally Closed Solenoid Valves**  
↓  
**Pneumatic Tubing / Syringe System**

### Pressure Monitoring

Two pressure transducers are used to monitor the pneumatic system:

- **Inlet Pressure Sensor:** Measures the pressure supplied to the
  ControlAir Type 500X.
- **Outlet Pressure Sensor:** Measures the regulated pressure after the
  ControlAir Type 500X.

A low-pressure gauge is also installed on the regulated side of the system
to provide a local visual indication of pressure.

### Pressure Regulation and Control

The **ControlAir Type 500X I/P Pressure Transducer** regulates the compressed
air according to the electrical control signal supplied by the control
system.

The three **normally closed (NC) solenoid valves** provide electrically
controlled routing of the regulated air to the pneumatic outputs. When a
solenoid is energized, its corresponding pneumatic path is opened; when
de-energized, the valve returns to its normally closed state.

> **Note:** The exact function of each solenoid output depends on the
> pneumatic connection to the syringe/extrusion assembly. Refer to the
> pneumatic assembly image and electrical wiring documentation for the
> corresponding valve connections.
```

The **ControlAir Type 500X** regulates the incoming compressed air according to its electrical control signal. The solenoid valves then provide electrically controlled routing of the regulated air to the appropriate pneumatic outputs.

---

## Final Inspection

Before operating the pneumatic system:

* Verify that all NPT fittings are fully threaded and properly sealed.
* Confirm that all tubing connections are secure.
* Verify that the solenoid valves are installed in the correct orientation.
* Confirm that the pressure sensors are connected to the intended measurement points.
* Verify that the pressure gauge is installed in the correct section of the system.
* Check that the air hose is securely connected to the compressor and pneumatic assembly.
* Slowly pressurize the system and check all connections for air leaks.
* Do not exceed the pressure rating of any component in the system.
