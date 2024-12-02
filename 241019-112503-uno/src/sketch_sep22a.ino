#include "Arduino.h"
#include "accelerometer.h"
#include "IRremote.hpp"
#include <Wire.h>

// Declare the accelerometer data structure
mpu9250_data_t *imu_data = new mpu9250_data_t;

void setup(void)
{ 
    Wire.begin();       // Start the I2C communication
    Serial.begin(9600); // Start serial communication for debugging
}

void loop()
{
    // Get accelerometer data
    get_accelerometer_data(I2C_PERIPHERAL, NUM_ACCEL_BYTES);  // Use 0x68 for the I2C address of MPU9250 if AD0 is connected to GND
    get_gryo_data(I2C_PERIPHERAL, 6);

    Serial.print("Pitch Data: ");
    Serial.println(imu_data->pitch_degrees);

    Serial.print("Roll Data: ");
    Serial.println(imu_data->roll_degrees);

   delay(500); //a delay to avoid flooding the serial monitor
}

void get_accelerometer_data(int addr, int num_bytes)
{
    Wire.beginTransmission(addr);
    Wire.write(ACCELX_DATA_ADDR);         // Specify the register to start reading from (0x3B)
    Wire.endTransmission(false);

    Wire.requestFrom(addr, num_bytes);  // Request the number of bytes from the device
    
    if (Wire.available() == num_bytes)
    {
        // Read 2 bytes for each axis and combine them (high byte + low byte)
        imu_data->accelx_g = (((Wire.read() << 8) | Wire.read()) / GSCALE_FACTOR);  // Combine high and low bytes for X-axis
        imu_data->accely_g = (((Wire.read() << 8) | Wire.read()) / GSCALE_FACTOR);  // Combine high and low bytes for Y-axis
        imu_data->accelz_g = (((Wire.read() << 8) | Wire.read()) / GSCALE_FACTOR);  // Combine high and low bytes for Z-axis
    }

    // raw data to radians
    imu_data->pitch_radians = atan2((imu_data->accelx_g * -1), sqrt(square(imu_data->accely_g) + square(imu_data->accelz_g)));
    // radians to degrees -> pitch
    imu_data->pitch_degrees = (imu_data->pitch_radians * (180 / PI));
    // raw data to roll radians
    imu_data->roll_radians = atan2(imu_data->accely_g, imu_data->accelz_g);
    // roll radians to degrees
    imu_data->roll_degrees = (imu_data->roll_radians * (180 / PI));
}

void get_temperature_data(int addr, int num_bytes)
{
    Wire.beginTransmission(addr);
    Wire.write(TEMP_DATA_ADDR);
    Wire.endTransmission(false);

    Wire.requestFrom(addr, num_bytes);

    // convert the raw data to celcius
    if (Wire.available() == num_bytes)
    {
        imu_data->temperature_c = (((Wire.read() << 8 | Wire.read()) / 333.87) + 21);
    }
}

void get_gryo_data(int addr, int num_bytes)
{
    Wire.beginTransmission(I2C_PERIPHERAL);
    Wire.write(GYRO_DATA_ADDR);
    Wire.endTransmission(false);

    Wire.requestFrom(addr, num_bytes);

    if (Wire.available() == num_bytes)
    {
        imu_data->gyrox = ((Wire.read() << 8 | Wire.read()) / 131.0);
        imu_data->gyroy = ((Wire.read() << 8 | Wire.read()) / 131.0);
        imu_data->gyroz = ((Wire.read() << 8 | Wire.read()) / 131.0);
    }
}

void get_mag_sense_data(void)
{
    // these will always be static
    Wire.beginTransmission(I2C_PERIPHERAL);
    Wire.write(MAGX_DATA_SENS);
    Wire.endTransmission(false);

    
}

void get_mag_data(int addr, int num_bytes)
{
    Wire.beginTransmission(I2C_PERIPHERAL);
    Wire.write(MAGX_DATA_SENS);2
    Wire.endTransmission(false);

    // get data from the calibration register first
    Wire.requestFrom(, num_bytes);


    if (Wire.available() == num_bytes)
    {
        imu_data->magx_data_raw = (Wire.read() << 8 | Wire.read()) 
    }
}







