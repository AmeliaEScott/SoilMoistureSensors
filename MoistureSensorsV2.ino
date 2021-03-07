#include <TinyWire.h>

constexpr byte I2C_ADDR = 0x3F;

constexpr byte I2C_CMD_SENSORS_ON = 0x01;
constexpr byte I2C_CMD_SENSORS_READ = 0x02;
constexpr byte I2C_CMD_SENSORS_OFF = 0x03;

constexpr int SENSOR_POWER_PIN = 4;
constexpr int SENSOR_1_PIN = 1;
constexpr int SENSOR_2_PIN = 3;

int sensorBuffer[2] = {1234, 5678};

byte i2cCommand = 0x00;

void setup() {
    pinMode(SENSOR_POWER_PIN, OUTPUT);
    TinyWire.begin(I2C_ADDR);
    TinyWire.onReceive(onI2CReceive);
    TinyWire.onRequest(onI2CRequest);
}

void loop() {
    if(i2cCommand == I2C_CMD_SENSORS_ON) {
        digitalWrite(SENSOR_POWER_PIN, HIGH);
        i2cCommand = 0x00;
    } else if (i2cCommand == I2C_CMD_SENSORS_OFF) {
        digitalWrite(SENSOR_POWER_PIN, LOW);
        i2cCommand = 0x00;
    } else if (i2cCommand == I2C_CMD_SENSORS_READ) {
        sensorBuffer[0] = analogRead(SENSOR_1_PIN);
        sensorBuffer[1] = analogRead(SENSOR_2_PIN);
        i2cCommand = 0x00;
    }

}

void onI2CReceive(int count) {
    while(TinyWire.available() > 0) {
        i2cCommand = TinyWire.read();
    }
}

void onI2CRequest() {
    TinyWire.send((uint8_t *) sensorBuffer, sizeof(sensorBuffer));
}
