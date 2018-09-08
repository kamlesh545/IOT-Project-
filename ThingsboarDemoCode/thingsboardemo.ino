#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

//wifi ssid and password
char ssid[] = "";
char pass[] = "";

int status = WL_IDLE_STATUS;
IPAddress ip;
// MQTTServer to use
char server[] = "demo.thingsboard.io";
#define TOKEN "05zd6gMuYKUnJbe2J4S9"


const int pin = 2;
//DHT11 Pin number
#define DHTPIN 10    

/
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
unsigned long currentTime;
unsigned long lastTime;
unsigned long intervalTime = 30000;
unsigned long lastSend;
void callback(char* topic, byte* payload, unsigned int length) {
//  Serial.print("Received message for topic ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.write(payload, length);
  Serial.println();
}


WiFiClient wifiClient;

PubSubClient client(server, 1883, callback, wifiClient);

void setup()
{
  Serial.begin(9600); 
  dht.begin();
   
  
  while (status != WL_CONNECTED) {
    Serial.println("Connecting to WiFi");
    status = WiFi.begin(ssid, pass);
    if (status == WL_CONNECTED)
      break;
    delay(10000);
  }
  Serial.println("Connected to WiFi");
  ip = WiFi.localIP();
  Serial.println(ip);
    lastSend = 0;
    pinMode(pin,INPUT);
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    status = WiFi.status();
    if ( status != WL_CONNECTED) {
      WiFi.begin(ssid, pass);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("Connected to AP");
    }
    Serial.print("Connecting to ThingsBoard node ...");
    // Attempt to connect (clientId, username, password)
    if ( client.connect("energiaClient", TOKEN, NULL) ) {
      Serial.println( "[DONE]" );
    } else {
      Serial.print( "[FAILED] [ rc = " );
      Serial.println( " : retrying in 5 seconds]" );
      // Wait 5 seconds before retrying
      delay( 5000 );
    }
  }
}
void loop()
{

    if ( !client.connected() ) {
    reconnect();
  }

  if ( millis() - lastSend > 1000 ) { // Update and send only after 1 seconds
    getAndSendTemperatureAndHumidityData();
    lastSend = millis();
  }

  client.loop();
}

void getAndSendTemperatureAndHumidityData()
{
  Serial.println("Collecting temperature data.");

 
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  String t = String(temperature);
  String h = String(humidity);


  // Just debug messages
  Serial.print( "Sending temperature and humidity : [" );
  Serial.print( t ); Serial.print( "," );
  Serial.print( h );
  Serial.print( "]   -> " );

  // Prepare a JSON payload string
  String payload = "{";
  payload += "\"temperature\":"; payload += t; payload += ",";
  payload += "\"humidity\":"; payload += h;
  payload += "}";

  // Send payload
  char attributes[100];
  payload.toCharArray( attributes, 100 );
  client.publish( "v1/devices/me/telemetry", attributes );
  Serial.println( attributes );

   int sensorValue = digitalRead(pin);
   int val;
   if (sensorValue == 1){
    int val = 0;
    // Prepare a JSON payload string
  String payloadd = "{";
  payloadd += "\"light\":"; payloadd += val;
  payloadd += "}";

  // Send payload
  char attributess[100];
  payloadd.toCharArray( attributess, 100 );
  client.publish( "v1/devices/me/telemetry", attributess );
  Serial.println( attributess );

    }
    else{
      int val =1;
      // Prepare a JSON payload string
  String payloadd = "{";
  payloadd += "\"light\":"; payloadd += val;
  payloadd += "}";

  // Send payload
  char attributess[100];
  payloadd.toCharArray( attributess, 100 );
  client.publish( "v1/devices/me/telemetry", attributess );
  Serial.println( attributess );

      
      }
    

}

