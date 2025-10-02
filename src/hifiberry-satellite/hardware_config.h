#ifndef HARDWARE_CONFIG_H
#define HARDWARE_CONFIG_H

// Rotary Encoder Pin Definitions

// On my Chinese KY-040 rotary encoder, CLK and DT pins are reversed, so reverse them in sketch for proper rotation direction.
//#define ROTARY_ENCODER_A_PIN 26       // A pin is CLK
//#define ROTARY_ENCODER_B_PIN 27       // B pin is DT
//#define ROTARY_ENCODER_BUTTON_PIN 25  // BUTTON pin is SW
//#define ROTARY_ENCODER_VCC_PIN -1     // set to -1 for vcc pin
//#define ROTARY_ENCODER_STEPS 4

// MaTouch
#define ROTARY_ENCODER_A_PIN 10       // A pin is CLK
#define ROTARY_ENCODER_B_PIN 9        // B pin is DT
#define ROTARY_ENCODER_BUTTON_PIN 6
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 4

// Other hardware constants can go here
// #define LED_PIN 13
// #define BUZZER_PIN 5

#endif
