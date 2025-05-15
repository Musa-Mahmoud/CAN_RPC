# CAN_RPC
A CAN Bus LED Control with Remote Data Request.

## Overview
This project demonstrates CAN bus communication between two nodes (N1 (i.e., STM32F446) and N2 (i.e., STM32F103)) using STM32 microcontrollers. The system includes:
- **N1** sending an LED number via a CAN Data Frame every second.
- **N2** lighting the corresponding LED upon receiving the message.
- **N1** requesting 2 bytes of data from N2 using a Remote Frame at a configurable interval (`4` seconds).
- **N2** responding with the requested data via a CAN Data Frame.
- **Interrupt-driven code** triggered by a user button press on the STM32 Nucleo board.

## Requirements
### Hardware
- 2 STM32 boards (e.g., NUCLEO-F446RE, Blue Pill).
- 2 CAN transceivers (e.g., CJMCU-230).
- LEDs and resistors (for N2).
- Jumper wires for connections.

### Software
- STM32CubeIDE.

## Hardware Setup
1. **CAN Bus Wiring**:
   - Connect `CAN_H` and `CAN_L` pins between nodes using transceivers.

2. **Node Configurations**:
   - **N1 (Transmitter/Requester)**:
     - Uses the **built-in user button** to start the application.
   - **N2 (Receiver/Responder)**:
     - Connect LEDs to GPIO pins (e.g., GPIOA pins 0-7 for 8 LEDs).

## Software Setup
1. Clone the repository:
   ```bash
   git clone https://github.com/Musa-Mahmoud/CAN_RPC
   ```
2. Import the N1 and N2 projects into STM32CubeIDE.
3. Build and flash the code to the respective boards.