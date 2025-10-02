#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <ESPmDNS.h>

class WiFiManager {
private:
    String ssid;
    String password;
    String hostname;
    
    static void onConnected(WiFiEvent_t event, WiFiEventInfo_t info);
    static void onGotIP(WiFiEvent_t event, WiFiEventInfo_t info);
    static void onDisconnected(WiFiEvent_t event, WiFiEventInfo_t info);
    
    static String static_hostname; // Static member to access in callbacks

public:
    WiFiManager();
    void begin(const String& ssid, const String& password, const String& hostname);
    bool isConnected();
    void printStatus();
};

#endif
