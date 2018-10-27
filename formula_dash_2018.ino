#include <stdint.h>

#include "pinout.h"
#include "constants.h"
#include "ecu_utils.h"
#include "dash_utils.h"
#include "conditions.h"

#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip(LED_STRIP_NUM_LEDS, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ring(LED_RING_NUM_LEDS, LED_RING_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_7segment ss_display;

void start_sequence() {
}

void setup() {
#if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

    pinMode(RPM_PIN, INPUT_PULLUP);
    pinMode(CLT_PIN, INPUT_PULLUP);
    pinMode(BAT_PIN, INPUT_PULLUP);

    pinMode(LED_BUTTON_R, OUTPUT);
    pinMode(LED_BUTTON_G, OUTPUT);
    pinMode(LED_BUTTON_B, OUTPUT);

    strip     .begin();
    ring      .begin();
    ss_display.begin(0x70);

    //start_sequence();
}

unsigned long blink_time = 0;
unsigned long blink_state = 0;
void generate_strip_output(int16_t rpm, int16_t clt, int16_t bat) {
    simple_color colors[LED_STRIP_NUM_LEDS];
    if (SHIFT_POINT2) {
        unsigned long current_time = millis();
        if ((current_time - blink_time) > SHIFT_LIGHT_BLINK_PERIOD) {
            blink_state = !blink_state;
            blink_time = current_time;
        }
        for (int i = 0; i < LED_STRIP_NUM_LEDS; i++) {
            colors[i] = blink_state ? simple_color::OFF : simple_color::BLUE;
        }
        writeStrip(strip, colors);
        return;
    } else {
        blink_state = 0;
    }
    if (SHIFT_POINT1) {
        for (int i = 0; i < LED_STRIP_NUM_LEDS; i++) {
            colors[i] = simple_color::BLUE;
        }
        writeStrip(strip, colors);
        return;
    }
    colors[7] = (rpm < RPM_RANGE1) ? simple_color::OFF : simple_color::GREEN;
    colors[0] = (rpm < RPM_RANGE1) ? simple_color::OFF : simple_color::GREEN;

    colors[6] = (rpm < RPM_RANGE2) ? simple_color::OFF : simple_color::GREEN;
    colors[1] = (rpm < RPM_RANGE2) ? simple_color::OFF : simple_color::GREEN;

    colors[5] = (rpm < RPM_RANGE3) ? simple_color::OFF : simple_color::YELLOW;
    colors[2] = (rpm < RPM_RANGE3) ? simple_color::OFF : simple_color::YELLOW;

    colors[4] = (rpm < RPM_RANGE4) ? simple_color::OFF : simple_color::RED;
    colors[3] = (rpm < RPM_RANGE4) ? simple_color::OFF : simple_color::RED;

    writeStrip(strip, colors);
}

void generate_ring_output(int16_t rpm, int16_t clt, int16_t bat) {
    int gauge_setting;
    simple_color static_color, dynamic_color;
    if (!CLT_ACTIVE) {
        gauge_setting = -1;
        static_color  = simple_color::OFF;
        dynamic_color = simple_color::OFF;
        writeRingGauge(ring, gauge_setting, static_color, dynamic_color);
        return;
    }
    gauge_setting = (clt < 15)  ? 0  :
                    (clt < 30)  ? 1  :
                    (clt < 45)  ? 2  :
                    (clt < 60)  ? 3  :
                    (clt < 70)  ? 4  :
                    (clt < 80)  ? 5  :
                    (clt < 85)  ? 6  :
                    (clt < 87)  ? 7  :
                    (clt < 90)  ? 8  :
                    (clt < 93)  ? 9  :
                    (clt < 96)  ? 10 :
                    (clt < 100) ? 11 : 12;
    static_color = simple_color::WHITE;
    dynamic_color = (ENGINE_COLD)      ? simple_color::BLUE   :
                    (ENGINE_OPERATING) ? simple_color::GREEN  :
                    (ENGINE_HOT)       ? simple_color::YELLOW :
                                         simple_color::RED    ;
    writeRingGauge(ring, gauge_setting, static_color, dynamic_color);
}

/* void generate_button_output(int16_t rpm, int16_t clt, int16_t bat) { */
/*     simple_color color = (!CLT_ACTIVE)        ? simple_color::OFF    : */
/*                          (ENGINE_COLD)        ? simple_color::BLUE   : */
/*                          (ENGINE_OPERATING || */
/*                           ENGINE_HOT)         ? simple_color::GREEN  : */
/*                                                 simple_color::RED    ; */
/*     writeButton(color); */
/* } */

void generate_button_output(int16_t rpm, int16_t clt, int16_t bat) {
    simple_color color = (!BAT_ACTIVE)  ? simple_color::OFF   :
                         (BATTERY_LOW)  ? simple_color::RED   :
                         (BATTERY_HIGH) ? simple_color::GREEN :
                                          simple_color::BLUE  ;
    writeButton(color);
}

void generate_display_output(int16_t rpm, int16_t clt, int16_t bat) {
    if (BAT_ACTIVE && !ENGINE_RUNNING) {
        writeDisplay(ss_display, bat, "");
        return;
    }
    if (ENGINE_RUNNING) {
        writeDisplay(ss_display, rpm, "");
        return;
    }
    /* writeDisplay(ss_display, -1, "zbfr"); // 'z' shouldn't show */
    writeDisplay(ss_display, 1337, "");
}

void loop() {
    int16_t rpm = get_rpm(RPM_PIN);
    int16_t clt = get_clt(CLT_PIN);
    int16_t bat = get_bat(BAT_PIN);
    generate_strip_output  (rpm, clt, bat);
    generate_ring_output   (rpm, clt, bat);
    generate_button_output (rpm, clt, bat);
    generate_display_output(rpm, clt, bat);
    delay(50);
}
