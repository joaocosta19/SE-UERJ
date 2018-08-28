#define LED_PIN 13
#define BUT_PIN  2
 //Fazer o LED acompanhar o estado do botão slide 8
 
void setup () {
    pinMode(13, OUTPUT);       // Enable pin 13 for digital output
    pinMode(2, INPUT);        // Enable pin 2 for digital input
}
 
void loop () {
    int but = digitalRead(2); // Read button state
    digitalWrite(13, but);     // Copy state to LED
}

