#ifndef PINOUT_H
#define PINOUT_H

// Inputs from ECU
#define RPM_PIN A0 // LS5
#define CLT_PIN A1 // LS7
#define BAT_PIN A2 // LS6

// RGB Strip
#define LED_STRIP_PIN 6
#define LED_STRIP_NUM_LEDS 8

// RGB Ring
#define LED_RING_PIN 5
#define LED_RING_NUM_LEDS 16
#define LED_RING_TOP_LED  7

// RGB Button
#define LED_BUTTON_R  9
#define LED_BUTTON_G  10
#define LED_BUTTON_B  11

#endif // PINOUT_H
