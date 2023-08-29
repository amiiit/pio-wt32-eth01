#include <Arduino_ESP32_OTA.h>
#include <ESPmDNS.h>

#include "distance.hpp"
#include "connection.hpp"

// https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/api/ethernet.html
#include <ETH.h>
#include "string"

#define MQTT_SERVER "openhabian.local"
#define MQTT_SERVER_PORT 1883
#define MQTT_USERNAME "esp32"
#define MQTT_PASSWORD "espuma23"
#define MQTT_DEBUG

const int trigPin = 14;
const int echoPin = 15;


ConnectionOptions connection_options;
Connection conn;
// connection_options.mqtt_debug = MQTT_DEBUG;

void handleConnectionStateUpdate(connection_event_type eventType) {
    Serial.print("Connection update ");
    Serial.println(eventType);
}

void setup() {
    Serial.begin(115200);  // Starts the serial communication

    Serial.printf("Starting with version: %s\n", APP_BUILD_VERSION);

    connection_options.mqtt_server = MQTT_SERVER;
    connection_options.mqtt_server_port = MQTT_SERVER_PORT;
    connection_options.mqtt_username = MQTT_USERNAME;
    conn = Connection(connection_options, handleConnectionStateUpdate);
    conn.ConnectionBegin();

    pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
}

void loop() {
    Serial.println("=================");
    int distanceCm = measureDistance(trigPin, echoPin);
    conn.SendDistanceData(distanceCm);
    String firmwareVersion = conn.QueryFirmwareVersion("prototype-1");
    if (firmwareVersion != APP_BUILD_VERSION) {
        Serial.printf("New firmware available: %s\n", firmwareVersion.c_str());
    }
    Serial.print("Firmware version: ");
    Serial.println(firmwareVersion.c_str());

    delay(5000);
}
