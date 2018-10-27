#ifndef CONSTANTS_H
#define CONSTANTS_H

// 200 Hz, 1% to 99% duty
#define ECU_PULSES_TO_SAMPLE 1
#define ECU_PULSE_TIMEOUT 25000 // us
#define ECU_PULSE_LEN_MIN 50    // us
#define ECU_PULSE_LEN_MAX 4950  // us

#define RPM_MIN 0    // RPM / 10
#define RPM_MAX 1300 // RPM / 10

// Top ends of RPM ranges
#define RPM_RANGE0  100 // RPM / 10 - car running
#define RPM_RANGE1  750 // RPM / 10 - downshift safe
#define RPM_RANGE2  800 // RPM / 10
#define RPM_RANGE3  875 // RPM / 10
#define RPM_RANGE4  950 // RPM / 10
#define RPM_RANGE5 1000 // RPM / 10 - shift point soon
#define RPM_RANGE6 1080 // RPM / 10 - shift point

#define CLT_MIN 5  // deg C
#define CLT_MAX 110 // deg C

// Top ends of CLT ranges
#define CLT_RANGE0 80 // deg C - cold
#define CLT_RANGE1 90 // deg C - operating
#define CLT_RANGE2 95 // deg C - hot

#define BAT_MIN 800  // Volts * 100
#define BAT_MAX 1500 // Volts * 100

// Top ends of BAT ranges
#define BAT_RANGE0 1240 // Volts * 100
#define BAT_RANGE1 1300 // Volts * 100

#define SHIFT_LIGHT_BLINK_PERIOD 100
#define START_SEQUENCE_DELAY 25

#endif // CONSTANTS_H
