#ifndef VOLUME_CONTROLLER_H
#define VOLUME_CONTROLLER_H

#include <HTTPClient.h>
#include <Arduino_JSON.h>

class VolumeController {
private:
    String apiUrl;
    HTTPClient http;
    
public:
    VolumeController();
    void begin(const String& apiUrl);
    
    bool fetchVolume(int& volume);
    bool setVolume(int volume);
    
    void printHttpError(int responseCode);
};

#endif
