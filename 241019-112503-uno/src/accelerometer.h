#include <Wire.h>

#define GSCALE_FACTOR    16384.0 // +- 2g scale factor
#define TEMP_DATA_ADDR   0x41    // temperate data address
#define ACCELX_DATA_ADDR 0x3B    // Register for accelerometer X data
#define I2C_PERIPHERAL   0X68    // i2c peripheral addr
#define GYRO_DATA_ADDR   0x43    // Register for gyro data
#define MAG_DATA_ADDR    0x03    // register for mag x data
#define MAG_DATA_Y       0x05    // register for mag y data
#define MAG_DATA_Z       0x07    // register for mag z data
#define MAGX_DATA_SENS   0x10    // register for magx sensistivity data
#define MAGY_DATA_SENS   0x11    // register for magx sensistivity data
#define MAGZ_DATA_SENS   0x12    // register for magx sensistivity data
#define RCV_6_BYTES      6       // receive 6 bytes
#define NUM_MAG_BYTEST   2       // 2 bytes: X, Y, Z data for Magnetometer
#define SDA              A4      // not used mostly reference bc im dumb 
#define SCL              A5      // not used mostly reference bc im dumb
#define C_TO_F(C)       (C * 1.80 + 32.0)

typedef struct mpu2950_data_s
{
    double accelx_g;
    double accely_g;
    double accelz_g;
    double gyrox;
    double gyroy;
    double gyroz;
    double temperature_c;
    double pitch_radians;
    double pitch_degrees;
    double roll_radians;
    double roll_degrees;
    double yaw_radians;
    double yaw_degrees;
    double magx_data_raw;
    double magy_data_raw;
    double magz_data_raw;
    double magx_adjusted_val;
    double magy_adjusted_val;
    double magz_adjusted_val;
} mpu9250_data_t;

void get_mag_data(int addr, int num_bytes);
void get_gryo_data(int addr, int num_bytes);
void get_temperature_data(int addr, int num_bytes);
void get_accelerometer_data(int addr, int num_bytes);