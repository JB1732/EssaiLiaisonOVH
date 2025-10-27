// Import required libraries
#include "WiFi.h"
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

const char *ssid = "Freeboxjb";
const char *password = "coucou123";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp32!");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup()
{
  //.....................Liaison série..............
  Serial.begin(115200);

  //  //--------------------------SPIFFS................................
  // Serial.println("Debut SPIFFS");
  // delay(500);
  // if (!SPIFFS.begin(true))
  // {
  //   Serial.println("Erreur SPIFFS...");
  //   return;
  // }
  // else
  //   Serial.println("SPIFFS OK");

  // File root = SPIFFS.open("/");
  // File file = root.openNextFile();

  // Serial.println("Parcours du SPIFFS");
  // delay(500);

  // while (file)
  // {
  //   Serial.print("File: ");
  //   Serial.println(file.name());
  //   file.close();
  //   file = root.openNextFile();
  // }

  // Serial.println("Fin SPIFFS");
  // delay(500);

  
  // Connect to Wi-Fi
      WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Adresse IP de l'ESP32 : " + WiFi.localIP().toString());
  Serial.println("\n");
  Serial.println(".....................ESP32-C6.......................");
  Serial.println(".............. .............");
  Serial.println("\n");

   //--------------------------SERVER-----------------------------------
  // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  //           { request->send(SPIFFS, "/index.html", "text/html"); });

  // server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request)
  //           { request->send(200, "text/plain", readDHTTemperature().c_str()); });
  
    if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  

}

void loop(void) {
  server.handleClient();
  delay(2);  //allow the cpu to switch to other tasks
}



//////////////////////////////////////////////////////

// #include <NetworkClient.h>
// #include <WebServer.h>
// #include <ESPmDNS.h>




