# ESP32 Air Mouse using MPU6050

## 📌 Project Overview

The **ESP32 Air Mouse** is a wireless motion-controlled mouse that allows users to control a computer cursor through hand movements without using a conventional physical mouse.

The project uses an **ESP32 microcontroller**, an **MPU6050 accelerometer and gyroscope**, and Bluetooth Low Energy (BLE) HID functionality to convert hand movements into cursor movements.

By tilting or rotating the device, users can move the cursor on a connected computer. Two push buttons are implemented for left and right mouse clicks.

## 🎯 Features

* Wireless mouse functionality using Bluetooth Low Energy (BLE).
* Motion-based cursor control using the MPU6050 gyroscope.
* Left-click and right-click functionality.
* Gyroscope calibration to compensate for sensor bias.
* Deadzone filtering to reduce unwanted cursor movement.
* Adjustable cursor sensitivity.
* Approximately 100 Hz mouse update rate.

## 🛠️ Hardware Requirements

| Component                         |    Quantity |
| --------------------------------- | ----------: |
| ESP32 Development Board           |           1 |
| MPU6050 Accelerometer & Gyroscope |           1 |
| Push Buttons                      |           2 |
| Jumper Wires                      | As required |
| USB Cable                         |           1 |

## 🔌 Circuit Connections

### MPU6050 to ESP32

| MPU6050 Pin | ESP32 Pin |
| ----------- | --------- |
| VCC         | 3.3V      |
| GND         | GND       |
| SDA         | GPIO 21   |
| SCL         | GPIO 22   |

### Push Button Connections

| Button      | ESP32 GPIO |
| ----------- | ---------- |
| Left Click  | GPIO 4     |
| Right Click | GPIO 5     |

**Note:** The push buttons are connected between their respective GPIO pins and GND. The code uses the ESP32's internal pull-up resistors (`INPUT_PULLUP`).

## 💻 Software Requirements

* Arduino IDE
* ESP32 Board Package
* Adafruit MPU6050 Library
* Adafruit Unified Sensor Library
* Adafruit BusIO Library
* BleMouse Library

### Required Libraries

Install the following libraries through Arduino IDE Library Manager where available:

1. Adafruit MPU6050
2. Adafruit Unified Sensor
3. Adafruit BusIO
4. ESP32 BLE Mouse

## ⚙️ Working Principle

The project works by converting the rotational movement of the user's hand into Bluetooth mouse movement.

**Step 1: Sensor Initialization**

The ESP32 communicates with the MPU6050 through the I2C protocol using SDA and SCL pins.

**Step 2: Gyroscope Calibration**

During startup, the device collects 200 gyroscope samples while stationary. The average readings are calculated and stored as calibration offsets.

**Step 3: Motion Detection**

The MPU6050 measures angular velocity along the X and Z axes.

* X-axis gyroscope data is used for vertical cursor movement.
* Z-axis gyroscope data is used for horizontal cursor movement.

**Step 4: Noise Filtering**

A deadzone of 0.08 rad/s is implemented to ignore small unwanted sensor movements.

**Step 5: Cursor Movement**

The filtered gyroscope readings are multiplied by a sensitivity factor and converted into mouse movement commands.

**Step 6: Bluetooth Communication**

The ESP32 sends mouse movement and button press/release commands to the paired computer through BLE HID functionality.

## 🧠 Algorithm

```text
START
  |
Initialize Serial Communication
  |
Initialize I2C and MPU6050
  |
Configure Accelerometer and Gyroscope
  |
Calibrate Gyroscope
  |
Initialize BLE Mouse
  |
Check Bluetooth Connection
  |
Read MPU6050 Sensor Data
  |
Subtract Calibration Offsets
  |
Apply Deadzone Filtering
  |
Calculate Cursor X and Y Movement
  |
Send BLE Mouse Movement
  |
Read Left and Right Button States
  |
Send Mouse Click Commands
  |
Repeat
```

## 🎛️ Configurable Parameters

The following parameters can be modified to adjust cursor behaviour.

| Parameter     | Default Value | Description                                            |
| ------------- | ------------: | ------------------------------------------------------ |
| `DEADZONE`    |          0.08 | Minimum angular velocity required for movement (rad/s) |
| `SENSITIVITY` |          12.0 | Cursor movement multiplier                             |
| `samples`     |           200 | Number of samples used for calibration                 |
| `delay(10)`   |         10 ms | Mouse update interval                                  |

### Customization

* Increase `SENSITIVITY` for faster cursor movement.
* Decrease `SENSITIVITY` for slower cursor movement.
* Increase `DEADZONE` to reduce unwanted cursor movements.
* Change the movement signs if the cursor direction is inverted due to sensor orientation.

## 🚀 How to Upload and Use

1. Connect the ESP32 to your computer using a USB cable.
2. Open the Arduino IDE.
3. Install all the required libraries.
4. Select the appropriate ESP32 board and COM port.
5. Upload the Arduino sketch.
6. Open the Serial Monitor at 115200 baud.
7. Keep the device stationary during gyroscope calibration.
8. Enable Bluetooth on your computer.
9. Search for the device named **ESP32 Air Mouse**.
10. Pair and connect the device.
11. Move the ESP32 to control the cursor.
12. Use the two push buttons for left and right clicks.

## 📚 Technologies Used

* Embedded C/C++
* ESP32 Microcontroller
* MPU6050 Motion Sensor
* I2C Communication Protocol
* Bluetooth Low Energy (BLE)
* Human Interface Device (HID) Protocol
* Arduino IDE

## 🔮 Future Improvements

* Implement accelerometer and gyroscope sensor fusion.
* Add advanced noise filtering for improved cursor stability.
* Implement adjustable sensitivity through button combinations.
* Add scroll functionality.
* Develop a rechargeable and compact PCB-based design.
* Improve cursor control using orientation estimation.

## 👨‍💻 Author

**Abhishek A Nair**

B.Tech – Electronics and Communication Engineering

GitHub: [Abhishek13mag](https://github.com/Abhishek13mag)

---

⭐ If you find this project interesting, consider giving the repository a star!
