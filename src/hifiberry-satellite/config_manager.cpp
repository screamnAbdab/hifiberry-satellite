#include "config_manager.h"

const char* DEFAULT_SSID = "velox";
const char* DEFAULT_PASSWORD = "sarahbeara";
const char* DEFAULT_HOSTNAME = "rosat";
const char* DEFAULT_HB_API_URL = "http://hbamp60.local:81/api/volume";

ConfigManager::ConfigManager() : configured(false) {}

void ConfigManager::begin() {
    preferences.begin("app-config", false);
    configured = preferences.isKey("configured");
    
    if (!configured) {
        loadDefaults();
    }
    
    preferences.end();
}

void ConfigManager::loadDefaults() {
    preferences.putString("hb-api-url", DEFAULT_HB_API_URL);
    preferences.putString("ssid", DEFAULT_SSID);
    preferences.putString("password", DEFAULT_PASSWORD);
    preferences.putString("hostname", DEFAULT_HOSTNAME);
    preferences.putBool("configured", true);
    configured = true;
}

String ConfigManager::getHbApiUrl() {
    preferences.begin("app-config", true);
    String url = preferences.getString("hb-api-url", DEFAULT_HB_API_URL);
    preferences.end();
    return url;
}

String ConfigManager::getSSID() {
    preferences.begin("app-config", true);
    String ssid = preferences.getString("ssid", DEFAULT_SSID);
    preferences.end();
    return ssid;
}

String ConfigManager::getPassword() {
    preferences.begin("app-config", true);
    String password = preferences.getString("password", DEFAULT_PASSWORD);
    preferences.end();
    return password;
}

String ConfigManager::getHostname() {
    preferences.begin("app-config", true);
    String hostname = preferences.getString("hostname", DEFAULT_HOSTNAME);
    preferences.end();
    return hostname;
}

void ConfigManager::setHbApiUrl(const String& url) {
    preferences.begin("app-config", false);
    preferences.putString("hb-api-url", url);
    preferences.end();
}

void ConfigManager::setSSID(const String& ssid) {
    preferences.begin("app-config", false);
    preferences.putString("ssid", ssid);
    preferences.end();
}

void ConfigManager::setPassword(const String& password) {
    preferences.begin("app-config", false);
    preferences.putString("password", password);
    preferences.end();
}

void ConfigManager::setHostname(const String& hostname) {
    preferences.begin("app-config", false);
    preferences.putString("hostname", hostname);
    preferences.end();
}

bool ConfigManager::isConfigured() {
    return configured;
}

void ConfigManager::markConfigured() {
    preferences.begin("app-config", false);
    preferences.putBool("configured", true);
    preferences.end();
    configured = true;
}
