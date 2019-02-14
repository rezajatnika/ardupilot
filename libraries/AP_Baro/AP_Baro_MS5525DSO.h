/**
 * Written by Reza Jatnika <rezajatnika@gmail.com>
 * 2019-02-14 15:00
 */

#pragma once

#include "AP_Baro_Backend.h"

#include <AP_HAL/AP_HAL.h>
#include <AP_HAL/Semaphores.h>
#include <AP_HAL/Device.h>


// MS5525 Commands structure.
#define MS5525_RESET               0x1E

#define MS5525_CONVERT_D1_OSR_256  0x40
#define MS5525_CONVERT_D1_OSR_512  0x42
#define MS5525_CONVERT_D1_OSR_1024 0x44
#define MS5525_CONVERT_D1_OSR_2048 0x46
#define MS5525_CONVERT_D1_OSR_4096 0x48

#define MS5525_CONVERT_D2_OSR_256  0x50
#define MS5525_CONVERT_D2_OSR_512  0x52
#define MS5525_CONVERT_D2_OSR_1024 0x54
#define MS5525_CONVERT_D2_OSR_2048 0x56
#define MS5525_CONVERT_D2_OSR_4096 0x58

#define MS5525_ADC_READ            0x00
#define MS5525_PROM_READ_BASE      0xA0

// MS5525 I2C address.
#define MS5525_I2C_ADDR_1          0x76
#define MS5525_I2C_ADDR_2          0x77

// We are going to use 1024 oversampling.
// This should be fast enough to reduce noise.
#define MS5525_CONVERT_PRESSURE    MS5525_CONVERT_D1_OSR_1024
#define MS5525_CONVERT_TEMPERATURE MS5525_CONVERT_D2_OSR_1024

class AP_Baro_MS5525DSO : public AP_Baro_Backend
{
public:
    void update() override;

    bool get_differential_pressure(float &pressure);
    bool get_temperature(float &temperature);

private:
    bool _init();
    bool _read_adc();
    bool _read_prom();

    void _calculate();
    void _timer(); 

    uint16_t _crc4_prom();
}
