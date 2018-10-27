#ifndef ECU_UTILS_H
#define ECU_UTILS_H

#include <stdint.h>

#include "constants.h"

#define PERCENT_TO_RANGE(percent,min,max) ((percent * (max - min)) + min)

float get_ecu(int pin) {
    unsigned long total_pulse_len = 0;
    for (int i = 0; i < ECU_PULSES_TO_SAMPLE; i++) {
        total_pulse_len += pulseIn(pin, LOW, ECU_PULSE_TIMEOUT);
    }
    unsigned long normalized_pulse_len = total_pulse_len / ECU_PULSES_TO_SAMPLE;
    normalized_pulse_len = (normalized_pulse_len > ECU_PULSE_LEN_MAX) ? ECU_PULSE_LEN_MAX : normalized_pulse_len;
    float pulse_len_percent = ((float)(normalized_pulse_len - ECU_PULSE_LEN_MIN)) /
                              ((float)(ECU_PULSE_LEN_MAX - ECU_PULSE_LEN_MIN));
    return (pulse_len_percent > 0) ? pulse_len_percent : -1;
}

int16_t get_rpm(int pin) {
    float pulse_len_percent = get_ecu(pin);
    return (pulse_len_percent > 0) ? PERCENT_TO_RANGE(pulse_len_percent, RPM_MIN, RPM_MAX) :
                                     -1;
}

int16_t get_clt(int pin) {
    float pulse_len_percent = get_ecu(pin);
    return (pulse_len_percent > 0) ? PERCENT_TO_RANGE(pulse_len_percent, CLT_MIN, CLT_MAX) :
                                     -1;
}

int16_t get_bat(int pin) {
    float pulse_len_percent = get_ecu(pin);
    return (pulse_len_percent > 0) ? PERCENT_TO_RANGE(pulse_len_percent, BAT_MIN, BAT_MAX) :
                                     -1;
}

#endif // ECU_UTILS_H
