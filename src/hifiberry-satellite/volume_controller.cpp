#include "volume_controller.h"
#include <WiFi.h>

VolumeController::VolumeController() {}

void VolumeController::begin(const String& apiUrl) {
    this->apiUrl = apiUrl;
}

bool VolumeController::fetchVolume(int& volume) {
    if (WiFi.status() != WL_CONNECTED) {
        //Serial.println("WiFi not connected - cannot fetch volume");
        return false;
    }
    
    http.begin(apiUrl);
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
        //Serial.print("HTTP Response code: ");
        //Serial.println(httpResponseCode);
        
        String payload = http.getString();
        //Serial.println("Received: " + payload);
        
        JSONVar responseJson = JSON.parse(payload);
        
        if (JSON.typeof(responseJson) == "undefined") {
            //Serial.println("Parsing API response failed!");
            http.end();
            return false;
        }
        
        if (responseJson.hasOwnProperty("percent")) {
            volume = (int)responseJson["percent"];
            http.end();
            return true;
        } else {
            //Serial.println("Response missing 'percent' field!");
            http.end();
            return false;
        }
    } else {
        //printHttpError(httpResponseCode);
        http.end();
        return false;
    }
}

bool VolumeController::setVolume(int volume) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi not connected - cannot set volume");
        return false;
    }
    
    JSONVar payload;
    payload["percent"] = String(volume);
    String jsonString = JSON.stringify(payload);
    
    Serial.print("Sending payload: ");
    Serial.println(jsonString);
    
    http.begin(apiUrl);
    http.addHeader("Content-Type", "application/json");
    
    int httpResponseCode = http.POST(jsonString);

    if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        
        String response = http.getString();
        Serial.println("Response: " + response);
        
        lastSentVolume = volume;

        http.end();
        return true;
    } else {
        //printHttpError(httpResponseCode);
        http.end();
        return false;
    }    
}

/*
void VolumeController::printHttpError(int responseCode) {
    Serial.print("HTTP Error code: ");
    Serial.println(responseCode);
    
    switch (responseCode) {
        case HTTPC_ERROR_CONNECTION_REFUSED:
            Serial.println("Connection refused");
            break;
        case HTTPC_ERROR_SEND_HEADER_FAILED:
            Serial.println("Send header failed");
            break;
        case HTTPC_ERROR_SEND_PAYLOAD_FAILED:
            Serial.println("Send payload failed");
            break;
        case HTTPC_ERROR_NOT_CONNECTED:
            Serial.println("Not connected");
            break;
        case HTTPC_ERROR_CONNECTION_LOST:
            Serial.println("Connection lost");
            break;
        case HTTPC_ERROR_NO_STREAM:
            Serial.println("No stream");
            break;
        case HTTPC_ERROR_NO_HTTP_SERVER:
            Serial.println("No HTTP server");
            break;
        case HTTPC_ERROR_TOO_LESS_RAM:
            Serial.println("Too less RAM");
            break;
        case HTTPC_ERROR_ENCODING:
            Serial.println("Encoding error");
            break;
        case HTTPC_ERROR_STREAM_WRITE:
            Serial.println("Stream write error");
            break;
        case HTTPC_ERROR_READ_TIMEOUT:
            Serial.println("Read timeout");
            break;
        default:
            Serial.println("Unknown error");
            break;
    }
}
*/
