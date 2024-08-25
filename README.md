# ESP32 Bluetooth Master

This repository contains the code for the Master ESP32 device, which establishes a Bluetooth connection with a Slave ESP32 device. The Master sends JSON-formatted commands to the Slave to control various GPIO pins, allowing for remote control of connected devices such as LEDs and relays.

## Features

- **Bluetooth Communication:** The Master ESP32 initiates a Bluetooth connection with the Slave device.
- **JSON Data Exchange:** Sends commands in JSON format for easy data manipulation.
- **GPIO Control:** The Master can send commands to control GPIO pins on the Slave device.
- **Button Integration:** Buttons connected to the Master ESP32 can toggle GPIO pins on the Slave.

## Hardware Requirements

- One ESP32 development board (Master)
- Buttons (optional, for GPIO control)

## Software Requirements

- Arduino IDE with ESP32 board support
- ArduinoJson library
- BluetoothSerial library (built-in with ESP32 Arduino core)

## Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/MagicBulletPro/esp32-bluetooth-master.git
cd esp32-bluetooth-master
```

## Upload the Code
- Open the esp32-bluetooth-master-slave.ino file in the Arduino IDE.
- Ensure you have selected the correct ESP32 board and port under Tools > Board and Tools > Port.
Upload the code to both ESP32 boards.
## Circuit Setup
Connect buttons to the GPIO pins as defined in the code.
Ensure all peripherals are properly connected for GPIO control.

## Run the Project
- Power up both ESP32 boards.
- The Master ESP32 will automatically try to connect to the Slave ESP32.
- Once connected, the Master can send JSON commands to the Slave to control the connected devices.
## Example JSON Command
The Master device sends commands in JSON format to the Slave device. An example of a JSON command is:
```
{
  "pin_number": 4,
  "pin_status": true
}
```
This command instructs the Slave device to set GPIO pin 2 to HIGH.
## Contributing
Contributions are welcome! Please fork this repository and submit a pull request with your enhancements.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

