#include "Device.h"

namespace Device {
    
    Encoder* rEncoder = nullptr;
    Encoder* lEncoder = nullptr;

    IRSensor* sensor = nullptr;

    Move* motor = nullptr;

    OLED* display = nullptr;

    uint32_t irq_count = 0;
}