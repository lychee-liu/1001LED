#include "main.h"
#include "motor.h"
//#include "algorithm.h"

float linearMapping(int16_t in, int16_t in_min, int16_t in_max, float out_min, float out_max) {
    float result = float(out_min + (out_max - out_min) * (in - in_min) / (in_max - in_min));
    return result;
}

void M3508_Motor::canRxMsgCallback(const uint8_t rx_data[8]) {
    last_ecd_angle_ = ecd_angle_;
    int16_t ecd_angle = (rx_data[0] << 8) | rx_data[1];
    ecd_angle_ = linearMapping(ecd_angle, 0, 8191, 0.0, 360.0);
    delta_ecd_angle_ = float(ecd_angle_ - last_ecd_angle_);
    if (delta_ecd_angle_ > 180)
        delta_ecd_angle_ -= 360;
    else if (delta_ecd_angle_ < -180)
        delta_ecd_angle_ += 360;
    rotate_speed_ = (rx_data[2] << 8) | rx_data[3];
    int16_t current = (rx_data[4] << 8) | rx_data[5];
    current_ = linearMapping(current, -16384, 16384, -20.0, 20.0);
    temp_ = rx_data[6];

    delta_angle_ = delta_ecd_angle_ / ratio_;
    angle_ += delta_angle_;
}

M3508_Motor Motor(3591.0f / 187.0f);