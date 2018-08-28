#define LED_PIN 13
#define BUT_PIN  2
 //Parar ao pressionar o Botão com lógica if - sem setup pinmode input 2
 //EXERCICIO 1 - SLIDE 10
 
void setup () {
    pinMode(13, OUTPUT);       // Enable pin 13 for digital output
    pinMode(2, INPUT);         // Enable pin 2 for digital input
}
void loop () {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  int but = digitalRead (2);
  if (but) {
      digitalWrite (13, HIGH);
      while(0);                     //The condition is a boolean expression that evaluates to true(1) or false(0)
  }
}

