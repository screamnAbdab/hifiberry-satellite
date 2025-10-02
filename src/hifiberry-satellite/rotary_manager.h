#ifndef ROTARY_MANAGER_H
#define ROTARY_MANAGER_H

#define ENCODER_MIN 0
#define ENCODER_MAX 50

#include "AiEsp32RotaryEncoder.h"
#include "hardware_config.h"

class RotaryManager {
private:
    AiEsp32RotaryEncoder* encoder;
    unsigned long lastButtonPress;
    static const unsigned long DEBOUNCE_DELAY = 500;
    
    void handleButtonClick();
    
public:
    RotaryManager();
    void begin();
    void process();
    
    bool hasValueChanged();
    bool isButtonClicked();
    long readValue();
    void setValue(long value);
    
    static void IRAM_ATTR encoderISR();
    static RotaryManager* instance; // Static instance for ISR access
};

#endif
