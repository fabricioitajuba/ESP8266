/*
ESP8266 - WebWiFi3

Este exemplo, mostra as redes wifi disponíveis.
Quando passar o mouse sobre a tabela, o cursor muda
e clicando em um dos ítens da tabela, o campo netword
é preenchido com o nome da rede clicada.

Autor: Eng. Fabrício de Lima Ribeiro
26/01/23
*/

//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "meu_id";
const char* password = "minha_senha";

ESP8266WebServer server(80);

void handleRoot(){

  String Page;
  
  Page += F("<!DOCTYPE html><html lang='pt-br'><head>"
            "<meta charset='UTF-8'>"
            "<meta name='viewport' content='width=device-width'>"
            "<title>WiFi Config</title></head><body>"
            "<h1>Wifi config</h1>"
            "<style>"
            ".tabela tr {cursor: pointer;}"
            "</style>");

  Page += String(F("<p>Você está conectado a rede WiFI: <b>"))+ssid+F("</b></p>");

  Page += String(F("Redes WLAN disponíveis (atualize a página caso necessário)<br><br>"));
          
  Serial.println("scan start"); 
  int n = WiFi.scanNetworks();  
  Serial.println("scan done");

  Page += F("<table id='table' class='tabela' border='1'>");
  Page += F("<tr><th>Redes disponíveis</th>");
  Page += F("<th>Sinal [dBm]</th></tr>");
  
  if (n > 0) {
    for (int i = 0; i < n; i++){
      Page += F("<tr><td>")+WiFi.SSID(i)+F("</td>")+F("<td align ='center'>")+WiFi.RSSI(i)+F("</td></tr>");
     }
  } else {
    Page += F("No WLAN found");
  }
  
  Page += F("</table>");
  
  Page += F("\r\n<br/><form method='POST' action='wifisave'><h4>Conectar a rede:</h4>"
            "<input type='text'id='ssid' placeholder='network' name='n'/>"
            "<br/><input type='password' placeholder='password' name='p'/>"
            "<br/><br/><input type='submit' value='Connect/Disconnect'/></form>" 
            "<script>"
                "var table = document.getElementById('table');"                
                "for(var i = 1; i < table.rows.length; i++)"
                "{table.rows[i].onclick = function()"
                 "{document.getElementById('ssid').value = this.cells[0].innerHTML;};}"
             "</script>"                       
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
