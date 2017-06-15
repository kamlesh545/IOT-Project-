#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <dht.h>

WiFiClient client;

char * server_name = "www.dweet.io";
#define thing_name  "new"

int moistureAO = 2;

int moistureDO = 8;

int ldrpinAO = 6;

int emp = 0;
void setup() {

  Serial.begin(115200);     
  Serial.println("Starting WiFi SmartConfig");
  WiFi.startSmartConfig();

  Serial.print("Connected to SSID: ");
  Serial.println(WiFi.SSID());

  while (WiFi.localIP() == INADDR_NONE) {
    
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nIP Address obtained");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(moistureAO, INPUT);

  pinMode(moistureDO, INPUT);

  pinMode(ldrpinAO, INPUT);

}

void loop() {
 
  int tmp = analogRead(moistureAO);
  
        Serial.print("A=");
        Serial.println(tmp);
  
  int emp = digitalRead(moistureDO);

        Serial.print("D=");
        Serial.println(emp);

 int ldrvalue = analogRead(ldrpinAO);
 Serial.print("ldrstatus=");
        Serial.println(ldrvalue);
  
  float temperature, humidity;
  if (dht::readFloatData(10, &temperature, &humidity, false) == 0)
  {
    Serial.print("T: ");
    Serial.print(temperature);
    Serial.print(" H: ");
    Serial.println(humidity);    
  }

  if (client.connect(server_name, 80)) {
    Serial.println("Connected");
    
    Serial.print(F("Sending request... "));
    
    client.print(F("GET /dweet/for/"));
    client.print(thing_name);
    client.print(F("?temperature="));
    client.print(temperature);
    delay(500);
    client.print(F("&humidity="));
    client.print(humidity);
    delay(500);
    client.print(F("&analogmoisture="));
client.print(tmp);
delay(500);
    client.print(F("&digitalmoisture="));
client.print(emp);
delay(500);
 client.print(F("&ldrstatus="));
client.print(ldrvalue);
    client.println(F(" HTTP/1.1"));
    client.println(F("Host: dweet.io"));
    client.println(F("Connection: close"));
    client.println(F(""));

    Serial.println(F("done."));
  }
  
 
  Serial.println(F("Reading answer..."));
  while (client.connected()) {
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
  }
  Serial.println(F(""));
  client.stop();
  Serial.println(F("Closing connection"));
  Serial.println(F(""));
 
}
