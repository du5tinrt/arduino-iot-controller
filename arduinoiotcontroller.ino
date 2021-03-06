#include <ESP8266WiFi.h>
#include <SocketIoClient.h>
SocketIoClient webSocket;

const char* ssid     = "ssid";
const char* password = "password";

#define USE_SERIAL Serial

// Login Listener Function
void getloginresponse(const char * payload, size_t length) {
  USE_SERIAL.printf("got message: %s\n", payload);
}
// Controller Listener Function
void fan2(const char * payload, size_t length) {
  USE_SERIAL.printf("got message: %s\n", payload);
}
void setup() {


 Serial.begin(9600);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
  // Connecting to Arduino Iot Controller Server
  webSocket.begin("iotcontroller.herokuapp.com");
  // Login 
  webSocket.emit("Login", "{\"email\":\"enter_username\",\"password\":\"enter_password\"}");
  // Listen For Login Response
  webSocket.on("Login", getloginresponse);
  // Listen From Controller
  webSocket.on("username:controllerid",fan2);
 

}

void loop() {
  // put your main code here, to run repeatedly:
webSocket.loop();

}
