#ifndef VOLUME_CONTROLLER_H
#define VOLUME_CONTROLLER_H

#include <HTTPClient.h>
#include <Arduino_JSON.h>

class VolumeController {
private:
    String apiUrl;
    HTTPClient http;
    int lastSentVolume = -1;
   
public:
    VolumeController();
    void begin(const String& apiUrl);
    int getLastSentVolume() const { return lastSentVolume; }
    bool fetchVolume(int& volume);
    bool setVolume(int volume);
    
    void printHttpError(int responseCode);
};

#endif
