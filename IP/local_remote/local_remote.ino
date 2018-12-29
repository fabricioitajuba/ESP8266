/*
 * Obtendo o IP interno e o externo utilizando o IPify
 * Autor: Eng. Fabricio de Lima Ribeiro
 * 24/12/18
*/
#include <ESP8266WiFi.h>

const char* wifiName = "";
const char* wifiPass = "";

String getIp()
{
  WiFiClient client;
  if (client.connect("api.ipify.org", 80)) 
  {
      //Serial.println("connected");
      client.println("GET / HTTP/1.0");
      client.println("Host: api.ipify.org");
      client.println();
  } else {
      Serial.println("Connection to ipify.org failed");
      return String();
  }
  delay(1000);
  String line;
  while(client.available())
  {
    line = client.readStringUntil('\n');
    //Serial.println(line);
  }
  return line;
}
  
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();

  Serial.print("Connecting to ");
  Serial.println(wifiName);

  WiFi.begin(wifiName, wifiPass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  
  Serial.print("IP interno: ");  
  Serial.println(WiFi.localIP());   //You can get IP address assigned to ESP
  
  Serial.print("IP externo: ");
  Serial.println(getIp());   //You can get IP address assigned to ESP
}

// the loop function runs over and over again forever
void loop() {
}
