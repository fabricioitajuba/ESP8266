/*
ESP8266 - WebWiFi
Este exemplo, mostra as redes wifi disponíveis
Autor: Eng. Fabrício de Lima Ribeiro
25/01/23
*/

//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "Fabricio_2G";
const char* password = "oioioimlr";

ESP8266WebServer server(80);

void handleRoot(){

  String Page;
  
  Page += F("<!DOCTYPE html><html lang='pt-br'><head>"
            "<meta charset='UTF-8'>"
            "<meta name='viewport' content='width=device-width'>"
            "<title>WiFi Config</title></head><body>"
            "<h1>Wifi config</h1>"
            "<style>"
              ".comment{"
                  "resize: none;"
                  "height: 100px;"
                  "width: 350px;"
              "}"
            "</style>");

  Page += String(F("<p>Você está conectado a rede WiFI: <b>"))+ssid+F("</b></p>");

  Page += String(F("Redes WLAN disponíveis (atualize a página caso necessário)<br>"));

  Page += F("<textarea class='comment'>");
  
  Serial.println("scan start");
  
  int n = WiFi.scanNetworks();
  
  Serial.println("scan done");
  
  if (n > 0) {
    for (int i = 0; i < n; i++){
      Page += String(F("\r\n\r\n-"))+WiFi.SSID(i)+F(" ")+((WiFi.encryptionType(i)==ENC_TYPE_NONE) ? F(" ") : F(" *")) + F(" (")+WiFi.RSSI(i)+F(")");
     }
  } else {
    Page += F("No WLAN found");
  }
  Page += F("</textarea>");
  Page += F("\r\n<br/><form method='POST' action='wifisave'><h4>Conectar a rede:</h4>"
            "<input type='text' placeholder='network' name='n'/>"
            "<br/><input type='password' placeholder='password' name='p'/>"
            "<br/><br/><input type='submit' value='Connect/Disconnect'/></form>"            
            "</body></html>");
  
  server.send(200, "text/html", Page);
  server.client().stop();
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  server.send(404, "text/plain", message);
}

void setup(void) {

  delay(1000);
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print(F("Conectando"));

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print(F("Conectado em: "));
  Serial.println(ssid);
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());


  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println(F("Servidor HTTP iniciado!"));
}

void loop(void) {
  server.handleClient();
}
