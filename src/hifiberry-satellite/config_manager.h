#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <Preferences.h>

class ConfigManager {
private:
    Preferences preferences;
    bool configured;

public:
    ConfigManager();
    void begin();
    void loadDefaults();
    
    String getHbApiUrl();
    String getSSID();
    String getPassword();
    String getHostname();
    
    void setHbApiUrl(const String& url);
    void setSSID(const String& ssid);
    void setPassword(const String& password);
    void setHostname(const String& hostname);
    
    bool isConfigured();
    void markConfigured();
};

#endif
