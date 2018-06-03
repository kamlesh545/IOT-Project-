#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>

WiFiClient client;

char * server_name = "afternoon-sierra-25379.herokuapp.com";
String PostData = "{\"flag\": \"1\", \"id\": 1}"; 
#define thing_name  "demooo"
const int trigPin = 2;
const int echoPin = 3;
// defines variables
long duration;
int distance;
String data;
 String par = "slot=";
// Your network name also called SSID
char ssid[] = "moto";
// your network password
char password[] = "987654321";
// your network key Index number (needed only for WEP)
int keyIndex = 0;
void setup() {

  Serial.begin(115200);     
  //Serial.println("Starting WiFi SmartConfig");
  //WiFi.startSmartConfig();
   Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);

 Serial.print("Connected to SSID: ");
  Serial.println(WiFi.SSID());

  while (WiFi.localIP() == INADDR_NONE) {
   
    Serial.print(".");
    delay(300);
  }

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

  Serial.println("\nIP Address obtained");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());


pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
 // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

if (distance <=10 ){
  String PostData = "{\"flag\": \"0\", \"id\": 1}"; 
  if (client.connect(server_name, 80)) {
    Serial.println("Connected");
    
    Serial.println("Sending request... ");
    
    client.println("POST /todos HTTP/1.1");
    client.println("Host: afternoon-sierra-25379.herokuapp.com");
    client.println("Cache-Control: no-cache");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(PostData.length());
    client.println();
    client.println(PostData);
    Serial.println(PostData);

  if (client.connected()) { 
    client.stop();  // DISCONNECT FROM THE SERVER
  }
    Serial.println("done.");
    delay(1000);
  }
}else {
  String PostDataa = "{\"flag\": \"1\", \"id\": 1}"; 
  if (client.connect(server_name, 80)) {
    Serial.println("Connected");
    
    Serial.println("Sending request... ");
    
    client.println("POST /todos HTTP/1.1");
    client.println("Host: afternoon-sierra-25379.herokuapp.com");
    client.println("Cache-Control: no-cache");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(PostDataa.length());
    client.println();
    client.println(PostDataa);
    Serial.println(PostDataa);

  if (client.connected()) { 
    client.stop();  // DISCONNECT FROM THE SERVER
  }
    Serial.println("done.");
    delay(1000);
    }
  }
     delay(1000);

}
