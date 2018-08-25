#define LED_PIN 9
#define BUT_PIN 7
 //I/O Básico - SLIDE 3
void setup () {
    pinMode(7, INPUT);        // Enable pin  7 for digital input
    pinMode(9, OUTPUT);       // Enable pin 9 for digital output
}
void loop () {
  int val = digitalRead (7);
  digitalWrite (9, HIGH);
}


