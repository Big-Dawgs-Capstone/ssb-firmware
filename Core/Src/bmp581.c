// Source file for BMP581 Pressure Sensor
// Created by: 	Dylan Donahue
// Date: 		02/06/2025

#include "bmp581.h"

bmp_data_t data_internal;


void bmp581_set_odr(uint8_t sample_rate) {
    uint8_t data = sample_rate << 2 | BMP581_MODE_NORMAL;
    HAL_I2C_Mem_Write(i2c, BMP581_ADDRESS, BMP581_REG_ODR, 1, &data, 1, 1000);
}

void bmp581_init(I2C_HandleTypeDef* i2c_handle, uint8_t sample_rate) {
    i2c = i2c_handle;
    bmp581_set_odr(sample_rate);
}

int bmp_read_data() {
    uint8_t data[6];
    int ret;

    ret = HAL_I2C_Mem_Read(i2c, BMP581_ADDRESS, BMP581_TEMP_XLSB, 1, data, 6, 1000);

    if (ret != HAL_OK) return ret;

    data_internal.temperature = (data[2] << 16 | data[1] << 8 | data[0]);        

    // account foe negative temperature
    if (data_internal.temperature & 0x800000) {
        data_internal.temperature |= 0xFF000000;
    }

    data_internal.pressure = (data[5] << 16 | data[4] << 8 | data[3]);

    return 0;
}

void bmp581_get_pressure(uint16_t* pressure) {
    *pressure = data_internal.pressure;
}

void bmp581_get_temperature(uint16_t* temperature) {
    *temperature = data_internal.temperature;
}



