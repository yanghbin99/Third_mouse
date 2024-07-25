#pragma once

#include "Control/Move.h"
#include "Sensor/Encoder.h"
#include "Sensor/IRSensor.h"
#include "Interface/HCMSDisplay.h"

#include "stm32g4xx_hal.h"

namespace Device {
    extern Encoder* rEncoder;
    extern Encoder* lEncoder;

    extern IRSensor* sensor;

    extern Move* motor;

    extern OLED* display;
}