// Libraries
#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <dht.h>


// WiFi Client
WiFiClient client;

int interval = 5000;

// Your network name also called SSID
char ssid[] = "demo";
// your network password
char password[] = "123455555";
// your network key Index number (needed only for WEP)
int keyIndex = 0;

// Dweet parameters
char * server_name = "www.newtechgadget.in";

void setup() {

  Serial.begin(115200);      // Initialize serial communication

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  
  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }

}


void loop() {
    
  
  // Measure temperature & humidity  
  float temperature, humidity;
  if (dht::readFloatData(10, &temperature, &humidity, false) == 0)
  {
    Serial.print("T: ");
    Serial.print(temperature);
    Serial.print(" H: ");
    Serial.println(humidity);    
  }
  
  // Send data to server
      if (client.connect(server_name, 80)) {
        Serial.println("Connected");
        
        Serial.print(F("Sending request... "));
        
        client.print("GET /add.php?");
        client.print("temperature=");
        client.print(temperature);
        client.print("&&");
        client.print("humidity=");
        client.print(humidity);
        client.println(" HTTP/1.1");
        client.println("Host: newtechgadget.in");
        client.println("Connection: close");
        client.println("");
        
        Serial.println("done.");
        client.stop();
    }
	else {

    // you didn't get a connection to the server:

    Serial.println("--> connection failed/n");

  }
  delay(interval);
  
  
}

