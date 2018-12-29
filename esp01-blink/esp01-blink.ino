/*
 Blink the blue LED on the ESP-01 module
 Autor: Fabrício de Lima Ribeiro
 08/09/2018
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  Serial.println("led off");
  delay(250);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  Serial.println("led on");
  delay(250);
}
