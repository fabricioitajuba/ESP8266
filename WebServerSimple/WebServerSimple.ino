/*
ESP8266 - Simples WebServer
Autor: Eng. Fabrício de Lima Ribeiro
25/01/23
*/

//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "meu_ssid";
const char* password = "minha_senha";

ESP8266WebServer server(80);

void handleRoot() {

  String msg;

  msg = F("Simples WebServer");
  
  String content = "<!DOCTYPE html>\
  <html lang='pt-br'>\
    <head>\
          <meta charset='UTF-8'>\
          <meta http-equiv='X-UA-Compatible' content='IE=edge'>\
          <meta name='viewport' content='width=device-width, initial-scale=1.0'>\
          <title>WebServer</title>\
    <body>\
      <h2>"+msg+"</h2>\
    </body>\
  </html>";
  
  server.send(200, "text/html", content);
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
  while (WiFi.status() != WL_CONNECTED) {
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
