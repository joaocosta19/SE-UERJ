//COMPARADOR - Ultrasonic Sensor
// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the Ultrasonic trig pin is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue;        // value read from the pot
int outputValue;        // value output to the PWM (analog out)

//PiR Sensor Constants
//const int pinoPIR = 3;                  //PINO DIGITAL UTILIZADO PELO SENSOR DE PRESENÇA//Pino 3 = DDRD = 1 << 3 // const int pinoPIR = 3; 
//const int pinoLED = 7;                   //PINO DIGITAL UTILIZADO PELO LED// Com gpio => PORTD = 1 << 7 // const int pinoLED = 7;  

//Ultrasonic Sensor Constants
#include "Ultrasonic.h"   //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO

const int echoPin = 11;   //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)  //
const int trigPin = 8;  //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)     // 
const int pinoBuzzer = 13;  //PINO DIGITAL EM QUE O BUZZER ESTÁ CONECTADO // 

Ultrasonic ultrasonic(trigPin,echoPin);   //INICIALIZANDO OS PINOS

int distancia;    //CRIA UMA VARIÁVEL CHAMADA "distancia" DO TIPO INTEIRO
String result;    //CRIA UMA VARIÁVEL CHAMADA "result" DO TIPO STRING

void setup(){

      //COMPARADOR - Ultrasonic Sensor
          // initialize serial communications at 9600 bps:
  Serial.begin(9600);
          //ACD = 0, habilita o comparador analogico
          //ACIE = 1, habilita interrupção do comparador
          //ACIS1:0 = 11, habilita interrupção por borda de subida
          //ACSR = ( 0 << ACD ) | ( 1 << ACIE ) | ( 1 << ACIS1 ) | ( 1 << ACIS0 );
      
  //Define PIN PiR
    // DDRD = 0 << 3;            //DEFINE O PINO 3 COMO ENTRADA // DDRD = 1 << 3 // pinMode(pinoPIR, INPUT);0
    // DDRD = 1 << 7;           //DEFINE O PINO 7 COMO SAÍDA  // DDRD = 1 << 7 // pinMode(pinoLED, OUTPUT);1
          
  DDRD = DDRD & B11110111;        // sets pin 3 as input - PiR
  DDRD = DDRD | B10000000;        //sets pin 7 as Output - LeD

  //Define PIN Ultrasonic
  //pinMode(echoPin, INPUT);     //DEFINE O PINO 11 COMO ENTRADA (RECEBE)
  DDRB = DDRB & B11110111;
  //pinMode(trigPin, OUTPUT);     //DEFINE O PINO 8 COMO SAÍDA (ENVIA)
  DDRB = DDRB | B00000001;
  //pinMode(pinoBuzzer, OUTPUT);  //DECLARA O PINO 13 COMO SENDO SAÍDA
  DDRB = DDRB | B00100000;
}
void loop(){

      //COMPARATOR
      // read the analog in value:
  sensorValue = analogRead(analogInPin);    //PINC = 255
      // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
      // change the analog out value:
  analogWrite(analogOutPin, outputValue);
      // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);
      // wait 2 milliseconds before the next loop for the analog-to-digital
      // converter to settle after the last reading:
  delay(2);
  
  //Programming PiR

 if(PIND = PIND & B00001000){           //SE A LEITURA DO PINO FOR IGUAL A HIGH, FAZ  // PORTD = 1 << 3 //  digitalRead(pinoPIR) == HIGH//DDRD == B00001000
  (PORTD = B10000000);              //ACENDE O LED                              // PORTD = 1 << 7 // digitalWrite(pinoLED, HIGH)//PORTD = B10000000
 }else{                                                           //SENÃO, FAZ
 (PORTD = B00000000);                 //APAGA O LED                               // PORTD = ~(1 << 7) // digitalWrite(pinoLED, LOW)//PORTD = B11110111
 }

 //Programming Ultrasonic
hcsr04();     // FAZ A CHAMADA DO MÉTODO "hcsr04()"

if(distancia <= 30){        // SE A DISTÂNCIA ENTRE O OBJETO E O SENSOR ULTRASONICO FOR MENOR     //QUE 30CM, FAZ
tone(pinoBuzzer,1500);      //ACIONA O BUZZER
//tone ((PORTB = PORTB & B00100000),1500); DESLIGAVA O CCTO
}else{                      //SENÃO, FAZ
noTone(pinoBuzzer);         //BUZZER PERMANECE DESLIGADO
}
}
  //MÉTODO RESPONSÁVEL POR CALCULAR A DISTÂNCIA
void hcsr04(){
//digitalWrite(trigPin, LOW);     //SETA O PINO 8 COM UM PULSO BAIXO "LOW"
PORTB = PORTB & B00000000;
delayMicroseconds(2);           // DELAY DE 2 MICROSSEGUNDOS
//digitalWrite(trigPin, HIGH);    //SETA O PINO 8 COM PULSO ALTO "HIGH"
PORTB = PORTB | B00000001;
delayMicroseconds(10);          // DELAY DE 10 MICROSSEGUNDOS
//digitalWrite(trigPin, LOW);     //SETA O PINO 8 COM PULSO BAIXO "LOW" NOVAMENTE
PORTB = PORTB & B00000000;
                                // FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
                               //RESPOSTA DO ECHO EM CENTÍMETROS E ARMAZENA
                               //NA VARIÁVEL "distancia"
distancia = (ultrasonic.Ranging(CM));   // VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
}
