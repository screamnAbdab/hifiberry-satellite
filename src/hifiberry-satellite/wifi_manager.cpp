#include "wifi_manager.h"

String WiFiManager::static_hostname = "";

WiFiManager::WiFiManager() {}

void WiFiManager::begin(const String& ssid, const String& password, const String& hostname) {
    this->ssid = ssid;
    this->password = password;
    this->hostname = hostname;
    static_hostname = hostname;
    
    WiFi.mode(WIFI_STA);
    WiFi.onEvent(onConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED);
    WiFi.onEvent(onGotIP, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
    WiFi.onEvent(onDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);

    //Serial.print("WiFi hostname: ");
    //Serial.println(hostname);
    WiFi.setHostname(hostname.c_str());
    
    //Serial.print("WiFi SSID: ");
    //Serial.println(ssid);
    //Serial.print("WiFi password: ");
    //Serial.println(password);
    
    WiFi.begin(ssid.c_str(), password.c_str());

    //Serial.println();
    //Serial.println("Waiting for WiFi connection...");
}

void WiFiManager::onConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
    //Serial.println("Connected to AP successfully!");
}

void WiFiManager::onGotIP(WiFiEvent_t event, WiFiEventInfo_t info) {
    //Serial.println("WiFi connected");
    //Serial.println("IP address: ");
    //Serial.println(WiFi.localIP());
    //Serial.print("ESP32 HostName: ");
    //Serial.println(WiFi.getHostname());
    //Serial.print("RSSI: ");
    //Serial.println(WiFi.RSSI());

    // Initialize mDNS
    if (!MDNS.begin(static_hostname.c_str())) {
        //Serial.println("Error setting up MDNS responder!");
        while(1) {
            delay(1000);
        }
    }
    //Serial.println("mDNS responder started");
}

void WiFiManager::onDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
    //Serial.println("Disconnected from WiFi access point");
    //Serial.print("WiFi lost connection. Reason: ");
    //Serial.println(info.wifi_sta_disconnected.reason);
    //Serial.println("Trying to Reconnect");
    WiFi.reconnect();
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::printStatus() {
    //Serial.print("WiFi Status: ");
    //Serial.println(WiFi.status());
    if (isConnected()) {
        //Serial.print("IP: ");
        Serial.println(WiFi.localIP());
        //Serial.print("RSSI: ");
        //Serial.println(WiFi.RSSI());
    }
}
