# CANOpen Motor Controller Simulator

A tool for simulating realistic CAN bus activity from virtual motor controllers, built for [TidalCore](https://github.com/) development and testing.

It lets you test a CANopen master (TidalCore) and control software without any physical hardware by running simulated CANopen slaves on a Linux virtual CAN interface (`vcan0`).

> [!NOTE]
> Most work is being done on the `v2` branch and its associated PR.

## How it works

- **Simulated motor controllers** are CANopen slaves built on [Lely CANopen](https://opensource.lely.com/canopen/). Each slave loads the motor controller's object dictionary from `motors.eds` and publishes data to the bus via TPDOs on each SYNC message. The object dictionary is converted from the manufacturers properitary format.
- **Master configuration** is generated with Lely's `dcfgen` from `master.yml`, which defines the PDO mapping between the master and each slave (`master.dcf`). The real configuration will be done using Servicetool.
- **External input** is received over UDP (port 5005) on a background thread and written into the slave's object dictionary. This is intended to connect to Simulink, so a virtual boat can drive the simulated motor controllers.

## Status

Done:
- Two simulated CANopen slaves (node IDs 6 and 7)
- Background thread for incoming data
- DCF generation with PDO mapping
- Dear ImGui (via HelloImGui) added to the project for GUI

Planned:
- Run 1-n simulated motor controllers from a single configuration
- Simulate latency variation found on a real CAN bus
- ImGui GUI for controlling the motor controllers and controlling bus state
- Full Simulink integration for a virtual boat
- Proper simulation of motor controller power states (shutdown, etc.)
