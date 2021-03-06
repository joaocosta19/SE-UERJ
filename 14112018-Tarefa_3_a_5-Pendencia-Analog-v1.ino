#include <math.h>

double Thermister(int RawADC) {
  double Temp;
  Temp = log(((10240000/RawADC) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273,15; // Convert Kelvin to Celcius
  return Temp;
}

//const int redLED = 13;
//const int yellowLED = 7;

void setup() {
  Serial.begin(9600);

ACSR = 0<<7;                    //habilita o comparador analogico

DDRB = DDRB | B00100000;        //sets pin 13 as Output - redLED
DDRD = DDRD | B10000000;        //sets pin 7 as Output - yellowLED
//pinMode (redLED, OUTPUT);
//pinMode (yellowLED, OUTPUT); 
}

void loop() {
  //Serial.print(Thermister(analogRead(0))); //read pin A0
  Serial.print (Thermister (analogRead (0<<PINC))); //read pin A0
  Serial.println("c");
  delay(500);
   
  if ((Thermister(analogRead(0<<PINC))) > 30)       //if ((ACSR) > 30));
  {
  //digitalWrite (yellowLED, HIGH);             
  PORTD = PORTD | B10000000;
  delay (1000);
    } else {
    //digitalWrite (yellowLED, LOW);
    PORTD = PORTD | B00000000;
    }
  if ((Thermister(analogRead(0<<PINC))) > 36)       //if ((ACSR) > 36);
  { 
  //digitalWrite(redLED,HIGH);                    
  PORTB = PORTB | B00100000;
  delay (1000);
} else {
    //digitalWrite(redLED,LOW);
    PORTB = PORTB | B00000000;
  }
}
