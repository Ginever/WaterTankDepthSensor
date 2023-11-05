/*
  Make sure your Firebase project's ".read" and ".write" rules are set to "true".
  Avoiding this will result in an error.
  For more details- https://github.com/Rupakpoddar/ESP8266Firebase/blob/master/README.md
*/

#include <ESP8266Firebase.h>
//#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define _SSID "common44"        // Your WiFi SSID
#define _PASSWORD "a1b2c3d4e5"    // Your WiFi Password
#define PROJECT_ID "house-iot-f1c15-default-rtdb"   // Your Firebase Project ID. Can be found in project settings.

// Define Trig and Echo pin:
#define trigPin 12
#define echoPin 14
#define power 13

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// Define variables:
long duration;
int distance;

Firebase firebase(PROJECT_ID);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(power, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(115200);

  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(power, HIGH);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.printf("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  // Print the IP address
  Serial.print("IP Address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  digitalWrite(LED_BUILTIN, HIGH);

  
  timeClient.begin();
  timeClient.setTimeOffset(39600);
  Serial.println("Time Client Connected");

//================================================================//
//================================================================//

//  // Examples of setting String, integer and float values.
//  firebase.setString("Example/setString", "It's Working");
//  firebase.setInt("Example/setInt", 123);
//  firebase.setFloat("Example/setFloat", 45.32);
//
//  // Examples of pushing String, integer and float values.
//  firebase.pushString("push", "Hello");
//  firebase.pushInt("push", 789);
//  firebase.pushFloat("push", 89.54);
//
//  // Example of getting a String.
//  String data1 = firebase.getString("Example/setString");
//  Serial.print("Received String:\t");
//  Serial.println(data1);
//
//  // Example of getting an int.
//  int data2 = firebase.getInt("Example/setInt");
//  Serial.print("Received Int:\t\t");
//  Serial.println(data2);
//
//  // Example of getting a float.
//  float data3 = firebase.getFloat("Example/setFloat");
//  Serial.print("Received Float:\t\t");
//  Serial.println(data3);
//
//  // Example of data deletion.
//  firebase.deleteData("Example");
}

void loop() {
  timeClient.update();

  
  // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  digitalWrite(power, HIGH);

  delayMicroseconds(5);

 // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance:
  distance = duration*0.034/2;
  
  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  Serial.print(timeClient.getEpochTime());
  Serial.print(": Distance = ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.println("tank_depth/" + timeClient.getFormattedTime());
  firebase.setInt("tank_depth/" + timeClient.getFormattedTime() , distance);
  
  delay(2000);
}
