#define LED_PIN 13
#define BUT_PIN  7
 //Parar ao pressionar o Botão com lógica if
 //EXERCICIO 1 - SLIDE 10
 
void setup () {
    pinMode(13, OUTPUT);       // Enable pin 13 for digital output
    pinMode(7, INPUT);        // Enable pin  7 for digital input
}
 
void loop () {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
 int but = digitalRead (7);
 if (but) {
  digitalWrite (13, HIGH);
  while (1);
 }
}

