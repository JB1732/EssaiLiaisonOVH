// Import required libraries
#include "WiFi.h"
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

const char *ssid = "Freeboxjb";
const char *password = "coucou123";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);


void setup()
{
  //.....................Liaison série..............
  Serial.begin(115200);

   //--------------------------SPIFFS................................
  Serial.println("Debut SPIFFS");
  delay(500);
  if (!SPIFFS.begin(true))
  {
    Serial.println("Erreur SPIFFS...");
    return;
  }
  else
    Serial.println("SPIFFS OK");

  File root = SPIFFS.open("/");
  File file = root.openNextFile();

  Serial.println("Parcours du SPIFFS");
  delay(500);

  while (file)
  {
    Serial.print("File: ");
    Serial.println(file.name());
    file.close();
    file = root.openNextFile();
  }

  Serial.println("Fin SPIFFS");
  delay(500);

  
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
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/index.html", "text/html"); });

  // server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request)
  //           { request->send(200, "text/plain", readDHTTemperature().c_str()); });
   server.begin();
}

void loop()
{
}
