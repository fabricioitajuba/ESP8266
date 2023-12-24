/*
Exemplo de utilização da biblioteca modbusIP para o ESP8266
Autor: Eng. Fabrício Ribeiro
Data: 22/12/2023
*/

#include <ESP8266WiFi.h>
#include <Modbus.h>
#include <ModbusIP_ESP8266.h>

//Modbus Registers Offsets
const int INPUT_BIN = 100;    //SCADABR - Bobina (Coil Status) - Envia Binário
const int OUTPUT_BIN = 101;   //SCADABR - Entrada discreta (Input Status) - Recebe Binário
const int INPUT_VAR = 102;    //SCADABR - Registrador Holding - Envia Variável
const int OUTPUT_VAR = 103;   //SCADABR - Registrador de entrada (input Register) - Recebe Variável

//Used Pins
const int led = 2;    //GPIO2
const int chave = 0;  //GPIO0

//ModbusIP object
ModbusIP mb;
  
long ts;
int var;

void setup() {

  Serial.begin(115200);
  delay(400);

  WiFi.begin("SSID", "PASS");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  delay(400);
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(led, OUTPUT);
  pinMode(chave, INPUT);

  mb.server();

  mb.addCoil(INPUT_BIN);
  mb.addIsts(OUTPUT_BIN);
  mb.addHreg(INPUT_VAR, 7); //Configurando o Holding Register com valor inicial = 7
  mb.addIreg(OUTPUT_VAR);

  ts = millis();
  var = 7376;
}
 
void loop() {
  
  //Call once inside loop() - all magic here
  mb.task();
  
  //Atualiza valores a cada 1 segundo
  if(millis() > ts + 1000){
    
    ts = millis();

    digitalWrite(led, mb.Coil(INPUT_BIN));    //Recebe um binário
    Serial.println(mb.Coil(INPUT_BIN));
    
    mb.Ists(OUTPUT_BIN, digitalRead(chave));  //Envia um binário
    
    Serial.println(mb.Hreg(INPUT_VAR));       //Recebe uma variável
    
    mb.Ireg(OUTPUT_VAR, var);                 //Envia uma variável
  }  

  delay(10);
}