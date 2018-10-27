#ifndef DASH_UTILS_H
#define DASH_UTILS_H

#include <stdint.h>

#include "pinout.h"

#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_NeoPixel.h"

enum simple_color {
    OFF    = 0b000,
    RED    = 0b100,
    GREEN  = 0b010,
    BLUE   = 0b001,
    PURPLE = RED   | BLUE,
    YELLOW = RED   | GREEN,
    CYAN   = GREEN | BLUE,
    WHITE  = RED   | GREEN | BLUE
};

void writeStrip(Adafruit_NeoPixel &strip, simple_color colors[LED_STRIP_NUM_LEDS]) {
    for (int i = 0; i < LED_STRIP_NUM_LEDS; i++) {
        strip.setPixelColor(i, (colors[i] & simple_color::RED)   ? 255 : 0,
                               (colors[i] & simple_color::GREEN) ? 255 : 0,
                               (colors[i] & simple_color::BLUE)  ? 255 : 0);
    }
    strip.show();
}

void writeStripSingle(Adafruit_NeoPixel &strip, int index, simple_color color) {
    simple_color colors[LED_STRIP_NUM_LEDS];
    for (int i = 0; i < LED_STRIP_NUM_LEDS; i++) {
        colors[i] = simple_color::OFF;
    }
    if (index >= 0 && index < LED_STRIP_NUM_LEDS) {
        colors[index] = color;
    }
    writeStrip(strip, colors);
}

void writeRing(Adafruit_NeoPixel &ring, simple_color colors[LED_RING_NUM_LEDS]) {
    for (int i = 0; i < LED_RING_NUM_LEDS; i++) {
        ring.setPixelColor((i+LED_RING_TOP_LED) % LED_RING_NUM_LEDS,
                           (colors[i] & simple_color::RED)   ? 255 : 0,
                           (colors[i] & simple_color::GREEN) ? 255 : 0,
                           (colors[i] & simple_color::BLUE)  ? 255 : 0);
    }
    ring.show();
}

void writeRingGauge(Adafruit_NeoPixel &ring, int gauge_setting, simple_color static_color,
                                                                simple_color dynamic_color) {
    simple_color colors[LED_RING_NUM_LEDS] = {simple_color::OFF,
                                              simple_color::OFF,
                                              simple_color::OFF,
                                              simple_color::OFF,
                                              simple_color::OFF,
                                              simple_color::OFF,
                                              simple_color::OFF,
                                              static_color,
                                              static_color,
                                              static_color,
                                              simple_color::OFF,
                                              simple_color::OFF,
                                              simple_color::OFF,
                                              simple_color::OFF,
                                              simple_color::OFF,
                                              simple_color::OFF};
    if (gauge_setting >= 0 && gauge_setting <= 12) {
        int led = 6 - gauge_setting;
        led = (led < 0) ? led + 16 : led;
        colors[led] = dynamic_color;
    }
    writeRing(ring, colors);
}

// only use RED, BLUE, or GREEN
void writeButton(simple_color color) {
    digitalWrite(LED_BUTTON_R, color & simple_color::RED);
    digitalWrite(LED_BUTTON_G, color & simple_color::GREEN);
    digitalWrite(LED_BUTTON_B, color & simple_color::BLUE);
}

void writeDisplay(Adafruit_7segment &display, int value, char text[4]) {
    static uint8_t letter_table[] = {
        //gfedcba
        0b1110111, // A
        0b1111100, // b
        0b1011000, // c
        0b1011000, // d
        0b1011000, // E
        0b1011000, // F
        0b0000000, // G
        0b1110110, // H
        0b0000000, // I
        0b0000000, // J
        0b0000000, // K
        0b0111000, // L
        0b0000000, // M
        0b1010100, // n
        0b1011100, // o
        0b1110011, // P
        0b0000000, // q
        0b1010000, // r
        0b1101101, // s
        0b1111000, // t
        0b0011100, // u
        0b0000000, // v
        0b0000000, // w
        0b0000000, // x
        0b1101110, // y
        0b0000000  // z
    };
    if (value < 0) {
        for (int i = 0; i < 4; i++) {
            display.writeDigitRaw(i, letter_table[text[i]-'a']);
        }
    } else {
        display.print(value, DEC);
    }
    display.writeDisplay();
}

#endif // DASH_UTILS_H
