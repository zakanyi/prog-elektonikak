#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

const char* host = "esp8266-webupdate";
const char* update_path = "/firmware";
const char* update_username = "admin";
const char* update_password = "admin";
const char* ssid = "........";
const char* password = "........";

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

void setup(){
	Serial.begin(115200);
	WiFi.mode(WIFI_AP_STA);
	WiFi.begin(ssid, password);

	while(WiFi.waitForConnectResult() != WL_CONNECTED){
		WiFi.begin(ssid, password);
		Serial.println("WiFi failed, retrying.");
	}

	MDNS.begin(host);

	httpUpdater.setup(&httpServer, update_path, update_username, update_password);
	httpServer.begin();

	MDNS.addService("http", "tcp", 80);
}

void loop(){
	httpServer.handleClient();
}