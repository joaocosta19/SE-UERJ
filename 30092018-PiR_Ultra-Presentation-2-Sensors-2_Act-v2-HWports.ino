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
  //Define PIN PiR
    // DDRD = 0 << 3;            //DEFINE O PINO 3 COMO ENTRADA // DDRD = 1 << 3 // pinMode(pinoPIR, INPUT);0
    // DDRD = 1 << 7;         //DEFINE O PINO 7 COMO SAÍDA  // DDRD = 1 << 7 // pinMode(pinoLED, OUTPUT);1
  
  DDRD = B11110111;         // sets Arduino pins 1 to 7 as outputs, pin 3 as input
  //DDRD = DDRD ^ B10000000;  // this is safer as it sets pins 7 as output

  //Define PIN Ultrasonic
  pinMode(echoPin, INPUT);     //DEFINE O PINO 11 COMO ENTRADA (RECEBE)
  pinMode(trigPin, OUTPUT);     //DEFINE O PINO 8 COMO SAÍDA (ENVIA)
  pinMode(pinoBuzzer, OUTPUT);  //DECLARA O PINO 13 COMO SENDO SAÍDA
}
void loop(){
  //Programming PiR
 if(PORTD = B00001000){          //SE A LEITURA DO PINO FOR IGUAL A HIGH, FAZ  // PORTD = 1 << 3 //  digitalRead(pinoPIR) == HIGH//DDRD == B00001000
    (PORTD = B10000000);              //ACENDE O LED                              // PORTD = 1 << 7 // digitalWrite(pinoLED, HIGH)//PORTD = B10000000
 }else{                                                           //SENÃO, FAZ
  (PORTD = B00000000);                 //APAGA O LED                               // PORTD = ~(1 << 7) // digitalWrite(pinoLED, LOW)//PORTD = B11110111
 }

 //Programming Ultrasonic
hcsr04();     // FAZ A CHAMADA DO MÉTODO "hcsr04()"

if(distancia <= 60){        // SE A DISTÂNCIA ENTRE O OBJETO E O SENSOR ULTRASONICO FOR MENOR     //QUE 60CM, FAZ
tone(pinoBuzzer,1500);      //ACIONA O BUZZER
}else{                      //SENÃO, FAZ
noTone(pinoBuzzer);         //BUZZER PERMANECE DESLIGADO
}
}
  //MÉTODO RESPONSÁVEL POR CALCULAR A DISTÂNCIA
void hcsr04(){
digitalWrite(trigPin, LOW);     //SETA O PINO 8 COM UM PULSO BAIXO "LOW"
delayMicroseconds(2);           // DELAY DE 2 MICROSSEGUNDOS
digitalWrite(trigPin, HIGH);    //SETA O PINO 8 COM PULSO ALTO "HIGH"
delayMicroseconds(10);          // DELAY DE 10 MICROSSEGUNDOS
digitalWrite(trigPin, LOW);     //SETA O PINO 8 COM PULSO BAIXO "LOW" NOVAMENTE
                                // FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
                               //RESPOSTA DO ECHO EM CENTÍMETROS E ARMAZENA
                               //NA VARIÁVEL "distancia"
distancia = (ultrasonic.Ranging(CM));   // VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
}
