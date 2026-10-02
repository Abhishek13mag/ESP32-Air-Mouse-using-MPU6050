#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <BleMouse.h>

Adafruit_MPU6050 mpu;
BleMouse bleMouse("ESP32 Air Mouse", "Espressif", 100);

// Buttons
#define LEFT_BUTTON_PIN   4
#define RIGHT_BUTTON_PIN  5

// Tuning Parameters
const float DEADZONE = 0.08;   // rad/s below which movement is ignored
const float SENSITIVITY = 12.0; // Multiplier for cursor speed

// Gyro calibration offsets
float gyroX_offset = 0;
float gyroZ_offset = 0;

void calibrateGyro() {
  Serial.println("Calibrating gyro... Keep device still on a flat surface.");
  const int samples = 200;
  float sumX = 0, sumZ = 0;

  for (int i = 0; i < samples; i++) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    sumX += g.gyro.x;
    sumZ += g.gyro.z;
    delay(10);
  }

  gyroX_offset = sumX / samples;
  gyroZ_offset = sumZ / samples;
  Serial.println("Calibration complete!");
}

void setup() {
  Serial.begin(115200);

  pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);

  Wire.begin(21, 22);

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050!");
    while (1) delay(10);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(500);
  calibrateGyro();

  bleMouse.begin();
  Serial.println("BLE Mouse started. Pair your device via Bluetooth!");
}

void loop() {
  if (bleMouse.isConnected()) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Remove baseline offsets
    float rawRateX = g.gyro.x - gyroX_offset; // Tilt Pitch (Up/Down)
    float rawRateZ = g.gyro.z - gyroZ_offset; // Yaw/Turn (Left/Right)

    int8_t moveX = 0;
    int8_t moveY = 0;

    // Apply deadzone and scaling
    // Note: Invert sign (-) if axes feel mirrored for your mounting orientation
    if (abs(rawRateZ) > DEADZONE) {
      moveX = (int8_t)(-rawRateZ * SENSITIVITY);
    }
    if (abs(rawRateX) > DEADZONE) {
      moveY = (int8_t)(-rawRateX * SENSITIVITY);
    }

    // Move cursor if above threshold
    if (moveX != 0 || moveY != 0) {
      bleMouse.move(moveX, moveY);
    }

    // Handle Left Click
    if (digitalRead(LEFT_BUTTON_PIN) == LOW) {
      if (!bleMouse.isPressed(MOUSE_LEFT)) {
        bleMouse.press(MOUSE_LEFT);
      }
    } else {
      if (bleMouse.isPressed(MOUSE_LEFT)) {
        bleMouse.release(MOUSE_LEFT);
      }
    }

    // Handle Right Click
    if (digitalRead(RIGHT_BUTTON_PIN) == LOW) {
      if (!bleMouse.isPressed(MOUSE_RIGHT)) {
        bleMouse.press(MOUSE_RIGHT);
      }
    } else {
      if (bleMouse.isPressed(MOUSE_RIGHT)) {
        bleMouse.release(MOUSE_RIGHT);
      }
    }

    delay(10); // ~100 Hz report rate for smooth tracking
  } else {
    delay(50);
  }
}
