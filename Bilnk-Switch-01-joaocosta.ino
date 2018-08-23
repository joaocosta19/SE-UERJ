#define LED_PIN 13
#define BUT_PIN  7
 //Fazer o LED acompanhar o estado do botão
 
void setup () {
    pinMode(13, OUTPUT);       // Enable pin 13 for digital output
    pinMode(7, INPUT);        // Enable pin  2 for digital input
}
 
void loop () {
    int but = digitalRead(7); // Read button state
    digitalWrite(13, but);     // Copy state to LED
}

