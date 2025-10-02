#include "rotary_manager.h"
#include "hardware_config.h"

RotaryManager* RotaryManager::instance = nullptr;

RotaryManager::RotaryManager() : lastButtonPress(0) {
    encoder = new AiEsp32RotaryEncoder(
        ROTARY_ENCODER_A_PIN, 
        ROTARY_ENCODER_B_PIN, 
        ROTARY_ENCODER_BUTTON_PIN, 
        ROTARY_ENCODER_VCC_PIN, 
        ROTARY_ENCODER_STEPS
    );
    instance = this; // Set static instance for ISR access
}

void RotaryManager::begin() {
    encoder->begin();
    encoder->setup(encoderISR);
    encoder->setBoundaries(ENCODER_MIN, ENCODER_MAX, false); // minValue, maxValue, circleValues
    //encoder->disableAcceleration();
}

void RotaryManager::process() {
    if (isButtonClicked()) {
        handleButtonClick();
    }
}

bool RotaryManager::hasValueChanged() {
    return encoder->encoderChanged();
}

bool RotaryManager::isButtonClicked() {
    return encoder->isEncoderButtonClicked();
}

long RotaryManager::readValue() {
    return encoder->readEncoder();
}

void RotaryManager::setValue(long value) {
    encoder->setEncoderValue(value);
}

void RotaryManager::handleButtonClick() {
    unsigned long currentTime = millis();
    if (currentTime - lastButtonPress < DEBOUNCE_DELAY) {
        return;
    }
    lastButtonPress = currentTime;
    
    //Serial.print("Button pressed at ");
    //Serial.print(currentTime);
    //Serial.println(" milliseconds after restart");
}

void IRAM_ATTR RotaryManager::encoderISR() {
    if (instance != nullptr) {
        instance->encoder->readEncoder_ISR();
    }
}
