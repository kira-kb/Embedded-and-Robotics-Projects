#include <Arduino.h>
#include <WiFi.h>

const char* ssid     = "ze-amanueal";
const char* password = "Ab1234567";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(2, OUTPUT);      

    delay(10);

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

int value = 0;
String light1 = "Click <a href=\"/H\">here to turn the lamp on.</a><br>";
String light2 = "Click <a href=\"/L\">here to turn the lamp off.</a><br>";

void loop(){
 WiFiClient client = server.available();

  if (client) {                             
    Serial.println("New Client.");           
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        if (c == '\n') {                    


          if (currentLine.length() == 0) {

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();


            client.print(light1);
            client.print(light2);


            client.println();

            break;
          } else {  
            currentLine = "";
          }
        } else if (c != '\r') { 
          currentLine += c;
        }

        if (currentLine.endsWith("GET /H")) {
          digitalWrite(2, HIGH);// GET /H turns the LED on
          Serial.println("led on");               
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(2, LOW);                // GET /L turns the LED off
          Serial.println("led off");
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
