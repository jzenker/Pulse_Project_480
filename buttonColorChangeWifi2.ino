//WiFi connection for ESP32 Module with Arduino 
//Josephine Zenker, December 2019 

//Tutorial followed from Mediums: Using Firebase to control your Arduino project, Hack Anons: IOT with Firebase and  
//over the web and other youtube tutorials

//I kept this module seperate as to not disturb the working button color changing code
//Libraries are installed but I'm currently having trouble with my computer finding my ESP32 library 
//My next goal is to get structured data into one object and to debug my issue with the ESP32 library

#include <WiFi.h>
#include <WiFiMulti.h>
#include <FirebaseArduino.h>

#define WIFI_SSID "insert wifi ssid"
#define WIFI_PASS "insert wifi password"
#define HOST "https://csci-480-senior-project.firebaseio.com/config/"
#define AUTH 

WiFiMulti wifiMulti; 
HTTPClient http; 

void setup() {
  Serial.begin(9600); 
  WiFi.begin(WIFI_SSID, WIFI_PASS); 
  Serial.print("Connecting..."); 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("."); 
    delay(600); 
  }
  //wifiMulti.addAP(WIFI_SSID, WIFI_PASS);
}

Serial.println(); 
Serial.print("Connection secured!"); 
Serial.println(WiFi.localIP()); 

void read() {
  //How we will read from Firebase database
  String host = HOST + WiFi.macAddress() + ".json";
  http.setTimeout(1000); 
  http.begin(host); 
  
  //Issue an HTTP GET request to this URL
  int getStatus = http.GET(); 
  if (getStatus <=0) {
    Serial.print("HTTP error: %s\n",
      http.errorToString(getStatus).c_str()); 
      return; 
  }
  
  //Read response from the Firebase database
  String payload = http.getString(); 
  Serial.println("HTTP reponse:"); 
  Serial.prinln(payload); 
}

//Run program periodically to call home to Firebase REST API
void loop() {
  read(); 

}
