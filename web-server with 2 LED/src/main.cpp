#include <WiFi.h>
#include <WebServer.h>


const char* ssid = "config";
const char* password = "rootPass";

/* Put IP Address details */
IPAddress local_ip(99,99,99,100);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

uint8_t LEDOnePin = 2;
bool LEDOneStatus = LOW;

uint8_t LEDTwoPin = 5;
bool LEDTwoStatus = LOW;


String SendHTML(uint8_t led1stat,uint8_t led2stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>home automotino</h1>\n";
  ptr +="<h3>wifi and bluetooth</h3>\n";
  
   if(led1stat)
  {ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}


void handle_OnConnect() {
  LEDOneStatus = LOW;
  LEDTwoStatus = LOW;
  Serial.println("GPIO2 Status: OFF | GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML(LEDOneStatus,LEDTwoStatus)); 
}

void handle_led1on() {
  LEDOneStatus = HIGH;
  Serial.println("GPIO2 Status: ON");
  server.send(200, "text/html", SendHTML(true,LEDTwoStatus)); 
}

void handle_led1off() {
  LEDOneStatus = LOW;
  Serial.println("GPIO2 Status: OFF");
  server.send(200, "text/html", SendHTML(false,LEDTwoStatus)); 
}

void handle_led2on() {
  LEDTwoStatus = HIGH;
  Serial.println("GPIO5 Status: ON");
  server.send(200, "text/html", SendHTML(LEDOneStatus,true)); 
}

void handle_led2off() {
  LEDTwoStatus = LOW;
  Serial.println("GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML(LEDOneStatus,false)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}


void setup() {
  Serial.begin(115200);
  pinMode(LEDOnePin, OUTPUT);
  pinMode(LEDTwoPin, OUTPUT);

  while(!WiFi.softAP(ssid, password)){
    delay(500);
    Serial.println(".");
  };

  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server Has started");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  server.handleClient();
  if(LEDOneStatus)
  {digitalWrite(LEDOnePin, HIGH);}
  else
  {digitalWrite(LEDOnePin, LOW);}
  
  if(LEDTwoStatus)
  {digitalWrite(LEDTwoPin, HIGH);}
  else
  {digitalWrite(LEDTwoPin, LOW);}
}
