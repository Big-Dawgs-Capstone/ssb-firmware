// Header file for BMP581 Pressure Sensor
// Created by: 	Dylan Donahue 
// Date: 		02/06/2025

#ifndef BMP581_H
#define BMP581_H

#include "main.h"
#include "i2c.h"
#include <stdint.h>

#define BMP581_ADDRESS          0x76

// registers
#define BMP581_REG_CHIP_ID      0x01
#define BMP581_REG_ODR          0x37
#define BMP581_TEMP_XLSB        0x1D


// ODR values
#define BMP581_ODR_1HZ          0x1C
#define BMP581_ODR_2HZ          0x1B
#define BMP581_ODR_5HZ          0x18
#define BMP581_ODR_25HZ         0x14
#define BMP581_ODR_50HZ         0x0F
#define BMP581_ODR_100HZ        0x0A
#define BMP581_ODR_200HZ        0x02
#define BMP581_ODR_2400HZ       0x00

// power modes
#define BMP581_MODE_STANDBY     0b00
#define BMP581_MODE_NORMAL      0b01
#define BMP581_MODE_FORCED      0b10
#define BMP581_MODE_CONTINUOUS  0b11

// status
#define BMP581_STATUS_DRDY      0b1



I2C_HandleTypeDef* i2c;

typedef struct {

    int pressure;
    int temperature;
} bmp_data_t;

void bmp581_init(I2C_HandleTypeDef* i2c, uint8_t sample_rate);
int bmp_read_data();
void bmp581_get_pressure(uint16_t* pressure);
void bmp581_get_temperature(uint16_t* temperature);

#endif
